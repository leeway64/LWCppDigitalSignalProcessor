#include <vector>
#include <complex>

#include <catch2/catch.hpp>

#include "../src/LWDSP.hpp"

using namespace std::complex_literals;

std::vector<double> vectorWithSingleValue(int size, int value) {
    std::vector<double> result;
	for (int i = size; i > 0; --i) {
		result.push_back(value);
	}
	return result;
}

TEST_CASE("Testing constructors", "[Default ctor, construction from vectors, copy ctor, operator=]") {
    std::vector<double> v1 = { 1,2,3,4 };
    std::vector<double> v2 = { 5,6,7,8 };

	SECTION("Default constructor") {
		LWDSP DSP1;
		REQUIRE(DSP1.x.empty());
		REQUIRE(DSP1.h.empty());
	}

	SECTION("Construction from vectors") {
		LWDSP DSP1(v1, v2);
		REQUIRE(DSP1.x == v1);
		REQUIRE(DSP1.h == v2);
	}

	SECTION("Copy constructor") {
		LWDSP DSP2(v1, v2);
		LWDSP DSP1(DSP2);
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}

	SECTION("Assignment operator") {
		std::vector<double> v3 = { 100, 200, 300, 400, 500, 600, 101010 };
		std::vector<double> v4 = { 100, 5050505, 101010 };
		LWDSP DSP1(v2, v1);
		LWDSP DSP2(v4, v3);
		DSP1 = DSP2;
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}
}

TEST_CASE("Overloads for equal to/not equal to operators", "[Overloads]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	std::vector<double> v3 = { 100, 50505, 1010 };

	LWDSP DSP1(v1, v2);
	LWDSP DSP2(v1, v2);
	LWDSP DSP3(v3, v1);

	REQUIRE(DSP1 == DSP2);
	REQUIRE(DSP3 != DSP1);
}

TEST_CASE("2 systems in parallel", "[Parallel]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	std::vector<double> v3 = { 100, 50505, 1010 };

	std::vector<double> v4 = {10, 12, 14, 16};
	std::vector<double> v5 = {105, 50511, 1017, 8};
	LWDSP DSP1(v1, v2);
	LWDSP DSP2(v1, v2);
	LWDSP DSP3(v3, v3);

	LWDSP DSP4 = DSP1 || DSP2;
	REQUIRE(DSP4.x == v1);
	REQUIRE(DSP4.h == v4);

	LWDSP DSP5 = DSP3 || DSP1;
	REQUIRE(DSP5.x == v3);
	REQUIRE(DSP5.h == v5);
}

TEST_CASE("Basic testing of DFT function", "[DFT]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	LWDSP DSP1;
	
	SECTION("Zero elements in x and h") {
		REQUIRE(LWDSP::DFT(DSP1.x).empty());
		REQUIRE(LWDSP::DFT(DSP1.h).empty());
	}

	SECTION("One element in x and h") {
		DSP1.x.push_back(v1[1]);
		DSP1.h.push_back(v1[1]);
		REQUIRE(LWDSP::DFT(DSP1.x)[0] == v1[1]);
		REQUIRE(LWDSP::DFT(DSP1.x).size() == 1);

		REQUIRE(LWDSP::DFT(DSP1.h)[0] == v1[1]);
		REQUIRE(LWDSP::DFT(DSP1.h).size() == 1);
	}

	SECTION("Constant values in x and h") {
		int size1 = 4;
		int size2 = 10;
		int value1 = 99;
		int value2 = 125;
		std::vector<std::complex<double>> v1(size1, 0);
		v1[0] = size1 * value1;
		std::vector<std::complex<double>> v2(size2, 0);
		v2[0] = size2 * value2;

		DSP1.x = vectorWithSingleValue(size1, value1);
		DSP1.h = vectorWithSingleValue(size2, value2);
		
		REQUIRE(LWDSP::DFT(DSP1.x).size() == v1.size());
		for (int index = 0; index < v1.size(); index++) {
			REQUIRE(Approx(real(LWDSP::DFT(DSP1.x)[index])).margin(1e-12) == real(v1[index]));
		}
		
		REQUIRE(LWDSP::DFT(DSP1.h).size() == v2.size());
		for (int index = 0; index < v2.size(); index++) {
			REQUIRE(Approx(real(LWDSP::DFT(DSP1.h)[index])).margin(1e-12) == real(v2[index]));
		}
	}
}

TEST_CASE("Further DFT testing", "[DFT]") {
	SECTION("Integers as input") {
        LWDSP DSP;
        std::vector<double> v1 = {10, 20, 30, 40};
        DSP.x = {1,2,3,4};
        DSP.h = v1;

        std::vector<std::complex<double>> result1 = {10, -2. + 2i, -2, -2. - 2i};
        std::vector<std::complex<double>> result2 = {100, -20. + 20i, -20, -20. - 20i};

        for (int i = 0; i < result1.size(); ++i)
        {
            REQUIRE(Approx(real(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == real(result1[i]));
            REQUIRE(Approx(real(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == real(result2[i]));

            REQUIRE(Approx(imag(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == imag(result1[i]));
            REQUIRE(Approx(imag(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == imag(result2[i]));
        }
	}

    SECTION("Doubles as input") {
        LWDSP DSP;
        DSP.x = {0.5, 2.5, 5.0, 100.0, 120.9};
        DSP.h = {1.2, 45.8, 222.2, 90.1};

        //std::vector<std::complex<double>> result1 = {10, -2. + 2i, -2, -2. - 2i};
        //std::vector<std::complex<double>> result2 = {100, -20. + 20i, -20, -20. - 20i};

        for (int i = 0; i < result1.size(); ++i)
        {
//            REQUIRE(Approx(real(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == real(result1[i]));
//            REQUIRE(Approx(real(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == real(result2[i]));
//
//            REQUIRE(Approx(imag(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == imag(result1[i]));
//            REQUIRE(Approx(imag(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == imag(result2[i]));
        }
    }
}

TEST_CASE("Complex doubles as input", "[Template]") {
	SECTION("") {
	}
}
