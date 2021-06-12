#include <vector>
#include <iostream>
#include <complex>
#include "catch.hpp"
#include "DSP.h"

using namespace std;

TEST_CASE("Testing constructors", "[Default ctor, construction from vectors, copy ctor, operator=]") {
	vector<complex<double>> v1 = { 1,2,3,4 };
	vector<complex<double>> v2 = { 5,6,7,8 };

	SECTION("Default constructor") {
		DSP DSP1;
		REQUIRE(DSP1.x.empty());
		REQUIRE(DSP1.h.empty());
	}

	SECTION("Construction from vectors") {
		DSP DSP1(v1, v2);
		REQUIRE(DSP1.x == v1);
		REQUIRE(DSP1.h == v2);
	}

	SECTION("Copy constructor") {
		DSP DSP2(v1, v2);
		DSP DSP1(DSP2);
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}

	SECTION("Assignment operator") {
		vector<complex<double>> v3 = { 100, 200, 300, 400, 500, 600, 101010 };
		vector<complex<double>> v4 = { 100, 5050505, 101010 };
		DSP DSP1(v2, v1);
		DSP DSP2(v4, v3);
		DSP1 = DSP2;
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}
}

TEST_CASE("Overloads for equal to/not equal to operators", "[Overloads]") {
	vector<complex<double>> v1 = { 1,2,3,4 };
	vector<complex<double>> v2 = { 5,6,7,8 };
	vector<complex<double>> v3 = { 100, 50505, 1010 };
	DSP DSP1(v1, v2);
	DSP DSP2(v1, v2);
	DSP DSP3(v3, v1);
	REQUIRE(DSP1 == DSP2);
	REQUIRE(DSP3 != DSP1);
}

TEST_CASE("Testing DFT function", "[DFT]") {
	vector<complex<double>> v1 = { 1,2,3,4 };
	vector<complex<double>> v2 = { 5,6,7,8 };
	DSP DSP1;
	
	SECTION("Zero elements in x and h") {
		REQUIRE(DSP::DFT(DSP1.x).empty());
		REQUIRE(DSP::DFT(DSP1.h).empty());
	}

	SECTION("One element in x and h") {
		DSP1.x.push_back(v1[1]);
		DSP1.h.push_back(v1[1]);
		REQUIRE(DSP::DFT(DSP1.x)[0] == v1[1]);
		REQUIRE(DSP::DFT(DSP1.x).size() == 1);

		REQUIRE(DSP::DFT(DSP1.h)[0] == v1[1]);
		REQUIRE(DSP::DFT(DSP1.h).size() == 1);
	}
}
