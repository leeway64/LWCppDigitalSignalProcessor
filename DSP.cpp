// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class then allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#include "DSP.h"
#include <complex>
#include <iostream>
using namespace std;


const double pi = 2 * acos(0.0);
const complex<double> j(0,1);


DSP::DSP(vector<complex<double>> x, vector<complex<double>> h){
    setX(x);
    setH(h);
}

void DSP::setX(vector<complex<double>> x){
    for (int i = 0; i < x.size(); i++){
        this->x[i] = x[i];
    }
}

void DSP::setH(vector<complex<double>> h){
    for (int i = 0; i < h.size(); i++){
        this->h[i] = h[i];
    }
}

vector<complex<double>> DSP::getX() const{
    return x;
}

vector<complex<double>> DSP::getH() const{
    return h;
}

// Returns the DFT of the input vector. Output is a vector input.size() long.
vector<complex<double>> DSP::DFT(vector<complex<double>> input){
    static complex<double> result[LENGTH];
    for (int i = 0; i < LENGTH; i++){
        result[i] = kValue(input, n_vector(), i);
    }
    return result;
}

// Calculate each k value one by one. Helper function for the DFT function.
complex<double> DSP::kValue(vector<complex<double>> input, vector<complex<double>> nVector, int k){
    complex<double> result(0, 0);
    for (int i = 0; i < LENGTH; i++){
        result += polar(1.0 * input[i], -1.0 * nVector[i] * k);
    }
    return result;
}

// Helper function for the DFT function.
vector<complex<double>> DSP::nVector(){
    double x = 2 * pi / LENGTH;
    static double result[LENGTH];
    for (int i = 0; i < LENGTH; i++){
        result[i] = x * i;
    }
    return result;
}
