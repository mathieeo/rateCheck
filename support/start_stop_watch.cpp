#include <start_stop_watch.h>


#ifndef LINUX
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace   rateCheckApp
{

static const double Meg = 1.0e6;
//static const double Gig = 1.0e9;

///
/// class StartStopWatchImpl.
///
/// Windows implementation.
///
#ifndef LINUX

class StartStopWatchImpl
{
public:
    StartStopWatchImpl();
    
    double          TimerRate() const
    {  return static_cast<double>(FTimerRate);  }
    
    double Now();
private:
    int64         FTimerRate;
    void QueryPerformanceFrequency(int64 & timerRate);
    void QueryPerformanceCounter(int64 & count);
};

///
///  Constructor of class StartStopWatchImpl
///

StartStopWatchImpl::StartStopWatchImpl()
    : FTimerRate(1)
{
    QueryPerformanceFrequency(FTimerRate);

    if (!FTimerRate)
        throw std::string("Performance timer unavailable!");
}

///
/// StartStopWatchImpl::Now().
///
/// returns a high precision time value
///

double StartStopWatchImpl::Now()
{
    int64 Current;
    QueryPerformanceCounter(Current);

    return static_cast<double>(Current)/TimerRate();
}

///
/// StartStopWatchImpl::QueryPerformanceFrequency().
///

void StartStopWatchImpl::QueryPerformanceFrequency(int64 & timerRate)
{
    ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&timerRate));
}

///
/// StartStopWatchImpl::QueryPerformancCounter().
///

void StartStopWatchImpl::QueryPerformanceCounter(int64 & count)
{
    ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&count));
}
#else

class StartStopWatchImpl
{
public:
    StartStopWatchImpl()  {  }
    double Now();
    double TimerRate() const
    {  return 0;  }

private:

    struct timeval now;
};

///
/// StartStopWatchImpl::Now().
///
/// returns a high precision time value
///

double StartStopWatchImpl::Now()
{

    gettimeofday(&now, NULL);
    double ret_val = now.tv_sec;
    ret_val += now.tv_usec/Meg;

    return ret_val;
}

#endif
///
/// CLASS StartStopWatch.
///
/// Accurate StartStopWatch timer class
///
///
//  constructor of class StartStopWatch
///

StartStopWatch::StartStopWatch()
    : impl(new StartStopWatchImpl())
{

}

///
///  Copy constructor
///

StartStopWatch::StartStopWatch(const StartStopWatch & /*other*/)
    : impl(new StartStopWatchImpl())
{
}

///
///  destructor of class StartStopWatch
///

StartStopWatch::~StartStopWatch()
{
    delete impl;  impl = 0;
}

///
///  Assignment operator
///

StartStopWatch & StartStopWatch::operator =(const StartStopWatch & other)
{
    if (this != &other)
    {
        delete impl;
        impl = new StartStopWatchImpl();
    }

    return *this;
}

///
/// StartStopWatch::Start().
///
/// Push a timer reading
///

void StartStopWatch::Start()
{
    Timer.push(Now());
}

///
/// StartStopWatch::Stop().
///
/// Calculate elapsed time (destructive)
///

double StartStopWatch::Stop()
{
    if (!Timer.size())
        return 0.0;

    double Delta = Now() - Timer.top();
    Timer.pop();

    return Delta;
}

///
/// StartStopWatch::Elapsed().
///
/// Calculate elapsed time (non-destructive)
///

double StartStopWatch::Elapsed()
{
    if (!Timer.size())
        return 0.0;

    return Now() - Timer.top();
}

///
/// StartStopWatch::uS().
///
/// Dwell for specified number of uS
///

void StartStopWatch::uS(int Delay)
{

    double Then = Now() + static_cast<double>(Delay)/Meg;

    while (Now() < Then)
        ;

}

///
/// StartStopWatch::Mhz().
///
/// Timer clock rate
///

double StartStopWatch::Mhz() const
{
    return impl->TimerRate()/Meg;
}

///
/// StartStopWatch::Now().
///
/// Return current time
///

double StartStopWatch::Now()
{
    return impl->Now();
}


}  //
