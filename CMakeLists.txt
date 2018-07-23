cmake_minimum_required(VERSION 3.10)
project(Iris2D_Cherry_Spinach)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(CompileType "Debug")
set(CompileArchitecture "x64")

if(WIN32)
	set(GLEW_H E:/OpenMetalMax/Iris-2D-Project/lib/glew/include/GL)
	if (CompileArchitecture STREQUAL "x64")
		set(GLFW_H E:/OpenMetalMax/Iris-2D-Project/lib/glfw/includex64/GLFW)
	elseif (CompileArchitecture STREQUAL "x86")
		set(GLFW_H E:/OpenMetalMax/Iris-2D-Project/lib/glfw/includex86/GLFW)
	endif ()
	set(GLM_H E:/OpenMetalMax/Iris-2D-Project/lib/)
	include_directories(${GLEW_H} ${GLFW_H} ${GLM_H})
elseif (APPLE)
	set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
	set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
	set(GLM_H /usr/local/include/)
	include_directories(${GLEW_H} ${GLFW_H} ${GLM_H})
endif ()

if (WIN32)
	
	if (CompileArchitecture STREQUAL "x64")
		if (CompileType STREQUAL  "Debug")
			set(GLEW_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/glew/x64/Debug/glew32d.lib)
			set(GLFW_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/glfw/x64/Debug/glfw3dll.lib)
			set(DIRECTX_TEX_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/x64/Debug/DirectXTex.lib)
		elseif (CompileType STREQUAL  "Release")
			set(GLEW_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/glew/x64/Release/glew32.lib)
			set(GLFW_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/glfw/x64/Release/glfw3dll.lib)
			set(DIRECTX_TEX_LINK_X64 E:/OpenMetalMax/Iris-2D-Project/lib/x64/Release/DirectXTex.lib)
		endif()

		link_libraries(${OPENGL} ${GLEW_LINK_X64} ${GLFW_LINK_X64} ${DIRECTX_TEX_LINK_X64})
	elseif (CompileArchitecture STREQUAL "x86")
		if (CompileType STREQUAL  "Debug")
			set(GLEW_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/glew/x86/Debug/glew32d.lib)
			set(GLFW_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/glfw/x86/Debug/glfw3dll.lib)
			set(DIRECTX_TEX_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/x86/Debug/DirectXTex.lib)
		elseif (CompileType STREQUAL  "Release")
			set(GLEW_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/glew/x86/Release/glew32.lib)
			set(GLFW_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/glfw/x86/Release/glfw3dll.lib)
			set(DIRECTX_TEX_LINK_X86 E:/OpenMetalMax/Iris-2D-Project/lib/x86/Release/DirectXTex.lib)
		endif()

		link_libraries(${OPENGL} ${GLEW_LINK_X86} ${GLFW_LINK_X86} ${DIRECTX_TEX_LINK_X86})
	endif()

elseif (APPLE)
	set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
	set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
	link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})
endif ()

find_package(OpenGL REQUIRED)

aux_source_directory(./src DIR_SRCS_MAIN)
aux_source_directory(./src/OpenGL DIR_SRCS_MAIN_OPENGL)
aux_source_directory(./src/OpenGL/Iris2D DIR_SRCS_MAIN_OPENGL_IRIS2D)
aux_source_directory(./src/OpenGL/Iris2D/Shaders DIR_SRCS_MAIN_OPENGL_IRIS2D_SHADER)
aux_source_directory(./src/OpenGL/Util DIR_SRCS_MAIN_OPENGL_UTIL)

aux_source_directory(./src/DirectX/Iris2D DIR_SRCS_MAIN_DIRECTX_IRIS2D)
aux_source_directory(./src/DirectX/Iris2D/Shaders DIR_SRCS_MAIN_DIRECTX_IRIS2D_SHADER)
aux_source_directory(./src/DirectX/Util DIR_SRCS_MAIN_DIRECTX_IRIS2D_UTIL)
aux_source_directory(./src/DirectX/DxUtil DIR_SRCS_MAIN_DIRECTX_DX_UTIL)

aux_source_directory(./src/Common/Iris2D DIR_SRCS_COMMON_IRIS2D)
aux_source_directory(./src/Common/Util DIR_SRCS_COMMON_IRIS2D_UTIL)

if (WIN32)
add_executable(main
		WIN32
        ${DIR_SRCS_MAIN}
        
		${DIR_SRCS_MAIN_OPENGL}
        ${DIR_SRCS_MAIN_OPENGL_IRIS2D}
		${DIR_SRCS_MAIN_OPENGL_IRIS2D_SHADER}
		${DIR_SRCS_MAIN_OPENGL_UTIL}
		
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_SHADER}
		${DIR_SRCS_MAIN_DIRECTX_IRIS2D_UTIL}
        ${DIR_SRCS_COMMON_IRIS2D}
        ${DIR_SRCS_COMMON_IRIS2D_UTIL}
		${DIR_SRCS_MAIN_DIRECTX_DX_UTIL}
      )
elseif (APPLE)
add_executable(main
        ${DIR_SRCS_MAIN}
        
		${DIR_SRCS_MAIN_OPENGL}
        ${DIR_SRCS_MAIN_OPENGL_IRIS2D}
		${DIR_SRCS_MAIN_OPENGL_IRIS2D_SHADER}
		${DIR_SRCS_MAIN_OPENGL_UTIL}

        ${DIR_SRCS_COMMON_IRIS2D}
        ${DIR_SRCS_COMMON_IRIS2D_UTIL}
		${DIR_SRCS_MAIN_DIRECTX_DX_UTIL}
      )
endif ()

target_link_libraries(main ${OPENGL_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
