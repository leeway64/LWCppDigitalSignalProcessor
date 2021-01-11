// 1/11/2021
// This class allows the user to define an input to a system and a system
// impulse function (x and h, respectively). This class then allows the user to
// perform the discrete Fourier transform (DFT) on x and h.

#include "DSP.h"
#include <complex>
#include <iostream>
using namespace std;


#define LENGTH 6
double pi = 2 * acos(0.0);
complex<double> j(0,1);


DSP::DSP(double x1[], double h1[]){
    setX(x1);
    setH(h1);
}

void DSP::setX(double x1[]){
    for (int i = 0; i < LENGTH; i++){
        x[i] = x1[i];
    }
}

void DSP::setH(double h1[]){
    for (int i = 0; i < LENGTH; i++){
        h[i] = h1[i];
    }
}

double * DSP::getX(){
    return x;
}

double * DSP::getH(){
    return h;
}

// Returns the DFT of x
complex<double> * DSP::DFTX(){
    return DFT(x);
}

// Returns the DFT of h
complex<double> * DSP::DFTH(){
    return DFT(h);
}

// Returns the DFT of the input vector. Output is an array of size LENGTH.
complex<double> * DSP::DFT(double input[]){
    static complex<double> result[LENGTH];
    for (int i = 0; i < LENGTH; i++){
        result[i] = k_value(input, n_vector(), i);
    }
    return result;
}


// Calculate each k value one by one. Helper function for the DFT function.
complex<double> DSP::k_value(double input[], double n_vector[], int k){
    complex<double> result(0, 0);
    for (int i = 0; i < LENGTH; i++){
        result += polar(1.0*input[i], -1.0*n_vector[i]*k);
    }
    return result;
}

// Helper function for the DFT function.
double * DSP::n_vector(){
    double x = 2 * pi / LENGTH;
    static double result[LENGTH];
    for (int i = 0; i < LENGTH; i++){
        result[i] = x * i;
    }
    return result;
}
