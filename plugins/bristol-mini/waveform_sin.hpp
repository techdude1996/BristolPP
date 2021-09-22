#pragma once

#include <cmath>

#include "iWaveform.hpp"

namespace bristol
{
    class SinWaveform : iWaveform
    {
        double Execute(double frequency, double time) override
        {
            return std::sin(FreqToAngVel(frequency) * time);
        }
    };
}
