// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class then allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#include "DSP.hpp"
#include <complex>
#include <iostream>
using namespace std;


const double pi = 2 * acos(0.0);
const complex<double> j(0,1);

DSP::DSP() {}

DSP::DSP(vector<double> x, vector<double> h): x(x), h(h) {}

DSP::DSP(const DSP& other) {
    *this = other;
}

// Assignment operator
DSP& DSP::operator=(const DSP& other) {
    this->x = other.x;
    this->h = other.h;
    return *this;
}

// Place 2 system impulse functions in parallel with each other
DSP& DSP::operator||(const DSP& other) {
    static DSP DSPResult;
    vector<double> largest = this->h;
    vector<double> smallest = other.h;

    if (other.h.size() > this->h.size()) {
        largest = other.h;
        smallest = this->h;
    }

    for (auto n = 0; n < smallest.size(); ++n) {
        largest[n] = smallest[n] + largest[n];
    }

    DSPResult.h = largest;
    DSPResult.x = this->x;

    return DSPResult;
}

// Returns the DFT of the input vector. Output is a vector input.size() long.
vector<complex<double>> DSP::DFT(vector<double> input) {
    vector<complex<double>> result;
    const int inputSize = input.size();
    for (int i = 0; i < inputSize; i++) {
        result.push_back(DFTElement(input, angularFrequency(inputSize), i));
    }
    return result;
}

// Calculate each DFT value one by one.Helper function for the DFT function.
complex<double> DSP::DFTElement(vector<double> input, vector<double> angularFrequency, int k) {
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
