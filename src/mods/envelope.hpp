#pragma once

#include "units.hpp"

//#ifdef BRISTOL_DEBUG
#include <fmt/format.h>
//#endif

namespace bristol
{
    class Envelope
    {
        private:
            /// Attack Time: The time distance from when the key is pressed to peak amplitude
            /// Must be positive
            bristol::Milliseconds m_attackTime;

            /// Amplitude in which the attack will reach.
            /// This is normally louder than the normal sustaining volume. Once this value has been
            /// reached, the amplitude will decrease to the sustaining amplitude across the decay time.
            bristol::Decibels m_peakAttackAmp;

            /// The duration of the sustain.
            /// Special Values:
            /// <0: Indefinite (until the key is released)
            /// =0: No sustain (like a plucked instrument)
            /// >0: Regular time before natural decay
            bristol::Milliseconds m_sustainTime;

            /// The amplitude during the sustain
            /// This should be less than the peak attack amplitude
            bristol::Decibels m_sustainAmp;

            /// The decay time from the peak attack to the sustain
            bristol::Milliseconds m_decayTime;

            /// The time from the note release till 0db
            bristol::Milliseconds m_releaseTime;

            /// Flag for telling if the note is actively being pressed (used for sustain & release)
            bool m_isActive;

            /// The time which the note was pressed (start the attack phase)
            bristol::Milliseconds m_noteStartTime;

            /// The time which the note was released (start the relase phase)
            bristol::Milliseconds m_noteReleaseTime;
        public:
            Envelope()
            {
            }
            /**
             * Destroy an envelope object
             */
            ~Envelope()
            {
                fmt::print("Destructing Envelope\n");
            }

            // Getters
            bristol::Milliseconds AttackTime() { return m_attackTime; }
            bristol::Milliseconds SustainTime() { return m_sustainTime; }
            bristol::Milliseconds DecayTime() { return m_decayTime; }
            bristol::Milliseconds ReleaseTime() { return m_releaseTime; }

            // Setters
            void AttackTime(bristol::Milliseconds attackTime)
            {
                if(attackTime.m_value >= 0.0)
                    m_attackTime = attackTime;
            }

            void SustainTime(bristol::Milliseconds sustainTime)
            {
                m_sustainTime = sustainTime;
            }

            void DecayTime(bristol::Milliseconds decayTime)
            {
                if(decayTime.m_value > 0.0)
                    m_decayTime = decayTime;
            }

            void Release(bristol::Milliseconds releaseTime)
            {
                if(releaseTime.m_value > 0.0)
                    m_releaseTime = releaseTime;
            }

            bristol::Decibels CurrentAmplitude(bristol::Milliseconds currentTime)
            {
                bristol::Decibels amplitude = 0.0_dB;
                bristol::Milliseconds timePosition = currentTime - m_noteStartTime;

                if(m_isActive)
                {
                    // Attack, Decay, Sustain

                    if(timePosition <= m_attackTime)
                    {
                        // Attack
                        amplitude = (timePosition / m_attackTime) * m_peakAttackAmp;
                    }
                    else if(timePosition > m_attackTime && timePosition <= (m_attackTime + m_decayTime))
                    {
                        // Decay
                        // FIXME
                        amplitude = ((timePosition - m_attackTime) / m_decayTime) * (m_sustainAmp - m_peakAttackAmp) + m_peakAttackAmp;
                    }
                    else if(timePosition > (m_attackTime + m_decayTime) && m_sustainTime != 0.0_ms)
                    {
                        // Sustain
                        if(m_sustainTime > 0.0_ms && timePosition < (m_attackTime + m_decayTime + m_sustainTime))
                        {
                            amplitude = m_sustainAmp;
                        }
                    }
                }
                else
                {
                    // Release
                }

                return amplitude;
            }
    };  
};

