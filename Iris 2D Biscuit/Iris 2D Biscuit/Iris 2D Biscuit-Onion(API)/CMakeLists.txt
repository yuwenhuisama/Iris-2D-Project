# Copy Nessesary File First
file(COPY "hlsl" DESTINATION "/")
file(COPY "fmodex.dll" DESTINATION "/")

# Set
set(ONION_ENCRYPTION_HEADER
	"include/Encryption/EncryptionDefines.h"
	"include/Encryption/GeneralEncriptyDefines.h"
	"include/Encryption/GeneralEncriptySourceExtract.h"
	"include/Encryption/IrisGraphicsSourceExtract.h"
	"include/Encryption/LZSS.h"
)

set(ONION_ENCRYPTION_SRC
	"src/Encryption/EncryptionFunction.cpp"
	"src/Encryption/GeneralEncriptySourceExtract.cpp"
	"src/Encryption/IrisGraphicsSourceExtract.cpp"
	"src/Encryption/LZSS.cpp"
)

set(ONION_IRIS2D_HEADER
	"include/Iris 2D/IrisApp.h"
	"include/Iris 2D/IrisBitmap.h"
	"include/Iris 2D/IrisColor.h"
	"include/Iris 2D/IrisD3DNamespace.h"
	"include/Iris 2D/IrisEncripedResourceManager.h"
	"include/Iris 2D/IrisFont.h"
	"include/Iris 2D/IrisPlane.h"
	"include/Iris 2D/IrisRect.h"
	"include/Iris 2D/IrisShader.h"
	"include/Iris 2D/IrisSprite.h"
	"include/Iris 2D/IrisTilemap.h"
	"include/Iris 2D/IrisViewport.h"
	"include/Iris 2D/IrisWindow.h"
	"include/Iris 2D/ModuleIrisAudio.h"
	"include/Iris 2D/ModuleIrisGraphics.h"
	"include/Iris 2D/ModuleIrisInput.h"
)

set(ONION_IRIS2D_SRC
	"src/Iris 2D/Iris2D.cpp"
	"src/Iris 2D/IrisApp.cpp"
	"src/Iris 2D/IrisBitmap.cpp"
	"src/Iris 2D/IrisColor.cpp"
	"src/Iris 2D/IrisEncripedResourceManager.cpp"
	"src/Iris 2D/IrisFont.cpp"
	"src/Iris 2D/IrisPlane.cpp"
	"src/Iris 2D/IrisRect.cpp"
	"src/Iris 2D/IrisShader.cpp"
	"src/Iris 2D/IrisSprite.cpp"
	"src/Iris 2D/IrisTilemap.cpp"
	"src/Iris 2D/IrisTone.cpp"
	"src/Iris 2D/IrisViewport.cpp"
	"src/Iris 2D/IrisWindow.cpp"
	"src/Iris 2D/ModuleIrisAudio.cpp"
	"src/Iris 2D/ModuleIrisGraphics.cpp"
	"src/Iris 2D/ModuleIrisInput.cpp"
)

set(ONION_TINY_XML_HEADER
	"include/LayoutXML/mylayout.h"
	"include/LayoutXML/tinystr.h"
	"include/LayoutXML/tinyxml.h"
	"include/LayoutXML/XMLDefine.h"
)

set(ONION_TINY_XML_SRC
	"src/XML Layout/tinystr.cpp"
	"src/XML Layout/tinyxml.cpp"
	"src/XML Layout/tinyxmlerror.cpp"
	"src/XML Layout/tinyxmlparser.cpp"
)

set(ONION_IRIS2D_NORMAL_HEADER
	"include/Iris 2D Library.h"
	"include/Iris2D.h"
	"include/Iris2DSupports.h"
	"include/stdafx.h"
	"include/targetver.h"
)

set(ONION_IRIS2D_NORMAL_SRC
	"src/dllmain.cpp"
	"src/Iris 2D Library.cpp"
	"src/stdafx.cpp"
)

set(ONION_IRIS_2D_NORMAL_EX_HEADER
	"include_ex/SDKDDKVer.h"
)

# Lib
if(MSVC)
	set(ONION_LINK_LIB
		"GdiPlus.lib"
		"winmm.lib"
		"d3d9.lib"
		"d3dx9.lib"
		"dinput8.lib"
		"dxguid.lib"
		"fmodex_vc.lib"
	)
else(MSVC)
	set(ONION_LINK_LIB
		"GdiPlus.lib"
		"winmm.lib"
		"d3d9.lib"
		"d3dx9.lib"
		"dinput8.lib"
		"dxguid.lib"
		"libfmodex.a"
	)
endif(MSVC)

# Include
include_directories("include/DirectX")
include_directories("include/Encryption")
include_directories("include/Fmod Ex")
include_directories("include/Iris 2D")
include_directories("include/LayoutXML")
include_directories("include")

if(NOT MSVC)
	include_directories("include_ex")
endif(NOT MSVC)

# Link
link_directories("lib")
link_directories("lib/DirectX Lib/x86/")
add_definitions( -D_CRT_SECURE_NO_WARNINGS ) 
add_definitions( -DUNICODE -D_UNICODE )
add_definitions("-DIRIS2DLIBRARY_EXPORTS")

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sdl")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=GBK -std=c++11")
endif(MSVC)

if(MSVC)
	add_library(Iris2D_Biscuit_Onion SHARED
		${ONION_ENCRYPTION_HEADER}
		${ONION_ENCRYPTION_SRC}
		${ONION_IRIS2D_HEADER}
		${ONION_IRIS2D_SRC}
		${ONION_TINY_XML_HEADER}
		${ONION_TINY_XML_SRC}
		${ONION_IRIS2D_NORMAL_HEADER}
		${ONION_IRIS2D_NORMAL_SRC}
	)
else(MSVC)
	add_library(Iris2D_Biscuit_Onion SHARED
		${ONION_ENCRYPTION_HEADER}
		${ONION_ENCRYPTION_SRC}
		${ONION_IRIS2D_HEADER}
		${ONION_IRIS2D_SRC}
		${ONION_TINY_XML_HEADER}
		${ONION_TINY_XML_SRC}
		${ONION_IRIS2D_NORMAL_HEADER}
		${ONION_IRIS2D_NORMAL_SRC}
		${ONION_IRIS_2D_NORMAL_EX_HEADER}
	)
endif(MSVC)

target_link_libraries(Iris2D_Biscuit_Onion ${ONION_LINK_LIB})
source_group("Headers" FILES ${ONION_IRIS2D_NORMAL_HEADER})
source_group("Headers\\Encryption" FILES ${ONION_ENCRYPTION_HEADER})
source_group("Headers\\Iris 2D" FILES ${ONION_IRIS2D_HEADER})
source_group("Headers\\TinyXML" FILES ${ONION_TINY_XML_HEADER})
source_group("Sources" FILES ${ONION_IRIS2D_NORMAL_SRC})
source_group("Sources\\Encryption" FILES ${ONION_ENCRYPTION_SRC})
source_group("Sources\\Iris 2D" FILES ${ONION_IRIS2D_SRC})
source_group("Sources\\TinyXML" FILES ${ONION_TINY_XML_SRC})

set_target_properties(Iris2D_Biscuit_Onion PROPERTIES
	OUTPUT_NAME "Iris2D"
	CLEAN_DIRECT_OUTPUT 1
	VERSION ${IRIS2D_VERSION}
)