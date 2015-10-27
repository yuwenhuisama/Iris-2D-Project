# Copy Nessesary File First
file(COPY "hlsl" DESTINATION "/")
file(COPY "image" DESTINATION "/")
file(COPY "layout" DESTINATION "/")
file(COPY "media" DESTINATION "/")
file(COPY "image.dat" DESTINATION "/")
file(COPY "fmodex.dll" DESTINATION "/")
if(MSVC)
	file(COPY "Iris2D.dll" DESTINATION "/")
	file(COPY "Iris2D.lib" DESTINATION "/")
else(MSVC)
	file(COPY "libIris2D.dll" DESTINATION "/")
	file(COPY "libIris2D.dll.a" DESTINATION "/")
endif(MSVC)

# Other
set(API_TEST_HEADER "Iris 2D Library.h")
set(API_TEST_SOURCE "main.cpp")

include_directories("/")
link_directories("/")

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sdl")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -finput-charset=GBK")
endif(MSVC)

add_executable(Iris_2D_API_Test WIN32 ${API_TEST_HEADER} ${API_TEST_SOURCE})

if(MSVC)
	target_link_libraries(Iris_2D_API_Test "Iris2D.lib")
else(MSVC)
	target_link_libraries(Iris_2D_API_Test "libIris2D.dll.a")
endif(MSVC)

# Source Group
source_group(Include FILES ${LIBRARY_HEADER})