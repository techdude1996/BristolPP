#pragma once

namespace bristol
{
    class Isynth
    {
        public:
            // Require to be overriden:
            //virtual void fooBar() = 0;
            // Export & Load the synth state
            virtual void State() = 0;
            virtual void State(void *state) = 0;
            virtual void Init() = 0; // Maybe just use constructor
            virtual void Reset() = 0; // Resets to default values (Make sure it's a playable state)
    };
}
