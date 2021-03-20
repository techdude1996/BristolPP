// TODO
// * double + Decibels
namespace bristol
{
    struct Decibels
    {
        double m_value;
        const bristol::Decibels& operator=(const double& b)
        {
            m_value = b;
            return *this;
        }
    };

    struct Milliseconds
    {
        double m_value;
    };

    constexpr Decibels operator"" _dB (long double n)
    {
        return Decibels{(double) n};
    }    

    constexpr Milliseconds operator"" _ms (long double n)
    {
        return Milliseconds{(double) n};
    }    

    /*************************
     * Arithmetic Operators
     *************************/
    inline Decibels operator+ (const bristol::Decibels& a, const bristol::Decibels& b)
    {
        return Decibels{a.m_value + b.m_value};
    }

    inline Decibels operator- (const bristol::Decibels& a, const bristol::Decibels& b)
    {
        return Decibels{a.m_value - b.m_value};
    }

    inline Decibels operator* (const bristol::Decibels& a, const bristol::Decibels& b)
    {
        return Decibels{a.m_value * b.m_value};
    }

    inline Decibels operator/ (const bristol::Decibels& a, const bristol::Decibels& b)
    {
        return Decibels{a.m_value / b.m_value};
    }

    /*************************
     * Comparisons
     *************************/
    inline bool operator< (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return a.m_value < b.m_value;
    }

    inline bool operator<= (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return a.m_value <= b.m_value;
    }

    inline bool operator== (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return a.m_value == b.m_value;
    }

    inline bool operator!= (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return !(a.m_value == b.m_value);
    }

    inline bool operator> (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return !(a <= b);
    }

    inline bool operator>= (const bristol::Decibels &a, const bristol::Decibels& b)
    {
        return !(a < b);
    }

    /*************************
     * Arithmetic w/ Milliseconds
     *************************/

    inline double operator+ (const bristol::Decibels& a, const bristol::Milliseconds& b)
    {
        return a.m_value + b.m_value;
    }

    inline double operator- (const bristol::Decibels& a, const bristol::Milliseconds& b)
    {
        return a.m_value - b.m_value;
    }

    inline double operator* (const bristol::Decibels& a, const bristol::Milliseconds& b)
    {
        return a.m_value * b.m_value;
    }

    inline double operator/ (const bristol::Decibels& a, const bristol::Milliseconds& b)
    {
        return a.m_value / b.m_value;
    }

    /*******************************************************
     * Milliseconds
     *******************************************************/

    /*************************
     * Arithmetic Operators
     *************************/
    inline Milliseconds operator+ (const bristol::Milliseconds& a, const bristol::Milliseconds& b)
    {
        return Milliseconds{a.m_value + b.m_value};
    }

    inline Milliseconds operator- (const bristol::Milliseconds& a, const bristol::Milliseconds& b)
    {
        return Milliseconds{a.m_value - b.m_value};
    }

    inline Milliseconds operator* (const bristol::Milliseconds& a, const bristol::Milliseconds& b)
    {
        return Milliseconds{a.m_value * b.m_value};
    }

    inline Milliseconds operator/ (const bristol::Milliseconds& a, const bristol::Milliseconds& b)
    {
        return Milliseconds{a.m_value / b.m_value};
    }

    /*************************
     * Comparrisons
     *************************/
    inline bool operator< (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return a.m_value < b.m_value;
    }

    inline bool operator<= (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return a.m_value <= b.m_value;
    }

    inline bool operator== (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return a.m_value == b.m_value;
    }

    inline bool operator!= (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return !(a.m_value == b.m_value);
    }

    inline bool operator> (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return !(a <= b);
    }

    inline bool operator>= (const bristol::Milliseconds &a, const bristol::Milliseconds& b)
    {
        return !(a < b);
    }

    struct Hertz
    {
        double m_value;
    };

    /*************************
     * Arithmetic w/ dBs
     *************************/

    inline double operator+ (const bristol::Milliseconds& a, const bristol::Decibels& b)
    {
        return a.m_value + b.m_value;
    }

    inline double operator- (const bristol::Milliseconds& a, const bristol::Decibels& b)
    {
        return a.m_value - b.m_value;
    }

    inline double operator* (const bristol::Milliseconds& a, const bristol::Decibels& b)
    {
        return a.m_value * b.m_value;
    }

    inline double operator/ (const bristol::Milliseconds& a, const bristol::Decibels& b)
    {
        return a.m_value / b.m_value;
    }

    /*******************************************************
     * Frequency (Hertz)
     *******************************************************/
    constexpr Hertz operator"" _Hz (long double n)
    {
        return Hertz{(double) n};
    }
    
    constexpr Hertz operator"" _kHz (long double n)
    {
        return Hertz{(double) n * 1000.0};
    }
};
