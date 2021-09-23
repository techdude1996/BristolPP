#include "moog-mini.hpp"
#include "DistrhoPlugin.hpp"

bristol::MiniMoogD::MiniMoogD() : Plugin(Parameters::paramCount, 1, 0)
{
    // TODO
    // Init oscs, envs, etc. here
    // loadProgram(0);
}

bristol::MiniMoogD::~MiniMoogD()
{
    // TODO: de-allocate anything allocated
}

void bristol::MiniMoogD::initParameter(uint32_t index, Parameter &parameter)
{
    if (index >= Parameters::paramCount)
        return;

    switch (index)
    {
        case Parameters::paramTune:
            parameter.ranges.min = -2.5f;
            parameter.ranges.max = 2.5f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Tune";
            parameter.symbol = "tune";
            parameter.description = "Changes the tuning of Oscillator 1.";
            break;

        case Parameters::paramGlide:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Glide";
            parameter.symbol = "glide";
            parameter.description = "Time it takes to glide between notes.";
            break;

        case Parameters::paramModMix:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Modulation Mix";
            parameter.symbol = "ModMix";
            parameter.description = "Amount of modulation that goes to either "
                "Oscillator 3 and the Noise generator";
            break;

        case Parameters::paramOscModSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Oscillator Modulation";
            parameter.shortName = "Osc Mod";
            parameter.symbol = "OscModSwitch";
            parameter.description = "Allows the oscillators to be modulated.";
            break;

        case Parameters::paramOsc1Range:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 3.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 1 Range";
            parameter.shortName = "Osc 1 Rng";
            parameter.symbol = "Osc1Range";
            parameter.description =
                "The octave the oscillator plays in, with LO being for LFO.";
            break;

        case Parameters::paramOsc1Waveform:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 1 Waveform";
            parameter.shortName = "Osc 1 Shape";
            parameter.symbol = "Osc1Waveform";
            parameter.description = "Waveform of Oscillator 1.";
            break;

        case Parameters::paramOsc2Range:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 3.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 2 Range";
            parameter.shortName = "Osc 2 Rng";
            parameter.symbol = "Osc2Range";
            parameter.description =
                "The octave the oscillator plays in, with LO being for LFO.";
            break;

        case Parameters::paramOsc2Frequency:
            parameter.ranges.min = -8.0f;
            parameter.ranges.max = 8.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Oscillator 2 Frequency";
            parameter.shortName = "Osc 2 Freq";
            parameter.symbol = "Osc2Freq";
            parameter.description =
                "The frequency offset from Oscillator 1 in semitones.";
            break;

        case Parameters::paramOsc2Waveform:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 2 Waveform";
            parameter.shortName = "Osc 2 Shape";
            parameter.symbol = "Osc2Waveform";
            parameter.description = "Waveform of Oscillator 2.";
            break;

        case Parameters::paramOsc3CtlSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Oscillator 3 Control";
            parameter.shortName = "Osc 3 Ctl";
            parameter.symbol = "Osc3CtlSwitch";
            parameter.description = "Releases oscillator 3 from keyboard control to be "
                "used as modulation source.";
            break;

        case Parameters::paramOsc3Range:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 3.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 3 Range";
            parameter.shortName = "Osc 3 Rng";
            parameter.symbol = "Osc3Range";
            parameter.description =
                "The octave the oscillator plays in, with LO being for LFO.";
            break;

        case Parameters::paramOsc3Frequency:
            parameter.ranges.min = -8.0f;
            parameter.ranges.max = 8.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Oscillator 3 Frequency";
            parameter.shortName = "Osc 3 Freq";
            parameter.symbol = "Osc3Freq";
            parameter.description =
                "The frequency offset from Oscillator 1 in semitones.";
            break;

        case Parameters::paramOsc3Waveform:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsInteger;
            parameter.name = "Oscillator 3 Waveform";
            parameter.shortName = "Osc 3 Shape";
            parameter.symbol = "Osc3Waveform";
            parameter.description = "Waveform of Oscillator 3.";
            break;

        case Parameters::paramOsc1MixSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Oscillator 1 Switch";
            parameter.shortName = "Osc 1 Switch";
            parameter.symbol = "Osc1Sw";
            parameter.description = "Turns the oscillator on or off for output.";
            break;

        case Parameters::paramOsc1Volume:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Oscillator 1 Volume";
            parameter.shortName = "Osc 1 Vol";
            parameter.symbol = "Osc1Volume";
            parameter.description = "The output volume of the oscillator.";
            break;

        case Parameters::paramOsc2MixSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Oscillator 2 Switch";
            parameter.shortName = "Osc 2 Switch";
            parameter.symbol = "Osc2Sw";
            parameter.description = "Turns the oscillator on or off for output.";
            break;

        case Parameters::paramOsc2Volume:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Oscillator 2 Volume";
            parameter.shortName = "Osc 2 Vol";
            parameter.symbol = "Osc2Volume";
            parameter.description = "The output volume of the oscillator.";
            break;

        case Parameters::paramOsc3MixSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Oscillator 3 Switch";
            parameter.shortName = "Osc 3 Switch";
            parameter.symbol = "Osc3Sw";
            parameter.description = "Turns the oscillator on or off for output.";
            break;

        case Parameters::paramOsc3Volume:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Oscillator 3 Volume";
            parameter.shortName = "Osc 3 Vol";
            parameter.symbol = "Osc3Volume";
            parameter.description = "The output volume of the oscillator.";
            break;

        case Parameters::paramExtInputMixSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "External Input Switch";
            parameter.shortName = "Ext Switch";
            parameter.symbol = "ExtSw";
            parameter.description =
                "Turns the external audio input on or off for output.";
            break;

        case Parameters::paramExtInputVolume:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "External Input Volume";
            parameter.shortName = "Ext Vol";
            parameter.symbol = "ExtVolume";
            parameter.description = "The output volume of the external audio input.";
            break;

        case Parameters::paramNoiseMixSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Noise Switch";
            parameter.symbol = "NoiseSw";
            parameter.description = "Turns the noise generator on or off for output.";
            break;

        case Parameters::paramNoiseVolume:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Noise Volume";
            parameter.shortName = "Noise Vol";
            parameter.symbol = "NoiseVolume";
            parameter.description = "The output volume of the noise generator.";
            break;

        case Parameters::paramNoiseTypeSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Noise Type Switch";
            parameter.shortName = "Noise Type";
            parameter.symbol = "NoiseType";
            parameter.description =
                "The type of noise. White is actually Pink, and Pink is actually Red.";
            break;

        case Parameters::paramFilterModSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Filter Modulation";
            parameter.shortName = "Filter Mod";
            parameter.symbol = "FilterModulation";
            parameter.description = "Allows modulation of the Filter Cutoff Frequency.";
            break;

        case Parameters::paramKeyboardCtl1Switch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Key Tracking 1";
            parameter.shortName = "Key track 1";
            parameter.symbol = "KeyTrack1";
            parameter.description = "Enables 1/3rd key tracking.";
            break;

        case Parameters::paramKeyboardCtl2Switch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name = "Key Tracking 2";
            parameter.shortName = "Key track 2";
            parameter.symbol = "KeyTrack2";
            parameter.description = "Enables 2/3rd key tracking.";
            break;

        case Parameters::paramCutoffFreq:
            parameter.ranges.min = -5.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Cuttoff Frequency";
            parameter.shortName = "Cuttoff Freq";
            parameter.symbol = "CuttoffFrequency";
            parameter.description = "Frequency that will be reduced at 24db/Octave.";
            break;

        case Parameters::paramEmphasis:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 5.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Emphasis";
            parameter.symbol = "Emphasis";
            parameter.description = "Amount of filter output routed back into the filter, creates resonance.";
            break;

        case Parameters::paramContourAmount:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 5.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Contour Amount";
            parameter.shortName = "Contour";
            parameter.symbol = "Contour";
            parameter.description = "The frequency reached by the attack time over the selected frequency.";
            break;

        case Parameters::paramAttackTime:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 35.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsLogarithmic;
            parameter.name = "Attack Time";
            parameter.shortName = "Atk";
            parameter.symbol = "FilterAttackTime";
            parameter.description = "Time to raise the filter's cutoff frequency + the contour amount.";
            break;

        case Parameters::paramDecayTime:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 35.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsLogarithmic;
            parameter.name = "Decay Time";
            parameter.shortName = "Decay";
            parameter.symbol = "FilterDecayTime";
            parameter.description = "Time to lower the filter's cutoff frequency to the selected frequency or the sustain level.";
            break;

        case Parameters::paramSustainLevel:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Sustain Level";
            parameter.shortName = "Sustain";
            parameter.symbol = "FilterSustainLevel";
            parameter.description = "Frequency the filter will be while a key is held.";
            break;

        case Parameters::paramLoudnessAttackTime:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 35.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsLogarithmic;
            parameter.name = "Attack Time";
            parameter.shortName = "Atk";
            parameter.symbol = "LoudnessAttackTime";
            parameter.description = "Time to raise the volume to max.";
            break;

        case Parameters::paramLoudnessDecayTime:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 35.0f;
            parameter.hints = kParameterIsAutomable | kParameterIsLogarithmic;
            parameter.name = "Decay Time";
            parameter.shortName = "Decay";
            parameter.symbol = "LoudnessDecayTime";
            parameter.description = "Time to lower the volume to sustain level/fall off.";
            break;

        case Parameters::paramLoudnessSustainLevel:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Sustain Level";
            parameter.shortName = "Sustain";
            parameter.symbol = "LoudnessSustainLevel";
            parameter.description = "Volume to hold while key is pressed.";
            break;

        case Parameters::paramMainVolumeOut:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 2.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Volume";
            parameter.shortName = "Volume";
            parameter.symbol = "MainVolumeOut";
            parameter.description = "The main synth output volume.";
            break;

        case Parameters::paramMainVolumeSwitch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.hints = kParameterIsBoolean | kParameterIsAutomable;
            parameter.name = "Main Output";
            parameter.shortName = "Output";
            parameter.symbol = "MainOutputSwitch";
            parameter.description = "Turns the main output on or off.";
            break;

        case Parameters::paramA440Switch:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsBoolean | kParameterIsAutomable;
            parameter.name = "A-440";
            parameter.shortName = "A440";
            parameter.symbol = "A440Switch";
            parameter.description =
                "Sends a solid pitch of 440 (A) out to tune oscillators";
            break;

        case Parameters::paramPhonesVolumeOut:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 10.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Headphone Volume";
            // TODO: Add short name
            parameter.shortName = "";
            parameter.description = "Amount of additional gain to the headphones output.";
            break;

        case Parameters::paramPitchBendWheel:
            parameter.ranges.min = -5.0f;
            parameter.ranges.max = 5.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomable;
            parameter.name = "Pitch";
            parameter.shortName = "Pitch";
            parameter.symbol = "PitchBendWheel";
            parameter.description = "Bends the pitch of all oscillators.";
            break;

        case Parameters::paramModWheel:
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.name = "Mod";
            parameter.shortName = "Mod";
            parameter.symbol = "ModWheel";
            parameter.description = "Controls the amount of modulation from 0% - 100%";
            break;

        default:
            break;
    }
}

