#ifndef start_stop_watchH
#define start_stop_watchH

#include <stack>

namespace rateCheckApp
{
#ifdef __CLR_VER
#pragma managed(push, off)
#endif

//========================================================================
//  CLASS StartStopWatch --  Accurate StartStopWatch timer class
//========================================================================

class StartStopWatch
{
public:
    // Ctors
    StartStopWatch();
    StartStopWatch(const StartStopWatch & other);
    virtual ~StartStopWatch();

    StartStopWatch & operator=(const StartStopWatch & other);

    // Member Fcns
    void            Start();
    double          Stop();
    double          Elapsed();
    void            uS(int delay);
    double          Now();
    double          Mhz() const;

private:
    // Data
    std::stack<double> Timer;

    class StartStopWatchImpl * impl;
    // Methods
};

#ifdef __CLR_VER
#pragma managed(pop)
#endif
}  // namespace

#endif

