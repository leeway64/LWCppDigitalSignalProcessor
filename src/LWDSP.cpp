// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class then allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#include "LWDSP.hpp"

const double pi = 2 * acos(0.0);
const std::complex<double> j(0,1);

LWDSP::LWDSP() {}

LWDSP::LWDSP(std::vector<double> x, std::vector<double> h): x(x), h(h) {}

LWDSP::LWDSP(const LWDSP& other) {
    *this = other;
}

// Assignment operator
LWDSP& LWDSP::operator=(const LWDSP& other) {
    this->x = other.x;
    this->h = other.h;
    return *this;
}

// Place 2 system impulse functions in parallel with each other
LWDSP& LWDSP::operator||(const LWDSP& other) {
    static LWDSP DSPResult;
    std::vector<double> largest = this->h;
    std::vector<double> smallest = other.h;

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
std::vector<std::complex<double>> LWDSP::DFT(std::vector<double> input) {
    std::vector<std::complex<double>> result;
    const int inputSize = input.size();
    for (int i = 0; i < inputSize; i++) {
        result.push_back(DFTElement(input, angularFrequency(inputSize), i));
    }
    return result;
}

// Calculate each DFT value one by one.Helper function for the DFT function.
std::complex<double> LWDSP::DFTElement(std::vector<double> input, std::vector<double> angularFrequency, int k) {
    std::complex<double> result(0, 0);
    int inputLength = input.size();
    for (int i = 0; i < inputLength; i++) {
        result += std::polar(1.0 * abs(input[i]), (-1.0 * angularFrequency[i] * k) + std::arg(input[i]));
    }
    return result;
}

// Helper function for the DFT function.
std::vector<double> LWDSP::angularFrequency(int inputSize) {
    const double x = 2 * pi / inputSize;
    std::vector<double> result;
    for (int i = 0; i < inputSize; i++) {
        result.push_back(x * i);
    }
    return result;
}
