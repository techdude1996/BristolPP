/**
 * Minimoog Model D
 *
 * Notes:
 *  - The 3 osc could not be put into sync, thus giving a warm sound
 *      (so offset times or waveforms for each osc)
 *  - The 3rd osc can be an LFO, the new re-make has an independent LFO
 **/

#include <bitset>

#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"
#include "DistrhoUtils.hpp"

#include "envelope.hpp"
#include "noise.hpp"
#include "oscillator.hpp"

namespace bristol
{
    class MiniMoogD : public DISTRHO::Plugin
    {
        private:
            // Modules
            bristol::Oscillator m_Osc1;
            bristol::Oscillator m_Osc2;
            bristol::Oscillator m_Osc3;
            bristol::Oscillator m_Lfo;  // Not sure if keeping this. Only the re-release has a dedicated LFO
            bristol::Envelope m_envelopeFilter;
            bristol::Envelope m_envelopeMod;
            bristol::Noise m_noiseGen;

            // Parameters

            /**
                Master Tune

                Controls the offset frequency of the pressed key by +/- 2.5 somethings. 
                I'm not sure if this is in semitones, like the other 2 oscillators' frequency
                knobs, or some other obscure range.

                UI Value Range: -2.5 => +2.5 semitones (ATM)

                Scale: Linear
                
                So, apparently the range of a modified version is +/- 12 semitones (12 up and 12 down).
                TODO: Discuss what the range should be
             */
            float masterTune;

            /**
                Glide Amount

                Controls the amount of time needed to move from note-to-note.
                The actual time represented by the 1-10 display is from 1 milliseconds
                to 10 seconds.

                UI Value Range: 0.0 => 10.0

                Usage Value Range: 1.0 milliseconds => 10 seconds

                Scale: Linear
            */
            float glideAmount;

            /**
                Modulation Mix

                Controls how much of Oscillator 3 and the Noise Generator is used for the
                modulation source. Really, this is just a percentage of how much the Noise
                Generator is contributing from 0% => 100%

                UI Value Range: 0.0 => 10.0

                Usage Value Range: 0.0 => 1.0 (percentage)

                Scale: Linear
            */
            float modulationMix;

            /**
                Switch Values

                Holds the values of the 15 usable switches in a space efficieny mannor.

                See the docs for the enum for specifics.
            */
            std::bitset<15> switches;

        public:
            enum Parameters
            {
                // Controllers

                /** Master tuning control for Oscillator 1 */
                paramTune = 0,

                /** The time it takes to glide from one note to another */
                paramGlide,

                /** The amount of the modulation source from oscillator 3 and the noise generator */
                paramModMix,

                /** Enables/Disables the modulation of oscillators 1 and 2 by oscillator 3 */
                paramOscModSwitch,
                
                // Osc Bank

                /** The octave set for oscillator 1 */
                paramOsc1Range,

                /** The waveform for oscillator 1 */
                paramOsc1Waveform,

                /** The octave set for oscillator 2 */
                paramOsc2Range,

                /** The frequency offset from the played note */
                paramOsc2Frequency,

                /** The waveform for oscillator 2 */
                paramOsc2Waveform,

                /** Enables/Disables oscillator 3 from keyboard control */
                paramOsc3CtlSwitch,

                /** The octave set for oscillator 3 */
                paramOsc3Range,

                /** The frequency offset from the played note */
                paramOsc3Frequency,

                /** The waveform for oscillator 3 */
                paramOsc3Waveform,

                //Mixer
                
                /** Enables/Disables the output of Oscillator 1 */
                paramOsc1MixSwitch,

                /** The volume control for Oscillator 1 */
                paramOsc1Volume,

                /** Enables/Disables the output of Oscillator 2 */
                paramOsc2MixSwitch,

                /** The volume control for Oscillator 2 */
                paramOsc2Volume,

                /** Enables/Disables the output of Oscillator 3 */
                paramOsc3MixSwitch,

                /** The volume control for Oscillator 3 */
                paramOsc3Volume,

                /** Enables/Disables the output of the external audio signal */
                paramExtInputMixSwitch,

                /** The volume control for the external audio signal */
                paramExtInputVolume,

                /** Enables/Disables the output of the noise generator */
                paramNoiseMixSwitch,

                /** The volume control for the noise generator */
                paramNoiseVolume,

                /** The type of noise generated, whether white (pink) or pink (red) */
                paramNoiseTypeSwitch,

                // Modifiers - Switches
                
                /** Enables/Disables the modulation of the Filter Cutoff Frequency */
                paramFilterModSwitch,

                /** Enables/Disables 1/3 keytrack capabilities to the Filter Cutoff Frequency */
                paramKeyboardCtl1Switch,

                /** Enables/Disables 2/3 keytrack capabilities to the Filter Cutoff Frequency */
                paramKeyboardCtl2Switch,

                // Modifiers - Frequency Filter Envelope

                /** Sets the Cutoff Frequency for the Ladder Filter */
                paramCutoffFreq,

                /** Controls how much of the Ladder Filter's output is routed back into the filter */
                paramEmphasis,

                /** Controls how much over the Filter's frequency setting is reached by the attack */
                paramContourAmount,

                /** Controls how fast the filter's frequency cutoff is raised */
                paramAttackTime,

                /** Controls how fast the filter frequency cutoff falls to sustain level, or manual setting */
                paramDecayTime,

                /** The frequency the filter frequency cutoff wil be while a key is held */
                paramSustainLevel,

                // Modifiers - Loudness Contour
                
                /** Controls how fast the volume is raised to maximum */
                paramLoudnessAttackTime,

                /** Controls how fast the volume falls to sustain level */
                paramLoudnessDecayTime,

                /** The volume to hold while a key is held */
                paramLoudnessSustainLevel,

                // Output
                
                /** The overall output volume of the synth */
                paramMainVolumeOut,

                /** Enables/Disables the main output */
                paramMainVolumeSwitch,

                /** Enables/Disables a constant A-440 tone */
                paramA440Switch,

                /** The output volume for the headphones/monitor output */
                paramPhonesVolumeOut,

                /** The amount of bending in the pitch of the played note */
                paramPitchBendWheel,

                /** The amount of modulation */
                paramModWheel,

                /** DISTRHO Required - holds the number of parameters for the synth */
                paramCount
            };

            enum SwitchBits : std::size_t
            {
                OscillatorModulation = 0,
                Osc3Control,
                Osc1Power,
                Osc2Power,
                Osc3Power,
                ExternInputPower,
                NoiseGenPower,
                NoiseType,
                FilterModEnable,
                KeyboardCtl1,
                KeyboardCtl2,
                A440,
                MainOutput
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

            void run(const float**, float**, uint32_t, const MidiEvent*, uint32_t);
    };

    Plugin* createPlugin()
    {
        return new bristol::MiniMoogD();
        
    }
        
}
