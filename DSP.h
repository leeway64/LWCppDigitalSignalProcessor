// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class also allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#ifndef DSP_H
#define DSP_H

#include <complex>
#include <vector>
using namespace std;

class DSP{
    private:
        vector<complex<double>> x;  // System input signal
        vector<complex<double>> h;  // System impulse function
        
        // Calculate each k value one by one. Helper function for the DFT function.
        static complex<double> kValue(vector<complex<double>> input, vector<double> angularFrequency, int k);

        // Helper function for the DFT function.
        static vector<double> angularFrequency(int inputSize);

    public:
        DSP(vector<complex<double>> x, vector<complex<double>> h);

        void setX(vector<complex<double>> x);

        void setH(vector<complex<double>> h);

        vector<complex<double>> getX() const;

        vector<complex<double>> getH() const;

        // Returns the DFT of the input vector
        static vector<complex<double>> DFT(vector<complex<double>> input);
};
#endif // DSP_H
