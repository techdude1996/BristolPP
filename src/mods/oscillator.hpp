#pragma once
/********************************************************************/
/* References & Notes                                               */
/* https://github.com/OneLoneCoder/synth/blob/master/main2.cpp      */
/********************************************************************/

#include <cmath>

#ifdef BRISTOL_DEBUG
#include <fmt/format.h>
#endif

namespace bristol
{
    /// bristol::WAVEFORM_SHAPE
    /// \brief Shape of the oscillator's waveform
    ///
    enum class WAVEFORM_SHAPE : unsigned short int
    {
        SINE,
        COSINE,
        TRIANGLE,
        SAWTOOTH_QUICK,  /// Less accurate, but faster computationaly
        SAWTOOTH_SLOW,   /// More realistic, but computationaly heavy
        SQUARE
    };

    class Oscillator
    {
        private:
            bristol::WAVEFORM_SHAPE m_currentShape;
            unsigned int m_sawtoothSlowApprox;      // The number of sine waves summed together for the slow model

        public:
            void CurrentWaveform(bristol::WAVEFORM_SHAPE newShape) { m_currentShape = newShape; }
            bristol::WAVEFORM_SHAPE CurrentWaveform() { return m_currentShape; }

            // Temporary function to hold the waveforms
            double TempExec(double frequency, double dTime)
            {
                switch (m_currentShape)
                {
                    case bristol::WAVEFORM_SHAPE::SINE:
                        return std::sin((frequency * 2.0 * 3.141529) * dTime);
                    case bristol::WAVEFORM_SHAPE::COSINE:
                        return std::cos((frequency * 2.0 * 3.141529) * dTime);
                    case bristol::WAVEFORM_SHAPE::SQUARE:
                        return std::sin((frequency * 2.0 * 3.141529) * dTime) > 0 ? 1.0 : -1.0;
                    case bristol::WAVEFORM_SHAPE::TRIANGLE:
                        return std::asin(std::sin((frequency * 2.0 * 3.141529) * dTime)) * (2.0 / 3.141529);
                    case bristol::WAVEFORM_SHAPE::SAWTOOTH_SLOW:
                    {
                        double output = 0.0;
                        for(double i = 1.0; i < (double)m_sawtoothSlowApprox; i++)
                            output += (std::sin(i * (frequency * 2.0 * 3.141529) * dTime)) / i;
                        return output * (2.0 * 3.141529);
                    }
                    case bristol::WAVEFORM_SHAPE::SAWTOOTH_QUICK:
                        return (2.0 / 3.141529) * (frequency * 3.141529 * std::fmod(dTime, 1.0 / frequency) - (3.141529 / 2.0));
                    
                }
                return 0.0;
            }
        
    };  
};

