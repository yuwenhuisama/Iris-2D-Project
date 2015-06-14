cmake_minimum_required(VERSION 3.1)
project(Iris2D_Tools)

option(IRIS2D_GENERAL_PAKER_TOOL "Build Iris 2D Biscuit-Turkey(API)" ON)
option(IRIS2D_GRAPH_PAKER_TOOL "Build Iris 2D Biscuit-Onion(API)" ON)

set(IRIS2D_TOOL_VERSION "2.0.0.1")

if(IRIS2D_GENERAL_PAKER_TOOL)
	add_subdirectory("Iris 2D General Source Packer and Unpacker")
endif(IRIS2D_GENERAL_PAKER_TOOL)

if(IRIS2D_GRAPH_PAKER_TOOL)
	add_subdirectory("Iris 2D Graphics Packer and Unpacker")
endif(IRIS2D_GRAPH_PAKER_TOOL)