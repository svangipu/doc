#include <ql/quantlib.hpp>

#include <boost/make_shared.hpp>

using namespace QuantLib;

int main() {

    Date evalDate(13, July, 2015);
    Settings::instance().evaluationDate() = evalDate;
    Date maturity = evalDate + 10 * Years;

    const Real S0 = 100.0;
    const Real K = 120.0;
    const Real vol = 0.20;

    const Size tGrid = 500*10;
    const Size xGrid = 2* 50 + 1;

    const Handle<Quote> S0_q(boost::make_shared<SimpleQuote>(S0));
    const Handle<BlackVolTermStructure> blackVol(
        boost::make_shared<BlackConstantVol>(evalDate, NullCalendar(), vol,
                                             Actual365Fixed()));
    Handle<YieldTermStructure> zeroyts(
        boost::make_shared<FlatForward>(evalDate, 0.0, Actual365Fixed()));

    boost::shared_ptr<StrikedTypePayoff> payoff =
        boost::make_shared<PlainVanillaPayoff>(Option::Call, K);
    boost::shared_ptr<Exercise> exercise =
        boost::make_shared<AmericanExercise>(maturity);
    boost::shared_ptr<VanillaOption> option =
        boost::make_shared<VanillaOption>(payoff, exercise);

    boost::shared_ptr<BlackScholesProcess> p =
        boost::make_shared<BlackScholesProcess>(S0_q, zeroyts, blackVol);

    boost::shared_ptr<FdBlackScholesVanillaEngine> engine =
        boost::make_shared<FdBlackScholesVanillaEngine>(p, tGrid, xGrid, 0,
                                                        FdmSchemeDesc::ExplicitEuler());

    option->setPricingEngine(engine);

    std::clog << "c = " << option->NPV() << std::endl;
}