float bristol::MiniMoogD::getParameterValue(uint32_t paramID) const
{
    if(paramID < Parameters::paramCount)
        return fParams[paramID];

    // If for some reason something invalid is given, the expected result is 0
    return 0.0f;
}

void bristol::MiniMoogD::setParameterValue(uint32_t paramID, float value)
{
    if(paramID < Parameters::paramCount)
    {
        // Keep the original value in case the new one is invalid
        // and the change request needs to be ignored.
        float oldValue = fParams[paramID];

        fParams[paramID] = value;

        switch(paramID)
        {
            case Parameters::paramTune:
                break;
            case Parameters::paramGlide:
                break;
            case Parameters::paramModMix:
                break;
            case Parameters::paramOscModSwitch:
                // If the above is not true, use this
                if(value)
                    switches |= SwitchBits::OscillatorModulation;
                else
                    switches &= ~(SwitchBits::OscillatorModulation);
                break;
            case Parameters::paramOsc1Range:
                break;
            case Parameters::paramOsc1Waveform:
                break;
            case Parameters::paramOsc2Range:
                break;
            case Parameters::paramOsc2Frequency:
                break;
            case Parameters::paramOsc2Waveform:
                break;
            case Parameters::paramOsc3CtlSwitch:
                break;
            case Parameters::paramOsc3Range:
                break;
            case Parameters::paramOsc3Frequency:
                break;
            case Parameters::paramOsc3Waveform:
                break;
            case Parameters::paramOsc1MixSwitch:
                break;
            case Parameters::paramOsc1Volume:
                break;
            case Parameters::paramOsc2MixSwitch:
                break;
            case Parameters::paramOsc2Volume:
                break;
            case Parameters::paramOsc3MixSwitch:
                break;
            case Parameters::paramOsc3Volume:
                break;
            case Parameters::paramExtInputMixSwitch:
                break;
            case Parameters::paramExtInputVolume:
                break;
            case Parameters::paramNoiseMixSwitch:
                break;
            case Parameters::paramNoiseVolume:
                break;
            case Parameters::paramNoiseTypeSwitch:
                break;
            case Parameters::paramFilterModSwitch:
                break;
            case Parameters::paramKeyboardCtl1Switch:
                break;
            case Parameters::paramKeyboardCtl2Switch:
                break;
            case Parameters::paramCutoffFreq:
                break;
            case Parameters::paramEmphasis:
                break;
            case Parameters::paramContourAmount:
                break;
            case Parameters::paramAttackTime:
                break;
            case Parameters::paramDecayTime:
                break;
            case Parameters::paramSustainLevel:
                break;
            case Parameters::paramLoudnessAttackTime:
                break;
            case Parameters::paramLoudnessDecayTime:
                break;
            case Parameters::paramLoudnessSustainLevel:
                break;
            case Parameters::paramMainVolumeOut:
                break;
            case Parameters::paramMainVolumeSwitch:
                break;
            case Parameters::paramA440Switch:
                break;
            case Parameters::paramPhonesVolumeOut:
                break;
            case Parameters::paramPitchBendWheel:
                break;
            case Parameters::paramModWheel:
                break;
            default:
                // Error, should not get here
                break;
        }
    }
}

void bristol::MiniMoogD::run(const float **, float **outputs, uint32_t frames,
        const MidiEvent *midiEvents,
        uint32_t midiEventCount)
{
    float *const outL = outputs[0];
    float *const outR = outputs[1];

    //TimePosition time = getTimePosition();

    // Main loop
    for (uint32_t count, pos = 0, curEventIndex = 0; pos < frames;)
    {
        for (; curEventIndex < midiEventCount && pos >= midiEvents[curEventIndex].frame; ++curEventIndex)
        {
            if (midiEvents[curEventIndex].size > MidiEvent::kDataSize)
            {
                continue;
            }

            const std::uint8_t* data = midiEvents[curEventIndex].data;

            // TODO: Ask Falk about this black magic
            // and status codes
            const std::uint8_t status = data[0] & 0xF0;

            switch (status)
            {
                // Key toggle?
                case 0x90:
                    const std::uint8_t note     = data[1];
                    const std::uint8_t velocity = data[2];

                    if (note < 128)
                    {
                        return;
                    }
                    else if (velocity > 0)
                    {
                        m_Osc1.Frequency(440.0f * std::pow(2.0f, (float)(note - 69)/12.0f));

                        float val = (float)m_Osc1.Execute();
                    }
            }

        }
    }
}
