#include <ql/quantlib.hpp>

#include <iostream>

using namespace QuantLib;

int main() {

    Handle<YieldTermStructure> yts(
        boost::make_shared<FlatForward>(0, TARGET(), 0.03, Actual365Fixed()));

    // test density

    Real beta = atof(getenv("BETA"));
    Real sigma = atof(getenv("SIGMA"));
    Real eta = atof(getenv("ETA"));
    Real x0 = atof(getenv("X0"));
    Real t0 = atof(getenv("T0"));
    Real t = atof(getenv("T"));
    Real lower = atof(getenv("LOWER"));
    Real upper = atof(getenv("UPPER"));
    Real h = atof(getenv("H"));

    sigma = 0.0010;
    while (sigma < 0.10) {

        Array times(0);
        std::vector<Date> dates(0);
        std::vector<Real> alpha(1, sigma);
        Array alpha2(1, sigma);
        std::vector<Real> kap(1, 0.01);
        Array kap2(1, 0.0);
        BetaEta model(yts, dates, alpha, kap, beta, eta);
        //Gsr model(yts, dates, alpha, kap);
        BetaEtaCore core(times, alpha2, kap2, beta, eta);

        model.useTabulation(false);

        Real tmp = lower; //-1.0 / beta;

        // Real sum = 0.0;

        // std::cout.precision(10);

        // while (tmp < upper) {
        //     Real d = core.p(t0, x0, t, tmp);
        //     std::cout << tmp << " " << d << std::endl;
        //     tmp += h;
        //     sum += h * d;
        // }

        // model.useTabulation(false);
        // Real py0_full = core.prob_y_0(t0,x0,t,false);
        // model.useTabulation(true);
        // Real py0_tab = core.prob_y_0(t0,x0,t,true);

        // std::clog << "sum      = " << sum << "\n";
        // std::clog << "py0 full = " << py0_full << " => " << sum+py0_full <<
        // "\n";
        // std::clog << "py0 tab  = " << py0_tab << " => " << sum+py0_tab <<
        // "\n";

        Real v = (t - t0) * sigma * sigma;
        Real s = std::sqrt(v);
        while (tmp < upper) {
            Real p = model.zerobond(t, t0, tmp);
            Real r = -std::log(p) / (t - t0);
            std::cout << sigma << " " << tmp << " " << r << std::endl;
            tmp += h;
        }
        std::cout << std::endl;

        sigma += 0.0010;
   }

    return 0;

    // Real eta = atof(getenv("ETA"));
    // Real beta = atof(getenv("BETA"));
    // Real t0 = atof(getenv("T0"));
    // Real t = atof(getenv("T"));
    // Real x0 = atof(getenv("X0"));
    // Real sigma= atof(getenv("SIGMA"));
    // Real kappa= atof(getenv("KAPPA"));

    // // test pretabulated M
    // Array times(0);
    // Array alpha(1, sigma);
    // Array kap(1, kappa);

    // Real eta0 = 0.0, eta05 = 0.5, eta1 = 1.0;
    // boost::shared_ptr<BetaEtaCore> core0_5 =
    //     boost::make_shared<BetaEtaCore>(times, alpha, kap, beta, eta05);
    // boost::shared_ptr<BetaEtaCore> core1 =
    //     boost::make_shared<BetaEtaCore>(times, alpha, kap, beta, eta1);
    // boost::shared_ptr<BetaEtaCore> core =
    //     boost::make_shared<BetaEtaCore>(times, alpha, kap, beta, eta);

    // // std::cerr << "eta=0.5 (analytical): M(t,x,T) = "
    // //           << core0_5->M(t0, x0, t, false) << "\n";
    // // std::cerr << "eta=1   (gh        ): M(t,x,T) = "
    // //           << core1->M(t0, x0, t, false) << "\n";
    // std::cerr << "eta=" << eta
    //           << " (full): M(t,x,T) = " << core->M(t0, x0, t, false) << "\n";
    // // std::cerr << "eta=" << eta
    // //           << " (pre ): M(t,x,T) = " << core->M(t0, x0, t, true) <<
    // "\n";

    // return 0;

    // // test smile

    // Date refDate(28, May, 2015);
    // Settings::instance().evaluationDate() = refDate;

    // Real rateLevel = 0.05;
    // Handle<YieldTermStructure> yts(boost::make_shared<FlatForward>(
    //     0, TARGET(), rateLevel, Actual365Fixed()));

    // boost::shared_ptr<IborIndex> euribor6m =
    //     boost::make_shared<Euribor>(6 * Months, yts);

    // Date effectiveDate = TARGET().advance(refDate, 2 * Days);
    // Date startDate = TARGET().advance(effectiveDate, 5 * Years);
    // Date maturityDate = TARGET().advance(effectiveDate, 10 * Years);

    // Schedule fixedSchedule(startDate, maturityDate, 1 * Years, TARGET(),
    //                        ModifiedFollowing, ModifiedFollowing,
    //                        DateGeneration::Forward, false);
    // Schedule floatingSchedule(startDate, maturityDate, 6 * Months, TARGET(),
    //                           ModifiedFollowing, ModifiedFollowing,
    //                           DateGeneration::Forward, false);

    // boost::shared_ptr<VanillaSwap> underlyingDummy =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Payer, 1.0, fixedSchedule, 0.03, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));

    // boost::shared_ptr<PricingEngine> discEngine =
    //     boost::make_shared<DiscountingSwapEngine>(yts);

    // underlyingDummy->setPricingEngine(discEngine);

    // Real atmForward = underlyingDummy->fairRate();
    // std::cout << "atmForward = " << atmForward << std::endl;
    // Real annuity = -underlyingDummy->fixedLegBPS() / 1E-4;

    // Real strikeR4 = atmForward - 0.0200;
    // Real strikeR3 = atmForward - 0.0150;
    // Real strikeR2 = atmForward - 0.0100;
    // Real strikeR1 = atmForward - 0.0050;
    // Real strikeAtm = atmForward;
    // Real strikeP1 = atmForward + 0.0050;
    // Real strikeP2 = atmForward + 0.0100;
    // Real strikeP3 = atmForward + 0.0150;
    // Real strikeP4 = atmForward + 0.0200;

    // boost::shared_ptr<VanillaSwap> underlyingR4 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Receiver, 1.0, fixedSchedule, strikeR4, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingR3 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Receiver, 1.0, fixedSchedule, strikeR3, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingR2 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Receiver, 1.0, fixedSchedule, strikeR2, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingR1 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Receiver, 1.0, fixedSchedule, strikeR1, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingAtm =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Receiver, 1.0, fixedSchedule, strikeAtm,
    //         Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingP1 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Payer, 1.0, fixedSchedule, strikeP1, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingP2 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Payer, 1.0, fixedSchedule, strikeP2, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingP3 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Payer, 1.0, fixedSchedule, strikeP3, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));
    // boost::shared_ptr<VanillaSwap> underlyingP4 =
    //     boost::make_shared<VanillaSwap>(VanillaSwap(
    //         VanillaSwap::Payer, 1.0, fixedSchedule, strikeP4, Thirty360(),
    //         floatingSchedule, euribor6m, 0.0, Actual360()));

    // std::vector<Date> exerciseDates;
    // for (Size i = 0; i < 1; ++i)
    //     exerciseDates.push_back(TARGET().advance(fixedSchedule[i], -2 *
    //     Days));

    // boost::shared_ptr<Exercise> exercise =
    //     boost::make_shared<BermudanExercise>(exerciseDates, false);

    // boost::shared_ptr<Swaption> swaptionR4 =
    //     boost::make_shared<Swaption>(underlyingR4, exercise);
    // boost::shared_ptr<Swaption> swaptionR3 =
    //     boost::make_shared<Swaption>(underlyingR3, exercise);
    // boost::shared_ptr<Swaption> swaptionR2 =
    //     boost::make_shared<Swaption>(underlyingR2, exercise);
    // boost::shared_ptr<Swaption> swaptionR1 =
    //     boost::make_shared<Swaption>(underlyingR1, exercise);
    // boost::shared_ptr<Swaption> swaptionAtm =
    //     boost::make_shared<Swaption>(underlyingAtm, exercise);
    // boost::shared_ptr<Swaption> swaptionP1 =
    //     boost::make_shared<Swaption>(underlyingP1, exercise);
    // boost::shared_ptr<Swaption> swaptionP2 =
    //     boost::make_shared<Swaption>(underlyingP2, exercise);
    // boost::shared_ptr<Swaption> swaptionP3 =
    //     boost::make_shared<Swaption>(underlyingP3, exercise);
    // boost::shared_ptr<Swaption> swaptionP4 =
    //     boost::make_shared<Swaption>(underlyingP4, exercise);

    // std::vector<Date> stepDates(exerciseDates.begin(), exerciseDates.end() -
    // 1);
    // std::vector<Real> sigmas(stepDates.size() + 1, 0.005);

    // Real reversion = 0.08;

    // Real tte = yts->timeFromReference(exerciseDates.front());

    // // --------------------------------------------------------------
    // // Gsr Model as benchmark
    // // --------------------------------------------------------------

    // boost::shared_ptr<Gsr> gsr =
    //     boost::make_shared<Gsr>(yts, stepDates, sigmas, reversion, 50.0);

    // boost::shared_ptr<PricingEngine> gsrSwaptionEngine =
    //     boost::make_shared<Gaussian1dSwaptionEngine>(gsr, 64, 7.0, true,
    //     false,
    //                                                  yts);

    // swaptionR4->setPricingEngine(gsrSwaptionEngine);
    // swaptionR3->setPricingEngine(gsrSwaptionEngine);
    // swaptionR2->setPricingEngine(gsrSwaptionEngine);
    // swaptionR1->setPricingEngine(gsrSwaptionEngine);
    // swaptionAtm->setPricingEngine(gsrSwaptionEngine);
    // swaptionP1->setPricingEngine(gsrSwaptionEngine);
    // swaptionP2->setPricingEngine(gsrSwaptionEngine);
    // swaptionP3->setPricingEngine(gsrSwaptionEngine);
    // swaptionP4->setPricingEngine(gsrSwaptionEngine);

    // Real npvR4Gsr = swaptionR4->NPV();
    // Real npvR3Gsr = swaptionR3->NPV();
    // Real npvR2Gsr = swaptionR2->NPV();
    // Real npvR1Gsr = swaptionR1->NPV();
    // Real npvAtmGsr = swaptionAtm->NPV();
    // Real npvP1Gsr = swaptionP1->NPV();
    // Real npvP2Gsr = swaptionP2->NPV();
    // Real npvP3Gsr = swaptionP3->NPV();
    // Real npvP4Gsr = swaptionP4->NPV();
    // Real implVolR4Gsr =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR4, atmForward,
    //     npvR4Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolR3Gsr =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR3, atmForward,
    //     npvR3Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolR2Gsr =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR2, atmForward,
    //     npvR2Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolR1Gsr =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR1, atmForward,
    //     npvR1Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolAtmGsr =
    //     blackFormulaImpliedStdDev(Option::Call, strikeAtm, atmForward,
    //                               npvAtmGsr, annuity) /
    //     std::sqrt(tte);
    // Real implVolP1Gsr =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP1, atmForward,
    //     npvP1Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolP2Gsr =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP2, atmForward,
    //     npvP2Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolP3Gsr =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP3, atmForward,
    //     npvP3Gsr,
    //                               annuity) /
    //     std::sqrt(tte);
    // Real implVolP4Gsr =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP4, atmForward,
    //     npvP4Gsr,
    //                               annuity) /
    //     std::sqrt(tte);

    // std::cerr << "npv Atm (Gsr) = " << npvAtmGsr << std::endl;
    // std::cerr << "volR4 (Gsr) = " << implVolR4Gsr << std::endl;
    // std::cerr << "volR3. (Gsr) = " << implVolR3Gsr << std::endl;
    // std::cerr << "volR2 (Gsr) = " << implVolR2Gsr << std::endl;
    // std::cerr << "volR1 (Gsr) = " << implVolR1Gsr << std::endl;
    // std::cerr << "volAm (Gsr) = " << implVolAtmGsr << std::endl;
    // std::cerr << "volP1 (Gsr) = " << implVolP1Gsr << std::endl;
    // std::cerr << "volP2 (Gsr) = " << implVolP2Gsr << std::endl;
    // std::cerr << "volP3 (Gsr) = " << implVolP3Gsr << std::endl;
    // std::cerr << "volP4 (Gsr) = " << implVolP4Gsr << std::endl;

    // // --------------------------------------------------------------
    // // BetaEta with eta = 0 (i.e. Hull White case)
    // // --------------------------------------------------------------

    // beta = 0.2; // doesn't matter when eta is zero
    // eta = 0.9;

    // boost::shared_ptr<BetaEta> betaEta = boost::make_shared<BetaEta>(
    //     yts, stepDates, sigmas, reversion, beta, eta);

    // boost::shared_ptr<PricingEngine> betaEtaSwaptionEngine =
    //     boost::make_shared<BetaEtaSwaptionEngine>(betaEta, 64, 6.0, yts);

    // swaptionR4->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionR3->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionR2->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionR1->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionAtm->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionP1->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionP2->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionP3->setPricingEngine(betaEtaSwaptionEngine);
    // swaptionP4->setPricingEngine(betaEtaSwaptionEngine);

    // Real npvR4BetaEta = swaptionR4->NPV();
    // Real npvR3BetaEta = swaptionR3->NPV();
    // Real npvR2BetaEta = swaptionR2->NPV();
    // Real npvR1BetaEta = swaptionR1->NPV();
    // Real npvAtmBetaEta = swaptionAtm->NPV();
    // Real npvP1BetaEta = swaptionP1->NPV();
    // Real npvP2BetaEta = swaptionP2->NPV();
    // Real npvP3BetaEta = swaptionP3->NPV();
    // Real npvP4BetaEta = swaptionP4->NPV();
    // Real implVolR4BetaEta =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR4, atmForward,
    //                               npvR4BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolR3BetaEta =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR3, atmForward,
    //                               npvR3BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolR2BetaEta =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR2, atmForward,
    //                               npvR2BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolR1BetaEta =
    //     blackFormulaImpliedStdDev(Option::Put, strikeR1, atmForward,
    //                               npvR1BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolAtmBetaEta =
    //     blackFormulaImpliedStdDev(Option::Call, strikeAtm, atmForward,
    //                               npvAtmBetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolP1BetaEta =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP1, atmForward,
    //                               npvP1BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolP2BetaEta =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP2, atmForward,
    //                               npvP2BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolP3BetaEta =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP3, atmForward,
    //                               npvP3BetaEta, annuity) /
    //     std::sqrt(tte);
    // Real implVolP4BetaEta =
    //     blackFormulaImpliedStdDev(Option::Call, strikeP4, atmForward,
    //                               npvP4BetaEta, annuity) /
    //     std::sqrt(tte);

    // std::cerr << "npv Atm (BetaEta) = " << npvAtmBetaEta << std::endl;
    // std::cerr << "volR4 (BetaEta) = " << implVolR4BetaEta << std::endl;
    // std::cerr << "volR3 (BetaEta) = " << implVolR3BetaEta << std::endl;
    // std::cerr << "volR2 (BetaEta) = " << implVolR2BetaEta << std::endl;
    // std::cerr << "volR1 (BetaEta) = " << implVolR1BetaEta << std::endl;
    // std::cerr << "volAm (BetaEta) = " << implVolAtmBetaEta << std::endl;
    // std::cerr << "volP1 (BetaEta) = " << implVolP1BetaEta << std::endl;
    // std::cerr << "volP2 (BetaEta) = " << implVolP2BetaEta << std::endl;
    // std::cerr << "volP3 (BetaEta) = " << implVolP3BetaEta << std::endl;
    // std::cerr << "volP4 (BetaEta) = " << implVolP4BetaEta << std::endl;

    // return 0;
}
