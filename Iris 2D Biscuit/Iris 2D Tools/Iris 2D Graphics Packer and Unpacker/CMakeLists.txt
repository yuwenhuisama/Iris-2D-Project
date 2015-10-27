set(GRAPH_INCLUDE
	"include/defines.h"
	"include/IrisGraphicsPacker.h"
	"include/IrisGraphicsSourceExtract.h"
	"include/IrisGraphicsUnpacker.h"
	"include/LZSS.h"
)

set(GRAPH_SRC
	"src/functions.cpp"
	"src/IrisGraphicsPacker.cpp"
	"src/IrisGraphicsSourceExtract.cpp"
	"src/IrisGraphicsUnpacker.cpp"
	"src/LZSS.cpp"
	"src/main.cpp"
)

set(GRAPH_LINK_LIB "GdiPlus.lib")

# Include
include_directories("include")

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sdl")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=GBK -std=c++11")
endif(MSVC)

add_definitions( -D_CRT_SECURE_NO_WARNINGS ) 
add_definitions( -DUNICODE -D_UNICODE )

add_executable(Iris2D_Graphics_Packer_and_Unpacker ${GRAPH_INCLUDE} ${GRAPH_SRC})