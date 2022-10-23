#ifndef Benchmark_MbH
#define Benchmark_MbH

#include <vector>
#include <start_stop_watch.h>

namespace rateCheckApp
{
#ifdef __CLR_VER
#pragma managed(push, off)
#endif

//===========================================================================
//  CLASS AveragedRate  -- Simple low-pass filtered rate data
//===========================================================================

class AveragedRate
{
public:
    AveragedRate(int taps=20);

    // Methods
    void   Reset();
    double Process(double sample);
    double Differential(double sample);
    double Differential();

private:
    // Data
    unsigned int			Taps;
    std::vector<double>		History;
    unsigned int			Cursor;
    bool                    Settled;
    double					LastSample;
    double                  Sum;
    rateCheckApp::StartStopWatch   Rtc;
};

#ifdef __CLR_VER
#pragma managed(pop)
#endif
}  // namespace

#endif
