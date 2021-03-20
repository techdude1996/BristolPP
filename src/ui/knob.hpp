namespace bristol
{
    // This is a template because the values could be either int or floating point
    // Doing it this way avoids casting from double -> int
    template <typename T>
    class Knob
    {
        private:
            void *image;
            T m_regularStepAmount;  // Regular drag
            T m_snapStepAmount;     // Ctrl & drag
            T m_preciseStepAmount;  // Shift & drag
            T m_valMin;
            T m_valMax;
            T m_currentVal;
            // Hold the image rotation amounts for the UI, hence explicit double
            double m_uiMin;
            double m_uiMax;
            double m_currentPos;
    };
}
