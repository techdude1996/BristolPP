#pragma once

#include <cmath>

#include "iWaveform.hpp"

namespace bristol
{
    class SquareWaveform : iWaveform
    {
        float Execute(float frequency, float time) override
        {
            return std::sin((frequency * 2.0f * 3.141529f) * time) > 0.0f ? 1.0f : -1.0f;
        }
    };
}
