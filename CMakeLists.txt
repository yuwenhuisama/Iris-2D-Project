cmake_minimum_required(VERSION 3.10)
project(Iris2D_Cherry_Spinach)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

if(WIN32)
	set(GLEW_H E:/3rdLib/glew-2.1.0/include/GL)
	set(GLFW_H E:/3rdLib/glfw-3.2.1.bin.WIN64/include/GLFW)
	include_directories(${GLEW_H} ${GLFW_H})
elseif (APPLE)
	set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
	set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
	set(GLM_H /usr/local/include/)
	include_directories(${GLEW_H} ${GLFW_H} ${GLM_H})
endif ()

if (WIN32)
	#set(GLEW_LINK E:/3rdLib/glew-2.1.0/lib/Release/x64/glew32s.lib)
	#set(GLFW_LINK E:/3rdLib/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.lib)
	set(DIRECTX_TEX_LINK E:/OpenMetalMax/Iris-2D-Project/lib/Debug/DirectXTex.lib)

	link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${DIRECTX_TEX_LINK})

elseif (APPLE)
	set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
	set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
	link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})
elseif (APPLE)
endif ()

find_package(OpenGL REQUIRED)

aux_source_directory(./src DIR_SRCS_MAIN)
aux_source_directory(./src/OpenGL DIR_SRCS_MAIN_OPENGL)
# aux_source_directory(./src/OpenGL/Iris2D DIR_SRCS_MAIN_OPENGL_IRIS2D)

aux_source_directory(./src/DirectX/Iris2D DIR_SRCS_MAIN_DIRECTX_IRIS2D)
aux_source_directory(./src/DirectX/Iris2D/IrisShaders DIR_SRCS_MAIN_DIRECTX_IRIS2D_SHADER)
aux_source_directory(./src/DirectX/Iris2DUtil DIR_SRCS_MAIN_DIRECTX_IRIS2D_UTIL)
aux_source_directory(./src/DirectX/DxUtil DIR_SRCS_MAIN_DIRECTX_DX_UTIL)

aux_source_directory(./src/Common/Iris2D DIR_SRCS_COMMON_IRIS2D)
aux_source_directory(./src/Common/Iris2DUtil DIR_SRCS_COMMON_IRIS2D_UTIL)

if (WIN32)
add_executable(main
		WIN32
        ${DIR_SRCS_MAIN}
        # ${DIR_SRCS_MAIN_OPENGL}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_SHADER}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_UTIL}
        ${DIR_SRCS_COMMON_IRIS2D}
        ${DIR_SRCS_COMMON_IRIS2D_UTIL}
		${DIR_SRCS_MAIN_DIRECTX_DX_UTIL}
        # ${DIR_SRCS_MAIN_OPENGL_IRIS2D}
      )
elseif (APPLE)
add_executable(main
        ${DIR_SRCS_MAIN}
        # ${DIR_SRCS_MAIN_OPENGL}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_SHADER}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_UTIL}
        ${DIR_SRCS_COMMON_IRIS2D}
        ${DIR_SRCS_COMMON_IRIS2D_UTIL}
		${DIR_SRCS_MAIN_DIRECTX_DX_UTIL}
        # ${DIR_SRCS_MAIN_OPENGL_IRIS2D}
      )
endif ()

target_link_libraries(main ${OPENGL_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
