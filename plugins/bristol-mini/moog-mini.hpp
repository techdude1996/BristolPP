/**
 * Minimoog Model D
 *
 * Notes:
 *  - The 3 osc could not be put into sync, thus giving a warm sound
 *      (so offset times or waveforms for each osc)
 *  - The 3rd osc can be an LFO, the new re-make has an independent LFO
 **/

#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"

#include "envelope.hpp"
#include "noise.hpp"
#include "oscillator.hpp"

namespace bristol
{
    class MiniMoogD : public Plugin
    {
        private:
            bristol::Oscillator m_Osc1;
            bristol::Oscillator m_Osc2;
            bristol::Oscillator m_Osc3;
            bristol::Oscillator m_Lfo;  // Not sure if keeping this. Only the re-release has a dedicated LFO
            bristol::Envelope m_envelopeFilter;
            bristol::Envelope m_envelopeMod;
            bristol::Noise m_noiseGen;

        public:
            enum Parameters
            {
                // Controllers
                paramTune = 0,
                paramGlide,
                paramModMix,
                paramOscModSwitch,
                // Osc Bank
                paramOsc1Range,
                paramOsc1Waveform,
                paramOsc2Range,
                paramOsc2Frequency,
                paramOsc2Waveform,
                paramOsc3CtlSwitch,
                paramOsc3Range,
                paramOsc3Frequency,
                paramOsc3Waveform,
                //Mixer
                paramOsc1MixSwitch,
                paramOsc1Volume,
                paramOsc2MixSwitch,
                paramOsc2Volume,
                paramOsc3MixSwitch,
                paramOsc3Volume,
                paramExtInputMixSwitch,
                paramExtInputVolume,
                paramNoiseMixSwitch,
                paramNoiseVolume,
                paramNoiseTypeSwitch,
                // Modifiers - Switches
                paramFilterModSwitch,
                paramKeyboardCtl1Switch,
                paramKeyboardCtl2Switch,
                // Modifiers - Frequency Filter Envelope
                paramCutoffFreq,
                paramEmphasis,
                paramContourAmount,
                paramAttackTime,
                paramDecayTime,
                paramSustainLevel,
                // Modifiers - Loudness Contour
                paramLoudnessAttackTime,
                paramLoudnessDecayTime,
                paramLoudnessSustainLevel,
                // Output
                paramMainVolumeOut,
                paramMainVolumeSwitch,
                paramA440Switch,
                paramPhonesVolumeOut,
                paramPitchBendWheel,
                paramModWheel,
                paramCount
            };

            MiniMoogD();
            ~MiniMoogD();

        protected:
            /*
             * DISTRHO Informational Callbacks
             */
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
              
            /*
             * DISTRHO Plugin Callbacks
             */
            void initParameter(uint32_t, Parameter&) override;

            float getParameterValue(uint32_t) const override;

            void setParameterValue(uint32_t, float) override;

            void run(const float**, float**, uint32_t, const MidiEvent*, uint32_t) override;
    };

    Plugin* createPlugin()
    {
        return new bristol::MiniMoogD();
        
    }
        
}
