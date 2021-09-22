#pragma once

#include <cmath>
#include <cstdint>

#include "iWaveform.hpp"

namespace bristol
{
    class SlowSawWaveform : iWaveform
    {
        private:
            std::uint16_t m_sawtoothSlowApprox;
        public:
            SlowSawWaveform(std::uint16_t sawtoothApproxAmount) : m_sawtoothSlowApprox(sawtoothApproxAmount) {}

            void SawtoothApproximation(std::uint16_t amount) { m_sawtoothSlowApprox = amount; }
            std::uint16_t SawtoothApproximation() { return m_sawtoothSlowApprox; }

            double Execute(double frequency, double time) override
            {
                double output = 0.0;
                for(std::uint16_t i = 1; i < m_sawtoothSlowApprox; ++i)
                {
                    double dI = i;
                    output += (std::sin(dI * FreqToAngVel(frequency) *  time)) / dI;
                }
                return output;
            }
    };
}
