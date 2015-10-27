set(GRAPH_INCLUDE
	"include/GeneralEncriptyDefines.h"
	"include/GeneralEncriptyMaker.h"
	"include/GeneralEncriptySourceExtract.h"
	"include/GeneralEncriptyUnmaker.h"
	"include/LZSS.h"
)

set(GRAPH_SRC
	"src/GeneralEncriptyMaker.cpp"
	"src/GeneralEncriptySourceExtract.cpp"
	"src/GeneralEncriptyUnmaker.cpp"
	"src/GeneralFunction.cpp"
	"src/LZSS.cpp"
	"src/main.cpp"
)

# Include
include_directories("include")

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sdl")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=GBK -std=c++11")
endif(MSVC)

add_definitions( -D_CRT_SECURE_NO_WARNINGS ) 
add_definitions( -DUNICODE -D_UNICODE )

add_executable(Iris2D_General_Packer_and_Unpacker ${GRAPH_INCLUDE} ${GRAPH_SRC})