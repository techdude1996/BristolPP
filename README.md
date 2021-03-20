# Bristol++
## C++ port/rewrite of the Bristol Synth emulator

This project is a complete re-write of the Bristol Synthesizer Emulator found here on SourceForge: [Bristol](http://bristol.sourceforge.net/index.html)

## Goals/Reasons
* Use Bristol synths as plugins with a DAW (like Ardour)
    - LV2 support was a large request from the community
    - Build upon an audio plugin framework (currently DISTRHO Plugin Framework)
* Currently, the original source does not compile on some modern systems
* Update the build system from autotools to CMake
* Have each synth stand-alone
* Create synth parts as modules for easy addition of new synths
* The original project has not had an update since 2013

## Current Synths
* MiniMoog (aka Bristol Mini) - WIP
