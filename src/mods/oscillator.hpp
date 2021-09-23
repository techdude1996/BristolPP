#pragma once
/********************************************************************/
/* References & Notes                                               */
/* https://github.com/OneLoneCoder/synth/blob/master/main2.cpp      */
/********************************************************************/

#include <cmath>

#include "iWaveform.hpp"

namespace bristol
{
    class Oscillator
    {
        private:
            bristol::iWaveform &m_waveform;
            double m_frequency;
            double m_sampleRate;
            double m_phase;

        public:
            Oscillator(bristol::iWaveform &waveform) : m_waveform(waveform) { ResetPhase(); }

            inline void ResetPhase() { m_phase = 0.0; }

            inline void NudgePhase()
            {
                m_phase += m_frequency / m_sampleRate;
                if(m_phase >= 1.0)
                    m_phase -= 1.0;
            }

            void   Waveform(bristol::iWaveform &waveform) { m_waveform = waveform; }

            void   Frequency(double frequency)            { m_frequency = frequency; }
            double Frequency()                            { return m_frequency; }

            void   SampleRate(double sampleRate)          { m_sampleRate = sampleRate; }
            double SampleRate()                           { return m_sampleRate; }

            double Execute()
            {
                double out = m_waveform.Execute(m_frequency, m_phase);
                NudgePhase();
                return out;
            }
/**
            // Temporary function to hold the waveforms
            double TempExec(double frequency, double dTime)
            {
                m_waveform.execute(frequency, dTime);
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
**/        
    };  
};
