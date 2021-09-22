#pragma once

namespace bristol
{
    class iWaveform
    {
        public:
            virtual double Execute(double frequency, double time) = 0;
        protected:
            /**
             * Utility function to convert frequency into angular velocity as the trig
             * functions take angular velocity and not frequency.
             **/
            inline double FreqToAngVel(double frequency)
            {
                return frequency * 2.0 * 3.14159265359;
            }
    };
}
