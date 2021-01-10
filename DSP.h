// 1/10/2021
// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class also allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#ifndef DSP_H
#define DSP_H

#include <complex>
#define LENGTH 6
using namespace std;


class DSP{
    private:
        double x[LENGTH];
        double h[LENGTH];

    public:
        DSP(double x1[], double h1[]);
        void setX(double x1[]);
        void setH(double h1[]);
        double * getX();
        double * getH();
        complex<double> * DFTX();
        complex<double> * DFTH();
        complex<double> * DFT(double input[]);
        // Calculate each k value one by one. Helper function for the DFT function.
        complex<double> k_value(double input[], double n_vector[], int k);
        // Helper function for the DFT function.
        double * n_vector();
};
#endif // DSP_H