#include <ql/quantlib.hpp>
#include <boost/assign/std/vector.hpp>
#include <iostream>

using namespace QuantLib;
using namespace boost::assign;

int main() {

    try {

        Real eta = atof(getenv("ETA"));
        Real beta = atof(getenv("BETA"));
        Real sigma = atof(getenv("SIGMA"));
        Real kappa = atof(getenv("KAPPA"));
        int full = atoi(getenv("FULL"));
        int single = atoi(getenv("SINGLE"));
        int calibrate = atoi(getenv("CALIBRATE"));

        // test smile

        Date refDate(28, May, 2015);
        Settings::instance().evaluationDate() = refDate;

        Real rateLevel = 0.03;
        Handle<YieldTermStructure> yts(boost::make_shared<FlatForward>(
            0, TARGET(), rateLevel, Actual365Fixed()));

        boost::shared_ptr<IborIndex> euribor6m =
            boost::make_shared<Euribor>(6 * Months, yts);

        Date effectiveDate = TARGET().advance(refDate, 2 * Days);
        Date startDate = TARGET().advance(effectiveDate, 10 * Years);
        Date maturityDate = TARGET().advance(startDate, 10 * Years);

        Schedule fixedSchedule(startDate, maturityDate, 1 * Years, TARGET(),
                               ModifiedFollowing, ModifiedFollowing,
                               DateGeneration::Forward, false);
        Schedule floatingSchedule(startDate, maturityDate, 6 * Months, TARGET(),
                                  ModifiedFollowing, ModifiedFollowing,
                                  DateGeneration::Forward, false);

        boost::shared_ptr<VanillaSwap> underlyingDummy =
            boost::make_shared<VanillaSwap>(VanillaSwap(
                VanillaSwap::Payer, 1.0, fixedSchedule, 0.03, Thirty360(),
                floatingSchedule, euribor6m, 0.0, Actual360()));

        boost::shared_ptr<PricingEngine> discEngine =
            boost::make_shared<DiscountingSwapEngine>(yts);

        underlyingDummy->setPricingEngine(discEngine);

        Real atmForward = underlyingDummy->fairRate();
        Real annuity = -underlyingDummy->fixedLegBPS() / 1E-4;

        // create underlyings for smile

        std::vector<Real> offsets;
        offsets += -0.02, -0.015, -0.01, -0.0050, -0.0025, 0.0, 0.0025, 0.0050,
            0.01, 0.015, 0.02;

        std::vector<boost::shared_ptr<Swaption> > swaptions, swaptions2;

        std::vector<Date> exerciseDates;
        for (Size i = 0; i < 1; ++i)
            exerciseDates.push_back(
                TARGET().advance(fixedSchedule[i], -2 * Days));
        boost::shared_ptr<Exercise> exercise =
            boost::make_shared<BermudanExercise>(exerciseDates, false);

        for (int i = -1; i < static_cast<int>(offsets.size()); ++i) {
            Real strike = i == -1 ? 0.0 : atmForward + offsets[i];
            boost::shared_ptr<VanillaSwap> underlyingTmp =
                boost::make_shared<VanillaSwap>(
                    VanillaSwap(strike >= atmForward ? VanillaSwap::Payer
                                                     : VanillaSwap::Receiver,
                                1.0, fixedSchedule, strike, Thirty360(),
                                floatingSchedule, euribor6m, 0.0, Actual360()));
            boost::shared_ptr<VanillaSwap> underlyingTmp2 =
                boost::make_shared<VanillaSwap>(
                    VanillaSwap(strike >= atmForward ? VanillaSwap::Receiver
                                                     : VanillaSwap::Payer,
                                1.0, fixedSchedule, strike, Thirty360(),
                                floatingSchedule, euribor6m, 0.0, Actual360()));
            boost::shared_ptr<Swaption> swaptionTmp =
                boost::make_shared<Swaption>(underlyingTmp, exercise);
            boost::shared_ptr<Swaption> swaptionTmp2 =
                boost::make_shared<Swaption>(underlyingTmp2, exercise);
            swaptions.push_back(swaptionTmp);
            swaptions2.push_back(swaptionTmp2);
        }

        std::vector<Date> stepDates(exerciseDates.begin(),
                                    exerciseDates.end() - 1);
        std::vector<Real> sigmas(stepDates.size() + 1, sigma);

        Real tte = yts->timeFromReference(exerciseDates.front());

        // --------------------------------------------------------------
        // smiles in gsr (benchmark) and betaeta
        // --------------------------------------------------------------

        boost::shared_ptr<Gsr> gsr =
            boost::make_shared<Gsr>(yts, stepDates, sigmas, kappa, 60.0);
        boost::shared_ptr<PricingEngine> gsrSwaptionEngine =
            boost::make_shared<Gaussian1dSwaptionEngine>(gsr, 64, 7.0, true,
                                                         false, yts);

        // std::clog << "strike &  price(Gsr) &  price(Tab) & price(Fl) & "
        //              "PC(Tab) "
        //              "& PC(Fl)"
        //           << std::endl;
        std::clog.precision(6);
        std::cout.precision(6);

        std::vector<Real> betaSc, etaSc, kappaSc;
        if (single) {
            betaSc.push_back(beta);
            etaSc.push_back(eta);
            kappaSc.push_back(kappa);
        } else {
            // beta scenarios
            betaSc.push_back(0.1);
            betaSc.push_back(1.0);
            betaSc.push_back(2.0);
            betaSc.push_back(3.0);
            betaSc.push_back(4.0);
            betaSc.push_back(5.0);
            // eta scenarios
            etaSc.push_back(0.0);
            etaSc.push_back(0.2);
            etaSc.push_back(0.5);
            etaSc.push_back(0.8);
            etaSc.push_back(1.0);
            // kappa scenarios
            kappaSc.push_back(-0.05);
            kappaSc.push_back(-0.01);
            kappaSc.push_back(0.0);
            kappaSc.push_back(0.01);
            kappaSc.push_back(0.05);
        }

        // we recalibrate alpha such that a reference ATM swaption is matched
        // so that the smile comparison makes sense
        Handle<Quote> referenceVol(boost::make_shared<SimpleQuote>(0.16));
        std::vector<boost::shared_ptr<CalibrationHelper> > helper;
        boost::shared_ptr<CalibrationHelper> tmp =
            boost::make_shared<SwaptionHelper>(
                10 * Years, 10 * Years, referenceVol, euribor6m, 1 * Years,
                Thirty360(), Actual360(), yts);
        helper.push_back(tmp);

        LevenbergMarquardt om;
        EndCriteria ec(1000, 100, 1E-8, 1E-8, 1E-8);

        helper[0]->setPricingEngine(gsrSwaptionEngine);
        if (calibrate)
            gsr->calibrateVolatilitiesIterative(helper, om, ec);
        // std::cout << "GSR calibrated sigma = " << gsr->volatility()[0] <<
        // std::endl;

        for (Size m2 = 0; m2 < etaSc.size(); ++m2) {
            for (Size m3 = 0; m3 < kappaSc.size(); ++m3) {
                for (Size m1 = 0; m1 < betaSc.size(); ++m1) {
                    boost::shared_ptr<BetaEta> betaEta =
                        boost::make_shared<BetaEta>(yts, stepDates, sigmas,
                                                    kappaSc[m3], betaSc[m1],
                                                    etaSc[m2]);
                    boost::shared_ptr<PricingEngine> betaEtaSwaptionEngine =
                        boost::make_shared<BetaEtaSwaptionEngine>(betaEta, 64,
                                                                  7.0, yts);
                    // recalibrate the alpha
                    helper[0]->setPricingEngine(betaEtaSwaptionEngine);
                    if (calibrate)
                        betaEta->calibrateVolatilitiesIterative(helper, om, ec);

                    Real implVol_m200;
                    Real implVol_atm;
                    Real implVol_p200;

                    for (Size i = 0; i < swaptions.size(); ++i) {
                        Real strike =
                            i == 0 ? 0.0 : atmForward + offsets[i - 1];
                        // --------------------
                        // gsr
                        // --------------------
                        swaptions[i]->setPricingEngine(gsrSwaptionEngine);
                        Real npvGsr = swaptions[i]->NPV();
                        Real implVolGsr = 0.0;
                        try {
                            implVolGsr =
                                blackFormulaImpliedStdDev(
                                    strike >= atmForward ? Option::Call
                                                         : Option::Put,
                                    strike, atmForward, npvGsr, annuity) /
                                std::sqrt(tte);
                        } catch (...) {
                        }
                        // --------------------
                        // betaeta with tabulation
                        // --------------------
                        betaEta->useTabulation(true);
                        swaptions[i]->setPricingEngine(betaEtaSwaptionEngine);
                        swaptions2[i]->setPricingEngine(betaEtaSwaptionEngine);
                        Real npvBetaEtaTab = swaptions[i]->NPV();
                        Real implVolBetaEtaTab = 0.0;
                        try {
                            implVolBetaEtaTab =
                                blackFormulaImpliedStdDev(
                                    strike >= atmForward ? Option::Call
                                                         : Option::Put,
                                    strike, atmForward, npvBetaEtaTab,
                                    annuity) /
                                std::sqrt(tte);
                        } catch (...) {
                        }
                        // --------------------
                        // put call wih tabulation
                        // --------------------
                        Real npvBetaEtaTab2 = swaptions2[i]->NPV();
                        // --------------------
                        // betaeta without tabulation (if active, otherwise
                        // identical to tab)
                        // --------------------
                        betaEta->useTabulation(full ? false : true);
                        Real npvBetaEta = swaptions[i]->NPV();
                        Real implVolBetaEta = 0.0;
                        try {
                            implVolBetaEta =
                                blackFormulaImpliedStdDev(
                                    strike >= atmForward ? Option::Call
                                                         : Option::Put,
                                    strike, atmForward, npvBetaEta, annuity) /
                                std::sqrt(tte);
                        } catch (...) {
                        }
                        // --------------------
                        // put call wihout tabulation
                        // --------------------
                        Real npvBetaEta2 = swaptions2[i]->NPV();
                        // --------------------
                        // results output
                        // --------------------
                        Real parityErrorTab =
                            (npvBetaEtaTab2 - npvBetaEtaTab) / annuity -
                            (strike < atmForward ? 1.0 : -1.0) *
                                (atmForward - strike);
                        Real parityError =
                            (npvBetaEta2 - npvBetaEta) / annuity -
                        //     (strike < atmForward ? 1.0 : -1.0) *
                        //         (atmForward - strike);
                        // // std::cout << etaSc[m2] << " " << betaSc[m1] << " "
                        // //           << kappaSc[m3] << " " << strike << " "
                        // //           << npvBetaEtaTab << " "
                        //           << parityErrorTab << " "
                        //           << implVolBetaEtaTab << "\n";
                        // std::cout << strike << " & " << npvGsr << " & "
                        //           << npvBetaEtaTab << " & " << npvBetaEta
                        //           << " & " << parityErrorTab << " & "
                        //           << parityError << " \\\\" << std::endl;
                        if (i == 0) // only output zero strike receiver
                            std::cout << etaSc[m2] << " & " << betaSc[m1]
                                      << " & " << kappaSc[m3] << " & "
                                      << npvBetaEtaTab << " \\\\ \n";
                        if (i == 1)
                            implVol_m200 = implVolBetaEtaTab;
                        if (i == 6)
                            implVol_atm = implVolBetaEtaTab;
                        if (i == 11)
                            implVol_p200 = implVolBetaEtaTab;
                    } // strikes
                    if (std::fabs(implVol_atm - referenceVol->value()) > 0.0020)
                        std::clog << "calibration failed for eta=" << etaSc[m2]
                                  << " kappa=" << kappaSc[m3]
                                  << " beta=" << betaSc[m1] << std::endl;
                    // if (std::fabs(implVol_atm - referenceVol->value()) <
                    // 0.0020)
                    //     std::cout
                    //         << etaSc[m2] << " & " << kappaSc[m3] << " & "
                    //         << betaSc[m1] << " & " << implVol_m200 << " & "
                    //         << implVol_atm << " & " << implVol_p200 << " & "
                    //         << (implVol_p200 - implVol_m200) << " & "
                    //         << (implVol_p200 - 2.0 * implVol_atm +
                    //         implVol_m200)
                    //         << " \\\\" << std::endl;
                } // kappa scenarios
            }     // eta scenarios
        }         // beta scnearios
    } catch (QuantLib::Error e) {
        std::clog << e.what() << std::endl;
    }

    return 0;
}
