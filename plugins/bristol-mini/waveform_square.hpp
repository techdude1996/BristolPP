#pragma once

#include <cmath>

#include "iWaveform.hpp"

namespace bristol
{
    class SquareWaveform : iWaveform
    {
        double Execute(double frequency, double time) override
        {
            return std::sin(FreqToAngVel(frequency) * time) > 0.0 ? 1.0 : -1.0;
        }
    };
}
