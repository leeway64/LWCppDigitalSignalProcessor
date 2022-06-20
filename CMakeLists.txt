cmake_minimum_required (VERSION 3.8)

project (
	"LWCppDigitalSignalProcessor"
	LANGUAGES CXX
	VERSION "1.0.0"
	)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_configures accepts the same arguments as conanfile.txt
conan_cmake_configure(REQUIRES catch2/2.13.8
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

# I can pass conan_cmake_install all the arguments that conan install supports
conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

find_package(Catch2)


add_executable (LWCppDigitalSignalProcessor_tests
				"src/DSP.hpp"
				"src/DSP.cpp"
				"tests/catch2_main.cpp"
				"tests/test_suite.cpp")

target_link_libraries(
	LWCppDigitalSignalProcessor_tests
	PRIVATE
		Catch2::Catch2
)
