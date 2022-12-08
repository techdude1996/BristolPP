#include <cmath>
#include <cstdint>

namespace bristol
{
    enum MidiStatusType : uint8_t
    {
        NOTE_OFF         = 0x80,
        NOTE_ON          = 0x90,
        AFTER_TOUCH      = 0xA0,
        CC               = 0xB0,
        PATCH_CHANGE     = 0xC0,
        CHANNEL_PRESSURE = 0xD0,
        PITCH_BEND       = 0xE0,
        SYSTEM_MESSAGE   = 0xF0
    };

    enum MidiSystemMessageType : uint8_t
    {
        SYSTEM_MESSAGE_START = 0xF0,
        MIDI_TIME_CODE       = 0xF1,
        SONG_POSITION_PTR    = 0xF2,
        SONG_SELECT          = 0xF3,
        NOT_USED_01          = 0xF4,
        NOT_USED_02          = 0xF5,
        TUNE_REQUEST         = 0xF6,
        SYSTEM_MESSAGE_END   = 0xF7,
        TIMING_CLOCK         = 0xF8,
        START                = 0xFA,
        CONTINUE             = 0xFB,
        STOP                 = 0xFC,
        NOT_USED_03          = 0xFD,
        ACTIVE_SENSING       = 0xFE,
        SYSTEM_RESET         = 0xFF
    };

    constexpr uint8_t GetMidiEventType(const uint8_t &status)
    {
        // Mask away the channel bits
        return status & 0xF0;
    }

    constexpr uint8_t GetMidiEventChannel(const uint8_t &status)
    {
        // Mask away the message type
        return status & 0x0F;
    }

    constexpr double MidiNoteToFrequency(const uint8_t &midiNote, const double &tuning = 440.0)
    {
        double d_midiNote = (double)midiNote;
        return 2.0 * ((d_midiNote - 69.0) / 12.0) * tuning;
    }

    constexpr uint8_t FrequencyToMidiNote(const double &pitch, const double &tuning = 440.0)
    {
        double d_midiNote = 69.0 + 12 * std::log2(pitch / tuning);
        return (uint8_t)d_midiNote;
    }
}
