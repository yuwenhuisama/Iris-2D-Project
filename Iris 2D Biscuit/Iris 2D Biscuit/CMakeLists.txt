cmake_minimum_required(VERSION 3.1)
project(Iris2D_Biscuit)

option(IRIS2D_BISCUIT_ONION "Build Iris 2D Biscuit-Onion(API)" ON)
option(IRIS2D_BISCUIT_TURKEY "Build Iris 2D Biscuit-Turkey(API)" ON)
option(IRIS2D_API_TEST "Build Iris 2D API Test Program" ON)

set(IRIS2D_VERSION "2.6.13.1")

if(IRIS2D_BISCUIT_ONION)
	add_subdirectory("Iris 2D Biscuit-Onion(API)")
endif(IRIS2D_BISCUIT_ONION)

if(IRIS2D_BISCUIT_TURKEY)
	add_subdirectory("Iris 2D Biscuit-Turkey(SC)")
endif(IRIS2D_BISCUIT_TURKEY)

if(IRIS2D_API_TEST)
	add_subdirectory("Iris 2D API Test")
endif(IRIS2D_API_TEST)