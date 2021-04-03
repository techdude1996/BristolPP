#pragma once

#include <random>

/*******************************************************************************
Noise needed:
    - White
    - Pink
    - Red
    - Brown?

General idea for usage:
iNoiseGenerator foo = WhiteNoise(someSeedValueHere?);

The interface base class iNoiseGenerator provides a common interface for all
the noise algorithms to be used by, allowing for (hopefully) easy algorithm
switching.
********************************************************************************/

namespace bristol
{
    class iNoiseGenerator
    {
        public:
            virtual void Init() = 0;
            virtual double GetNextValue() = 0;
    };

    class WhiteNoise : public iNoiseGenerator
    {
        public:
            void Init() override
            {
            }

            double GetNextValue() override
            {
                return 0.0;
            }
    };

    class PinkNoise : public iNoiseGenerator
    {
        public:
            void Init() override
            {
            }

            double GetNextValue() override
            {
                return 0.0;
            }
    };

    class RedNoise : public iNoiseGenerator
    {
        public:
            void Init() override
            {
            }

            double GetNextValue() override
            {
                return 0.0;
            }
    };
};
