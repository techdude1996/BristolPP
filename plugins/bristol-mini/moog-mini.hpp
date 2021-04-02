/**
 * Minimoog Model D
 *
 * Notes:
 *  - The 3 osc could not be put into sync, thus giving a warm sound
 *      (so offset times or waveforms for each osc)
 *  - The 3rd osc can be an LFO, the new re-make has an independent LFO
 **/

#include "DistrhoPlugin.hpp"

#include "oscillator.hpp"
#include "envelope.hpp"

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
            MiniMoogD() : Plugin(0, 0, 0)
            {
            }

        protected:
            const char* getLabel() const override
            {
                return "BristolMini";
            }

            const char* getDescription() const override
            {
                return "Bristol synth that emulates the MiniMood D";
            }

            const char* getMaker() const override
            {
                return "Bristol++";
            }

            const char* getHomePage() const override
            {
                return "https://github.com/techdude1996/BristolPP";
            }

            const char* getLicense() const override
            {
                return "GPL-3.0";
            }

            uint32_t getVersion() const override
            {
                return d_version(0, 1, 0);
            }

            int64_t getUniqueId() const override
            {
                // TODO: Need this information
                return d_cconst('d', 'M', 'T', 'r');
            }
                
            void initParameter(uint32_t, Parameter&) override;

            float getParameterValue(uint32_t) const override;

            void setParameterValue(uint32_t, float) override;

            void run(const float**, float**, uint32_t, const MidiEvent*, uint32_t) override;
    };
}
