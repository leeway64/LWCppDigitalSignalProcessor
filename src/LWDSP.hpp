// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class also allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#ifndef DSP_H
#define DSP_H

#include <complex>
#include <vector>

class LWDSP{
    public:
        std::vector<double> x;  // System input signal
        std::vector<double> h;  // System impulse function
        
        // Default constructor. Leaves x and h as empty vectors.
        LWDSP();

        /**
        Constructor that sets x and h equal to the input vectors, x and h
        @param x is the system input signal that member variable x should be set to
        @param h is the system impulse function that member variable h should be set to
        */
        LWDSP(std::vector<double> x, std::vector<double> h);

        /**
        Copy constructor. Initializes a previously uninitialized LWDSP object with a previously
        initialized LWDSP object.
        @param other is the other LWDSP object to initialize this LWDSP object to. Sets this object's x and h
        equal to the other object's x and h.
        */
        LWDSP(const LWDSP& other);

        /**
        Assignment operator. Replaces the member variables of an already initialized LWDSP object
        with the member variables of another initialized LWDSP object.
        @param other is the other LWDSP object to set this LWDSP object to. Replaces the input signal
        and impulse function of a previously initialized LWDSP object with the input signal and
        impulse function of another previously initialized LWDSP object.
        @return A reference to a LWDSP object.
        */
        LWDSP& operator=(const LWDSP& other);

        /**
        Overload for equal to operator.
        @param left is the first LWDSP object to be compared.
        @param right is the second LWDSP object to be compared.
        @return true if the xs and hs for left and right are equal.
        */
        friend bool operator==(const LWDSP& left, const LWDSP& right) {
            return (left.x == right.x) && (left.h == right.h);
        }

        /**
        Overload for not equal to operator.
        @param left is the first LWDSP object to be compared.
        @param right is the second LWDSP object to be compared.
        @return true if either x or h are different from each other, false if not.
        */
        friend bool operator!=(const LWDSP& left, const LWDSP& right) {
            return (left.x != right.x) || (left.h != right.h);
        }

        /**
        Connects 2 system impulse functions in parallel
        @param other is the LWDSP that provides the other impulse function that the impulse function
        of this LWDSP will be in parallel with
        @return A new LWDSP, with an h of the sum of the impulse functions of this and other.
        The x of the new LWDSP is the x of this LWDSP.
        */
        LWDSP& operator||(const LWDSP& other);

        /**
        Returns the DFT of the input vector.
        @param input is the standard vector to find the DFT of.
        @return A standard vector of the DFT of the input vector. The DFT of input will have the same
        length as input.
        */
        static std::vector<std::complex<double>> DFT(std::vector<double> input);
    private:
        /**
        Calculate each DFT value one by one. Helper function for the DFT function.
        @param input is the vector to find the DFT of.
        @param angularFrequency is a vector of angular frequencies. Calculated from the angularFrequency
        function.
        @param k is the index of the DFT element to calculate.
        @return
        */
        static inline std::complex<double> DFTElement(std::vector<double> input, std::vector<double> angularFrequency, int k);

        /**
        Calculates each angular frequency divided by the index of the DFT element. Helper function
        for the DFT function.
        @param inputSize is the size of the input vector to find the DFT of.
        @return A vector inputSize long. Each element in the output is 2pi*index/inputSize.
        */
        static inline std::vector<double> angularFrequency(int inputSize);
};
#endif // DSP_H
