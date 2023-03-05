#ifndef DSP_H
#define DSP_H

#include <complex>
#include <vector>
#include <numbers>

const std::complex<double> j(0,1);


// LWDSP allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class also allows the user to
// perform the discrete Fourier transform (DFT) on x and h.
template <class T>
class LWDSP {
    public:
        std::vector<T> x;  // System input signal
        std::vector<T> h;  // System impulse function
        
        // Default constructor. Leaves x and h as empty vectors.
        LWDSP();

        /**
        Constructor that sets x and h equal to the input vectors, x and h
        @param x is the system input signal that member variable x should be set to
        @param h is the system impulse function that member variable h should be set to
        */
        LWDSP(std::vector<T> x, std::vector<T> h);

        /**
        Copy constructor. Initializes a previously uninitialized LWDSP object with a previously
        initialized LWDSP object.
        @param other is the other LWDSP object to initialize this LWDSP object to. Sets this object's x and h
        equal to the other object's x and h.
        */
        LWDSP(const LWDSP<T>& other);

        /**
        Assignment operator. Replaces the member variables of an already initialized LWDSP object
        with the member variables of another initialized LWDSP object.
        @param other is the other LWDSP object to set this LWDSP object to. Replaces the input signal
        and impulse function of a previously initialized LWDSP object with the input signal and
        impulse function of another previously initialized LWDSP object.
        @return A reference to a LWDSP object.
        */
        LWDSP<T>& operator=(const LWDSP<T>& other);

        /**
        Overload for equal to operator.
        @param left is the first LWDSP object to be compared.
        @param right is the second LWDSP object to be compared.
        @return true if the xs and hs for left and right are equal.
        */
        friend bool operator==(const LWDSP<T>& left, const LWDSP<T>& right) {
            return (left.x == right.x) && (left.h == right.h);
        }

        /**
        Overload for not equal to operator.
        @param left is the first LWDSP object to be compared.
        @param right is the second LWDSP object to be compared.
        @return true if either x or h are different from each other, false if not.
        */
        friend bool operator!=(const LWDSP<T>& left, const LWDSP<T>& right) {
            return (left.x != right.x) || (left.h != right.h);
        }

        /**
        Connects 2 system impulse functions in parallel
        @param other is the LWDSP that provides the other impulse function that the impulse function
        of this LWDSP will be in parallel with
        @return A new LWDSP, with an h of the sum of the impulse functions of this and other.
        The x of the new LWDSP is the x of this LWDSP.
        */
        LWDSP<T>& operator||(const LWDSP<T>& other);

        /**
        Returns the DFT of the input vector.
        @param input is the standard vector to find the DFT of.
        @return A standard vector of the DFT of the input vector. The DFT of input will have the same
        length as input.
        */
        static std::vector<std::complex<double>> DFT(std::vector<T> input);
};


template <class T>
LWDSP<T>::LWDSP(){}

template <class T>
LWDSP<T>::LWDSP(std::vector<T> x, std::vector<T> h): x(x), h(h) {}

template <class T>
LWDSP<T>::LWDSP(const LWDSP<T>& other) {
    *this = other;
}

// Assignment operator
template <class T>
LWDSP<T>& LWDSP<T>::operator=(const LWDSP<T>& other) {
    this->x = other.x;
    this->h = other.h;
    return *this;
}

// Place 2 system impulse functions in parallel with each other
template <class T>
LWDSP<T>& LWDSP<T>::operator||(const LWDSP<T>& other) {
    static LWDSP DSPResult;
    std::vector<double> largest = this->h;
    std::vector<double> smallest = other.h;

    if (other.h.size() > this->h.size())
    {
        largest = other.h;
        smallest = this->h;
    }

    for (auto n = 0; n < smallest.size(); ++n)
    {
        largest[n] = smallest[n] + largest[n];
    }

    DSPResult.h = largest;
    DSPResult.x = this->x;

    return DSPResult;
}

// Returns the DFT of the input vector. Output is a vector input.size() long.
template <class T>
std::vector<std::complex<double>> LWDSP<T>::DFT(std::vector<T> input) {
    std::vector<std::complex<double>> result;
    
    const int N = input.size();
    for (int k = 0; k < N; k++)
    {
        std::complex<double> element(0, 0);
        for (int n = 0; n < N; ++n)
        {
            const double knN = 1.0 * k * n / N;
            element += exp(-1.0 * j * 2.0 * std::numbers::pi * knN) * static_cast<double>(input[n]);
        }
        result.push_back(element);
    }
    return result;
}
#endif // DSP_H
