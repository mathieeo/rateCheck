#include <benchmark.h>
#include <numeric>
#include <algorithm>

namespace rateCheckApp
{
///
/// CLASS AveragedRate.
/// Simple low-pass filtered rate data
///

///
/// constructor for class AveragedRate
///

AveragedRate::AveragedRate(int taps)
    : Taps(taps), History(taps), Cursor(0), LastSample(0.0), Sum(0.0)
{
    Reset();
}

///
/// AveragedRate::Reset().
/// Reset the prams
///

void AveragedRate::Reset()
{
    std::fill(History.begin(), History.end(), 0.0);
    Cursor = 0;
    Settled = false;
    LastSample = 0.0;
    Sum = 0.0;
}

///
/// AveragedRate::Process().
/// Process the average rate from number of recent cached taps
///

double AveragedRate::Process(double sample)
{
    Sum -= History[Cursor];
    Sum += sample;
    History[Cursor++] = sample;
    if (Cursor == Taps)
    {
        Cursor = 0;
        Settled = true;
    }

    return (!Settled) ? 0.0 : Sum/Taps;
}

///
///  AveragedRate::Differential().
/// Set the different sample.
///

double AveragedRate::Differential(double sample)
{
    double result = Process(sample-LastSample);
    LastSample = sample;

    return result;
}

///
/// AveragedRate::Differential().
/// Get the different sample.
///

double AveragedRate::Differential()
{
    return Differential(Rtc.Now());
}

}  // namespace

