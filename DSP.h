// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class also allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#ifndef DSP_H
#define DSP_H

#include <complex>
#include <vector>
using namespace std;

class DSP{
    public:
        vector<complex<double>> x;  // System input signal
        vector<complex<double>> h;  // System impulse function
        
        // Default constructor
        DSP();

        DSP(vector<complex<double>> x, vector<complex<double>> h);

        // Copy constructor. Initializes a previously uninitialized DSP object with a preivously
        // initialized DSP object.
        DSP(const DSP& other);

        // Assignment operator. Replaces the input signal and impulse function of a previously
        // initialized DSP object with the input signal and impulse function of another previously
        // initialized DSP object.
        DSP& operator=(const DSP& other);

        // Returns the DFT of the input vector
        static vector<complex<double>> DFT(vector<complex<double>> input);
    private:
        // Calculate each k value one by one. Helper function for the DFT function.
        static complex<double> kValue(vector<complex<double>> input, vector<double> angularFrequency, int k);

        // Helper function for the DFT function.
        static vector<double> angularFrequency(int inputSize);
};
#endif // DSP_H
