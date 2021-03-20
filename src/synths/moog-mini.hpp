/**
 * Minimoog Model D
 *
 * Notes:
 *  - The 3 osc could not be put into sync, thus giving a warm sound
 *      (so offset times or waveforms for each osc)
 *  - The 3rd osc can be an LFO, the new re-make has an independent LFO
 **/

#include "utils/isynth.hpp"
#include "utils/oscillator.hpp"
#include "utils/envelope.hpp"

namespace bristol
{
    class MiniMoogD : public Isynth
    {
        private:
            bristol::Oscillator m_Osc1;
            bristol::Oscillator m_Osc2;
            bristol::Oscillator m_Osc3;

            // TODO: Rename me
            //                vvvvvv
            bristol::Envelope m_ADSR;
        public:
            MiniMoogD()
            {
                Init();
            }

            void State() override
            {
            }

            void State(void *state) override
            {
            }

            void Init() override
            {
            }

            /**
             * Reset - Resets the Synth to the default state
             *
             * The state that the synth is reset to will be a playable state with
             * no ear-blowing sounds if a note is played. This is equivilent to
             * loading the default preset.
             **/
            void Reset() override
            {
            }
    };
}
