#include <vector>
#include <complex>

#include <iostream>
#include <catch2/catch.hpp>

#include "../src/LWDSP.hpp"

using namespace std::complex_literals;  // Need to use this namespace to use the imaginary unit i


TEST_CASE("Testing constructors", "[Default ctor, construction from vectors, copy ctor, operator=]") {
    std::vector<double> v1 = { 1,2,3,4 };
    std::vector<double> v2 = { 5,6,7,8 };

	SECTION("Default constructor") {
		LWDSP<int> DSP1;
		REQUIRE(DSP1.x.empty());
		REQUIRE(DSP1.h.empty());
	}

	SECTION("Construction from vectors") {
		LWDSP<double> DSP1(v1, v2);
		REQUIRE(DSP1.x == v1);
		REQUIRE(DSP1.h == v2);
	}

	SECTION("Copy constructor") {
		LWDSP<double> DSP2(v1, v2);
		LWDSP<double> DSP1(DSP2);
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}

	SECTION("Assignment operator") {
		std::vector<double> v3 = { 100, 200, 300, 400, 500, 600, 101010 };
		std::vector<double> v4 = { 100, 5050505, 101010 };
		LWDSP<double> DSP1(v2, v1);
		LWDSP<double> DSP2(v4, v3);
		DSP1 = DSP2;
		REQUIRE(DSP1.x == DSP2.x);
		REQUIRE(DSP1.h == DSP2.h);
	}
}

TEST_CASE("Overloads for equal to/not equal to operators", "[Overloads]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	std::vector<double> v3 = { 100, 50505, 1010 };

	LWDSP<double> DSP1(v1, v2);
	LWDSP<double> DSP2(v1, v2);
	LWDSP<double> DSP3(v3, v1);

	REQUIRE(DSP1 == DSP2);
	REQUIRE(DSP3 != DSP1);
}

TEST_CASE("2 systems in parallel", "[Parallel]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	std::vector<double> v3 = { 100, 50505, 1010 };
	std::vector<double> v4 = {10, 12, 14, 16};
	std::vector<double> v5 = {105, 50511, 1017, 8};
	
	LWDSP<double> DSP1(v1, v2);
	LWDSP<double> DSP2(v1, v2);
	LWDSP<double> DSP3(v3, v3);

	LWDSP DSP4 = DSP1 || DSP2;
	REQUIRE(DSP4.x == v1);
	REQUIRE(DSP4.h == v4);

	LWDSP DSP5 = DSP3 || DSP1;
	REQUIRE(DSP5.x == v3);
	REQUIRE(DSP5.h == v5);
}

TEST_CASE("DFT function", "[DFT]") {
	std::vector<double> v1 = { 1,2,3,4 };
	std::vector<double> v2 = { 5,6,7,8 };
	LWDSP<double> DSP1;
	
	SECTION("Zero elements in x and h") {
		REQUIRE(LWDSP<double>::DFT(DSP1.x).empty());
		REQUIRE(LWDSP<double>::DFT(DSP1.h).empty());
	}

	SECTION("One element in x and h") {
		DSP1.x.push_back(v1[1]);
		DSP1.h.push_back(v1[1]);
		REQUIRE(LWDSP<double>::DFT(DSP1.x)[0] == v1[1]);
		REQUIRE(LWDSP<double>::DFT(DSP1.x).size() == 1);

		REQUIRE(LWDSP<double>::DFT(DSP1.h)[0] == v1[1]);
		REQUIRE(LWDSP<double>::DFT(DSP1.h).size() == 1);
	}
	/*
	SECTION("Integers as input") {
		
		SECTION("Constant values in x and h") {
			// Create vectors of different sizes and populate them with 0's
			std::vector<std::complex<double>> v1(4, 0);
			std::vector<std::complex<double>> v2(10, 0);
			v1[0] = 4 * 99;
			v2[0] = 10 * 125;

			DSP1.x = { 99, 99, 99, 99 };
			DSP1.h = { 125, 125, 125, 125, 125, 125, 125, 125, 125, 125 };
			
			REQUIRE(LWDSP::DFT(DSP1.x).size() == v1.size());
			for (int index = 0; index < v1.size(); index++) {
				REQUIRE(Approx(real(LWDSP::DFT(DSP1.x)[index])).margin(1e-10) == real(v1[index]));
			}

			REQUIRE(LWDSP::DFT(DSP1.h).size() == v2.size());
			for (int index = 0; index < v2.size(); index++) {
				REQUIRE(Approx(real(LWDSP::DFT(DSP1.h)[index])).margin(1e-10) == real(v2[index]));
			}
		}
		
		SECTION("Basic integer scenario")
		{
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
	}
	
	SECTION("Doubles as input") {
		SECTION("Basic doubles scenario")
		{
			LWDSP DSP;
			DSP.x = {0.5, 2.5, 5.0, 100.0, 120.9};
			DSP.h = {1.2, 45.8, 222.2, 90.1};

			std::vector<std::complex<double>> result1 = {228.9, -46.3140873035010 + 168.4446904971312i,
														 -66.8859126964990 - 20.7565951766108i, -66.8859126964990 + 20.7565951766108i,
														 -046.3140873035010 - 168.4446904971312i};
			std::vector<std::complex<double>> result2 = {359.3, -221. + 44.3i, 87.5, -221. - 44.3i};

			for (int i = 0; i < result1.size(); ++i)
			{
				REQUIRE(Approx(real(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == real(result1[i]));
	            REQUIRE(Approx(real(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == real(result2[i]));

	            REQUIRE(Approx(imag(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == imag(result1[i]));
	            REQUIRE(Approx(imag(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == imag(result2[i]));
			}
		}
    }
	
	SECTION("Complex doubles as input") {
		SECTION("Complex integers")
		{
			SECTION("Imaginary numbers only") {
				LWDSP DSP;
				//DSP.x = { -64i, 128i };
				//DSP.h = { 1i, 2i, 3i, 4i, 5i, 6i };

				std::vector<std::complex<double>> result1 = { 64i, -192i };
				std::vector<std::complex<double>> result2 = { 15i, -3.440954801177933 - 2.5i, -0.812299240582266 - 2.5i, 0.812299240582266 - 2.5i, 3.440954801177933 - 2.5i };

				for (int i = 0; i < result1.size(); ++i)
				{
					//REQUIRE(Approx(real(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == real(result1[i]));
					//REQUIRE(Approx(real(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == real(result2[i]));

					//REQUIRE(Approx(imag(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == imag(result1[i]));
					//REQUIRE(Approx(imag(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == imag(result2[i]));
				}				
			}
			
			SECTION("Imaginary and real numbers") {
				LWDSP DSP;
				//DSP.x = { 1., 2.-1i, -1i, -1.+2i };
				//DSP.h = { -4i, 1+8i, 4i, 8 };

				std::vector<std::complex<double>> result1 = { 2., -2.-2i, -2i, 4.+4i};
				std::vector<std::complex<double>> result2 = { 9.+8i, 8-1i, -9-8i, -8-15i };

				for (int i = 0; i < result1.size(); ++i)
				{
					//REQUIRE(Approx(real(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == real(result1[i]));
					//REQUIRE(Approx(real(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == real(result2[i]));

					//REQUIRE(Approx(imag(LWDSP::DFT(DSP.x)[i])).margin(1e-12) == imag(result1[i]));
					//REQUIRE(Approx(imag(LWDSP::DFT(DSP.h)[i])).margin(1e-12) == imag(result2[i]));
				}
			}			
		}
		SECTION("Imaginary and real doubles") {
			
		}		
	}*/
}
