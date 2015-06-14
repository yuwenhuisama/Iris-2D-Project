# Copy Nessesary File First
file(COPY "hlsl" DESTINATION "/")
file(COPY "image" DESTINATION "/")
file(COPY "media" DESTINATION "/")
file(COPY "layout" DESTINATION "/")
file(COPY "fmodex.dll" DESTINATION "/")

# Set
set(TURKEY_ENCRYPTION_HEADER
	"include/Encryption/EncryptionDefines.h"
	"include/Encryption/GeneralEncriptyDefines.h"
	"include/Encryption/GeneralEncriptySourceExtract.h"
	"include/Encryption/IrisGraphicsSourceExtract.h"
	"include/Encryption/LZSS.h"
)

set(TURKEY_ENCRYPTION_SRC
	"src/Encryption/EncryptionFunction.cpp"
	"src/Encryption/GeneralEncriptySourceExtract.cpp"
	"src/Encryption/IrisGraphicsSourceExtract.cpp"
	"src/Encryption/LZSS.cpp"
)

set(TURKEY_IRIS2D_HEADER
	"include/Iris 2D/IrisApp.h"
	"include/Iris 2D/IrisBitmap.h"
	"include/Iris 2D/IrisColor.h"
	"include/Iris 2D/IrisD3DNamespace.h"
	"include/Iris 2D/IrisEncripedResourceManager.h"
	"include/Iris 2d/IrisError.h"
	"include/Iris 2D/IrisFont.h"
	"include/Iris 2D/IrisPlane.h"
	"include/Iris 2D/IrisRect.h"
	"include/Iris 2D/IrisShader.h"
	"include/Iris 2D/IrisSprite.h"
	"include/Iris 2D/IrisTilemap.h"
	"include/Iris 2D/IrisTone.h"
	"include/Iris 2D/IrisViewport.h"
	"include/Iris 2D/IrisWindow.h"
	"include/Iris 2D/ModuleIrisAudio.h"
	"include/Iris 2D/ModuleIrisGraphics.h"
	"include/Iris 2D/ModuleIrisInput.h"
)

set(TURKEY_IRIS2D_SRC
	"src/Iris 2D/D3D Init.cpp"
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

set(TURKEY_TINY_XML_HEADER
	"include/LayoutXML/mylayout.h"
	"include/LayoutXML/tinystr.h"
	"include/LayoutXML/tinyxml.h"
	"include/LayoutXML/XMLDefine.h"
)

set(TURKEY_TINY_XML_SRC
	"src/XML Layout/tinystr.cpp"
	"src/XML Layout/tinyxml.cpp"
	"src/XML Layout/tinyxmlerror.cpp"
	"src/XML Layout/tinyxmlparser.cpp"
)

set(TURKEY_IRIS2D_NORMAL_HEADER
	"include/Iris2D.h"
	"include/Iris2DSupports.h"
)

# Lib
if(MSVC)
	set(TURKEY_LINK_LIB
		"GdiPlus.lib"
		"winmm.lib"
		"d3d9.lib"
		"d3dx9.lib"
		"dinput8.lib"
		"dxguid.lib"
		"fmodex_vc.lib"
	)
else(MSVC)
	set(TURKEY_LINK_LIB
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

# Link
link_directories("lib")
link_directories("lib/DirectX Lib/x86/")
add_definitions( -D_CRT_SECURE_NO_WARNINGS ) 
add_definitions( -DUNICODE -D_UNICODE )

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sdl")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=GBK -std=c++11")
endif(MSVC)

add_executable(Iris2D_Biscuit_Turkey WIN32
	${TURKEY_ENCRYPTION_HEADER}
	${TURKEY_ENCRYPTION_SRC}
	${TURKEY_IRIS2D_HEADER}
	${TURKEY_IRIS2D_SRC}
	${TURKEY_TINY_XML_HEADER}
	${TURKEY_TINY_XML_SRC}
	${TURKEY_IRIS2D_NORMAL_HEADER}
	${TURKEY_IRIS2D_NORMAL_SRC}
)

target_link_libraries(Iris2D_Biscuit_Turkey ${TURKEY_LINK_LIB})
source_group("Headers" FILES ${TURKEY_IRIS2D_NORMAL_HEADER})
source_group("Headers\\Encryption" FILES ${TURKEY_ENCRYPTION_HEADER})
source_group("Headers\\Iris 2D" FILES ${TURKEY_IRIS2D_HEADER})
source_group("Headers\\TinyXML" FILES ${TURKEY_TINY_XML_HEADER})
source_group("Sources\\Encryption" FILES ${TURKEY_ENCRYPTION_SRC})
source_group("Sources\\Iris 2D" FILES ${TURKEY_IRIS2D_SRC})
source_group("Sources\\TinyXML" FILES ${TURKEY_TINY_XML_SRC})
