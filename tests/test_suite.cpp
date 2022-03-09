#include <vector>
#include <complex>

#include <Catch2/catch.hpp>

#include "../src/DSP.hpp"

using namespace std;

vector<double> vectorWithSingleValue(int size, int value) {
	vector<double> result;
	for (int i = size; i > 0; --i) {
		result.push_back(value);
	}
	return result;
}

void verifyVector(complex<double> v1, complex<double> v2) {
}

TEST_CASE("Testing constructors", "[Default ctor, construction from vectors, copy ctor, operator=]") {
	vector<double> v1 = { 1,2,3,4 };
	vector<double> v2 = { 5,6,7,8 };

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
		vector<double> v3 = { 100, 200, 300, 400, 500, 600, 101010 };
		vector<double> v4 = { 100, 5050505, 101010 };
		DSP DSP1(v2, v1);
		DSP DSP2(v4, v3);
		DSP1 = DSP2;
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}
}

TEST_CASE("Overloads for equal to/not equal to operators", "[Overloads]") {
	vector<double> v1 = { 1,2,3,4 };
	vector<double> v2 = { 5,6,7,8 };
	vector<double> v3 = { 100, 50505, 1010 };

	DSP DSP1(v1, v2);
	DSP DSP2(v1, v2);
	DSP DSP3(v3, v1);

	REQUIRE(DSP1 == DSP2);
	REQUIRE(DSP3 != DSP1);
}

TEST_CASE("2 systems in parallel", "[Parallel]") {
	vector<double> v1 = { 1,2,3,4 };
	vector<double> v2 = { 5,6,7,8 };
	vector<double> v3 = { 100, 50505, 1010 };

	vector<double> v4 = {10, 12, 14, 16};
	vector<double> v5 = {105, 50511, 1017, 8};
	DSP DSP1(v1, v2);
	DSP DSP2(v1, v2);
	DSP DSP3(v3, v3);

	DSP DSP4 = DSP1 || DSP2;
	REQUIRE(DSP4.x == v1);
	REQUIRE(DSP4.h == v4);

	DSP DSP5 = DSP3 || DSP1;
	REQUIRE(DSP5.x == v3);
	REQUIRE(DSP5.h == v5);
}

TEST_CASE("Basic testing of DFT function", "[DFT]") {
	vector<double> v1 = { 1,2,3,4 };
	vector<double> v2 = { 5,6,7,8 };
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

	SECTION("Constant values in x and h") {
		int size1 = 4;
		int size2 = 10;
		int value1 = 99;
		int value2 = 125;
		vector<complex<double>> v1(size1, 0);
		v1[0] = size1 * value1;
		vector<complex<double>> v2(size2, 0);
		v2[0] = size2 * value2;

		DSP1.x = vectorWithSingleValue(size1, value1);
		DSP1.h = vectorWithSingleValue(size2, value2);
		
		REQUIRE(DSP::DFT(DSP1.x).size() == v1.size());
		for (int index = 0; index < v1.size(); index++) {
			REQUIRE(Approx(real(DSP::DFT(DSP1.x)[index])).margin(1e-12) == real(v1[index]));
		}
		
		REQUIRE(DSP::DFT(DSP1.h).size() == v2.size());
		for (int index = 0; index < v2.size(); index++) {
			REQUIRE(Approx(real(DSP::DFT(DSP1.h)[index])).margin(1e-12) == real(v2[index]));
		}
	}
}

TEST_CASE("Further DFT testing", "[DFT]") {
	SECTION("") {
	}
}

TEST_CASE("Complex doubles as input", "[Template]") {
	SECTION("") {
	}
}
