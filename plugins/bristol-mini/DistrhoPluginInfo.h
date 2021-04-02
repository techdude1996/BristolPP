#pragma once

#define DISTRHO_PLUGIN_BRAND "Bristol"
#define DISTRHO_PLUGIN_NAME  "Bristol Mini"
#define DISTRHO_PLUGIN_URI   "BristolPP:bristol:mini"

#define DISTRHO_PLUGIN_HAS_UI     1
#define DISTRHO_PLUGIN_IS_RT_SAFE 1
#define DISTRHO_PLUGIN_IS_SYNTH   1 // Auto enables *_WANTS_MIDI_INPUT

#define DISTRHO_PLUGIN_NUM_INPUTS  0
#define DISTRHO_PLUGIN_NUM_OUTPUTS 2 // Maybe we can output stereo?

#define DISTRHO_WANT_TIME_POS 1

#define DISTRHO_UI_USER_RESIZABLE 1
