#include <vector>
#include <complex>

#include <iostream>
#include <catch2/catch.hpp>

#include "../src/LWDSP.hpp"

using namespace std::complex_literals;  // Need to use this namespace to use the imaginary unit i


TEST_CASE("Testing constructors", "[Default ctor, construction from vectors, copy ctor, operator=]") {
    std::vector<double> v1 = { 1, 2, 3, 4 };
    std::vector<double> v2 = { 5, 6, 7, 8 };

	SECTION("Default constructor") {
		LWDSP<int> DSP;
		REQUIRE(DSP.x.empty());
		REQUIRE(DSP.h.empty());
	}

	SECTION("Construction from vectors") {
		LWDSP<double> DSP(v1, v2);
		REQUIRE(DSP.x == v1);
		REQUIRE(DSP.h == v2);
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
	std::vector<double> v1 = { 1, 2, 3, 4 };
	std::vector<double> v2 = { 5, 6, 7, 8 };
	std::vector<double> v3 = { 100, 50505, 1010 };

	LWDSP<double> DSP1(v1, v2);
	LWDSP<double> DSP2(v1, v2);
	LWDSP<double> DSP3(v3, v1);

	REQUIRE(DSP1 == DSP2);
	REQUIRE(DSP3 != DSP1);
}

TEST_CASE("2 systems in parallel", "[Parallel]") {
	std::vector<double> v1 = { 1, 2, 3, 4 };
	std::vector<double> v2 = { 5, 6, 7, 8 };
	std::vector<double> v3 = { 100, 50505, 1010 };
	std::vector<double> v4 = { 10, 12, 14, 16 };
	std::vector<double> v5 = { 105, 50511, 1017, 8 };
	
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
    
    SECTION("Basic DFT scenarios")
    {
	    std::vector<int> v1 = { 1, 2, 3, 4 };
	    std::vector<int> v2 = { 5, 6, 7, 8 };
	    LWDSP<int> DSP;
	    
	    SECTION("Zero elements in x and h") {
		    REQUIRE(LWDSP<int>::DFT(DSP.x).empty());
		    REQUIRE(LWDSP<int>::DFT(DSP.h).empty());
	    }

	    SECTION("One element in x and h") {
		    DSP.x.push_back(v1[1]);
		    DSP.h.push_back(v2[1]);
		    
			const auto x_DFT = LWDSP<int>::DFT(DSP.x);
			const auto h_DFT = LWDSP<int>::DFT(DSP.h);
		    
		    REQUIRE(LWDSP<int>::DFT(DSP.x).size() == 1);
			REQUIRE(Approx(real(x_DFT[0])).margin(1e-12) == std::real(v1[1]));
			REQUIRE(Approx(imag(x_DFT[0])).margin(1e-12) == std::imag(v1[1]));

		    REQUIRE(LWDSP<int>::DFT(DSP.h).size() == 1);
			REQUIRE(Approx(real(h_DFT[0])).margin(1e-12) == std::real(v2[1]));
			REQUIRE(Approx(imag(h_DFT[0])).margin(1e-12) == std::imag(v2[1]));
	    }
    }
	
	SECTION("Integers as input") {
		SECTION("Constant values in x and h") {
    	    LWDSP<int> DSP;
			// Create vectors of different sizes and populate them with 0's
			std::vector<int> v1(4, 0);
			std::vector<int> v2(10, 0);
			v1[0] = 4 * 99;
			v2[0] = 10 * 125;

			DSP.x = { 99, 99, 99, 99 };
			DSP.h = { 125, 125, 125, 125, 125, 125, 125, 125, 125, 125 };
			
			const auto x_DFT = LWDSP<int>::DFT(DSP.x);
			const auto h_DFT = LWDSP<int>::DFT(DSP.h);
			
			REQUIRE(x_DFT.size() == v1.size());
			for (int index = 0; index < v1.size(); index++) {
				REQUIRE(Approx(std::real(x_DFT[index])).margin(1e-10) == std::real(v1[index]));
				REQUIRE(Approx(std::imag(x_DFT[index])).margin(1e-10) == std::imag(v1[index]));
			}

			REQUIRE(h_DFT.size() == v2.size());
			for (int index = 0; index < v2.size(); index++) {
				REQUIRE(Approx(std::real(h_DFT[index])).margin(1e-10) == std::real(v2[index]));
				REQUIRE(Approx(std::imag(h_DFT[index])).margin(1e-10) == std::imag(v2[index]));
			}
		}
		
		SECTION("Basic integer scenario")
		{
			LWDSP<int> DSP;
			DSP.x = { 1, 2, 3, 4 };
			DSP.h = { 10, 20, 30, 40 };

			std::vector<std::complex<double>> result1 = { 10, -2.+2i, -2, -2.-2i };
			std::vector<std::complex<double>> result2 = { 100, -20.+20i, -20, -20.-20i };

			const auto x_DFT = LWDSP<int>::DFT(DSP.x);
			const auto h_DFT = LWDSP<int>::DFT(DSP.h);

			REQUIRE(x_DFT.size() == result1.size());
			REQUIRE(h_DFT.size() == result2.size());
			
			for (int i = 0; i < result1.size(); ++i)
			{
				REQUIRE(Approx(std::real(x_DFT[i])).margin(1e-12) == std::real(result1[i]));
				REQUIRE(Approx(std::real(h_DFT[i])).margin(1e-12) == std::real(result2[i]));

				REQUIRE(Approx(std::imag(x_DFT[i])).margin(1e-12) == std::imag(result1[i]));
				REQUIRE(Approx(std::imag(h_DFT[i])).margin(1e-12) == std::imag(result2[i]));
			}
		}
	}
	
	SECTION("Doubles as input") {
		SECTION("Basic doubles scenario")
		{
			LWDSP<double> DSP;
			DSP.x = { 0.5, 2.5, 5.0, 100.0, 120.9 };
			DSP.h = { 1.2, 45.8, 222.2, 90.1 };

			std::vector<std::complex<double>> result1 = { 228.9, -46.3140873035010+168.4446904971312i,
														 -66.8859126964990-20.7565951766108i, -66.8859126964990+20.7565951766108i,
														 -046.3140873035010-168.4446904971312i };
			std::vector<std::complex<double>> result2 = { 359.3, -221.+44.3i, 87.5, -221.-44.3i };

			const auto x_DFT = LWDSP<double>::DFT(DSP.x);
			const auto h_DFT = LWDSP<double>::DFT(DSP.h);

			REQUIRE(x_DFT.size() == result1.size());
			for (int i = 0; i < result1.size(); ++i)
			{	            
				REQUIRE(Approx(std::real(x_DFT[i])).margin(1e-12) == std::real(result1[i]));
				REQUIRE(Approx(std::imag(x_DFT[i])).margin(1e-12) == std::imag(result1[i]));
			}
			
			REQUIRE(h_DFT.size() == result2.size());
			for (int i = 0; i < result2.size(); ++i)
			{	            
				REQUIRE(Approx(std::real(h_DFT[i])).margin(1e-12) == std::real(result2[i]));
				REQUIRE(Approx(std::imag(h_DFT[i])).margin(1e-12) == std::imag(result2[i]));
			}
		}
    }
	
	SECTION("Complex doubles as input") {
		SECTION("Complex integers")
		{
			SECTION("Imaginary numbers only") {
				LWDSP<std::complex<int>> DSP;
				DSP.x = { -64i, 128i };
				DSP.h = { 1i, 2i, 3i, 4i, 5i, 6i };

				std::vector<std::complex<double>> result1 = { 64i, -192i };
				std::vector<std::complex<double>> result2 = { 21.i, -5.196152422706632-3.i, -1.732050807568877-3.i, -3.i, 1.732050807568877-3.i, 5.196152422706632-3.i };

			    const auto x_DFT = LWDSP<std::complex<int>>::DFT(DSP.x);
			    const auto h_DFT = LWDSP<std::complex<int>>::DFT(DSP.h);

			    REQUIRE(x_DFT.size() == result1.size());
				for (int i = 0; i < result1.size(); ++i)
				{
				    REQUIRE(Approx(std::real(x_DFT[i])).margin(1e-12) == std::real(result1[i]));
				    REQUIRE(Approx(std::imag(x_DFT[i])).margin(1e-12) == std::imag(result1[i]));
				}
				
				REQUIRE(h_DFT.size() == result2.size());
				for (int i = 0; i < result2.size(); ++i)
				{
				    REQUIRE(Approx(std::real(h_DFT[i])).margin(1e-12) == std::real(result2[i]));
				    REQUIRE(Approx(std::imag(h_DFT[i])).margin(1e-12) == std::imag(result2[i]));
				}
			}
			
			SECTION("Imaginary and real numbers") {
				LWDSP<std::complex<double>> DSP;  // The type needs to be complex<double>
				DSP.x = { 1., 2.-1i, -1i, -1.+2i };
				DSP.h = { -4i, 1.+8i, 4i, 8. };

				std::vector<std::complex<double>> result1 = { 2., -2.-2i, -2i, 4.+4i};
				std::vector<std::complex<double>> result2 = { 9.+8i, 8.-1i, -9.-8i, -8.-15i };

			    const auto x_DFT = LWDSP<std::complex<double>>::DFT(DSP.x);
			    const auto h_DFT = LWDSP<std::complex<double>>::DFT(DSP.h);

			    REQUIRE(x_DFT.size() == result1.size());
				REQUIRE(h_DFT.size() == result2.size());
				REQUIRE(x_DFT.size() == h_DFT.size());
				
				for (int i = 0; i < result1.size(); ++i)
				{
					REQUIRE(Approx(std::real(x_DFT[i])).margin(1e-12) == std::real(result1[i]));
					REQUIRE(Approx(std::real(h_DFT[i])).margin(1e-12) == std::real(result2[i]));

					REQUIRE(Approx(std::imag(x_DFT[i])).margin(1e-12) == std::imag(result1[i]));
					REQUIRE(Approx(std::imag(h_DFT[i])).margin(1e-12) == std::imag(result2[i]));
				}
			}
		}
		
		SECTION("Imaginary and real doubles") {
			LWDSP<std::complex<double>> DSP;
			DSP.x = { 3.5-1.5i, 0.64-2i, 12.8+3i };
			DSP.h = { 90.9, 12.34+8.88i, 6.5+67.3i, 9.736-8.888i, 4.+5.i };

			std::vector<std::complex<double>> result1 = { 16.94-0.5i, -7.550127018922193+8.530868910018773i, 1.110127018922192 -12.530868910018773i };
			std::vector<std::complex<double>> result2 = { 123.476+72.292i, 131.2864198522991-48.9968830629883i, 12.5193751479846-1.1586030973452i, 152.8763493171854+14.8008926843555i, 34.3418556825308-36.9374065240220i };

		    const auto x_DFT = LWDSP<std::complex<double>>::DFT(DSP.x);
		    const auto h_DFT = LWDSP<std::complex<double>>::DFT(DSP.h);

		    REQUIRE(x_DFT.size() == result1.size());
			for (int i = 0; i < result1.size(); ++i)
			{
			    REQUIRE(Approx(std::real(x_DFT[i])).margin(1e-12) == std::real(result1[i]));
			    REQUIRE(Approx(std::imag(x_DFT[i])).margin(1e-12) == std::imag(result1[i]));
			}
			
			REQUIRE(h_DFT.size() == result2.size());
			for (int i = 0; i < result2.size(); ++i)
			{
			    REQUIRE(Approx(std::real(h_DFT[i])).margin(1e-12) == std::real(result2[i]));
			    REQUIRE(Approx(std::imag(h_DFT[i])).margin(1e-12) == std::imag(result2[i]));
			}
		}
	}
}
