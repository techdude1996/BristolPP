/**
 * Minimoog Model D
 *
 * Notes:
 *  - The 3 oscillators are not perfectly in sync, there are some drifts
 *      causing a warm sound.
 *  - The 3rd osc can be an LFO, the new re-make has an independent LFO
 **/

#include <bitset>
#include <array>
#include <chrono>

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

            std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

            /**
                Master Tune

                Controls the offset frequency of the pressed key by +/- 2.5 volts. 
		It is 5 volts per octave, so this is +/- 6 semitones.

                UI Value Range: -2.5 => +2.5 volts

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

                See the docs for the enum for specifics.
            */
            std::uint16_t switches;

            /**
                Oscillator 1 Octave Range Position

                Hold the position of the oscillator 1 range knob.

                This controls what is the fundamental octave for the oscillator.

                UI Value Range: 0.0 => 5.0

                Usage Value Range: 0 => 5 (integer positions)
                
                Scale: Discrete
            */
            int osc1RangePos;

            /**
                Oscillator 1 Waveform Position

                Holds the position of the oscillator 1 waveform knob.

                The waveforms that Oscillator 1 has is:
                0 Triangle
                1 Triangle/Sawtooth Hybrid
                2 Sawtooth
                3 Square (aka Pulse 1)
                4 Wide Rectangle (aka Pulse 2)
                5 Narrow Rectangle (aka Pulse 3)

                Value Range: 0 => 5
            */
            int osc1WaveformPos;

            /**
                Oscillator 2 Octave Range Knob Position

                This controls what is the fundamental octave for the oscillator.

                Range: 0 => 5 (integer positions)
                
                Scale: Discrete
            */
            int osc2RangePos;

            /**
                Oscillator 2 Frequency Offset Knob Position (In Semitones)

                Range: -8.0 => +8.0

                Scale: Linear
            */
            float osc2FrequencyOffsetPos;

            /**
                Oscillator 2 Waveform Knob Position

                The waveforms that Oscillator 2 has is (Same as Oscillator 1):
                0 Triangle
                1 Triangle/Sawtooth Hybrid
                2 Sawtooth
                3 Square (aka Pulse 1)
                4 Wide Rectangle (aka Pulse 2)
                5 Narrow Rectangle (aka Pulse 3)

                Value Range: 0 => 5
            */
            int osc2WaveformPos;

            /**
                Oscillator 3 Octave Range Knob Position

                This controls what is the fundamental octave for the oscillator.

                Range: 0 => 5 (integer positions)
                
                Scale: Discrete
            */
            int osc3RangePos;

            /**
                Oscillator 3 Frequency Offset Knob Position (In Semitones)

                Range: -8.0 => +8.0

                Scale: Linear
            */
            float osc3FrequencyOffsetPos;

            /**
                Oscillator 3 Waveform Knob Position

                The waveforms that Oscillator 3 has is:
                0 Triangle
                1 Reverse Sawtooth (Oscillator 3 exclusive)
                2 Sawtooth
                3 Square (aka Pulse 1)
                4 Wide Rectangle (aka Pulse 2)
                5 Narrow Rectangle (aka Pulse 3)

                Value Range: 0 => 5
            */
            int osc3WaveformPos;

            /**
                Oscillator 1 Volume Knob Position

                Range: 0.0 => 10.0

                Scale: Linear
            */
            float osc1VolPos;

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

            enum SwitchBits : std::uint16_t
            {
                OscillatorModulation = 0b0000000000000001,
                Osc3Control          = 0b0000000000000010,
                Osc1Power            = 0b0000000000000100,
                Osc2Power            = 0b0000000000001000,
                Osc3Power            = 0b0000000000010000,
                ExternInputPower     = 0b0000000000100000,
                NoiseGenPower        = 0b0000000001000000,
                NoiseType            = 0b0000000010000000,
                FilterModEnable      = 0b0000000100000000,
                KeyboardCtl1         = 0b0000001000000000,
                KeyboardCtl2         = 0b0000010000000000,
                A440                 = 0b0000100000000000,
                MainOutput           = 0b0001000000000000
            };

        private:
            // This has to be after the enums
            std::array<float, Parameters::paramCount> fParams;

        public:
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
