// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class then allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#include "DSP.h"
#include <complex>
#include <iostream>
using namespace std;


const double pi = 2 * acos(0.0);
const complex<double> j(0,1);

// Default constructor
DSP::DSP() {

}

DSP::DSP(vector<complex<double>> x, vector<complex<double>> h){
    this->x = x;
    this->h = h;
}

// Returns the DFT of the input vector. Output is a vector input.size() long.
vector<complex<double>> DSP::DFT(vector<complex<double>> input) {
    vector<complex<double>> result;
    const int inputSize = input.size();
    for (int i = 0; i < inputSize; i++) {
        result[i] = kValue(input, angularFrequency(inputSize), i);
    }
    return result;
}

// Calculate each k value one by one. Helper function for the DFT function.
complex<double> DSP::kValue(vector<complex<double>> input, vector<double> angularFrequency, int k) {
    complex<double> result(0, 0);
    int inputLength = input.size();
    for (int i = 0; i < inputLength; i++) {
        result += polar(1.0 * abs(input[i]), (-1.0 * angularFrequency[i] * k) + arg(input[i]));
    }
    return result;
}

// Helper function for the DFT function.
vector<double> DSP::angularFrequency(int inputSize) {
    const double x = 2 * pi / inputSize;
    vector<double> result;
    for (int i = 0; i < inputSize; i++) {
        result.push_back(x * i);
    }
    return result;
}
