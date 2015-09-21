#pragma once
#include "Iris2D.h"

class IrisViewport;
class IrisSprite;
class IrisBitmap;
class IrisTone;
class IrisColor;
class IrisRect;

class MyLayout : public LayoutToObject{

	DECLARE_MAPPING(IrisViewport)
	DECLARE_MAPPING(IrisSprite)
	DECLARE_MAPPING(IrisBitmap)
	DECLARE_MAPPING(IrisTone)
	DECLARE_MAPPING(IrisColor)
	DECLARE_MAPPING(IrisRect)

	BEGIN_OBJECT_CREATE_DEAL()
		BEGIN_CREATE_OBJ(IrisViewport)
		CREATE_OBJ(IrisViewport,
			stringToNum<float>(GET_ATTR_BY_ID(CUR_NODE, "X")),
			stringToNum<float>(GET_ATTR_BY_ID(CUR_NODE, "Y")),
			stringToNum<float>(GET_ATTR_BY_ID(CUR_NODE, "Width")),
			stringToNum<float>(GET_ATTR_BY_ID(CUR_NODE, "Height")))
		END_CREATE_OBJ()

		BEGIN_CREATE_OBJ(IrisSprite)
		CREATE_OBJ(IrisSprite, CALL_MAPPING(IrisViewport, GET_ATTR_BY_ID(PAR_NODE, "ID")))
		END_CREATE_OBJ()

		BEGIN_CREATE_OBJ(IrisBitmap)
		CREATE_OBJ(IrisBitmap, StringToWString(string(GET_ATTR_BY_ID(CUR_NODE, "Src"))))
		LINK_PARENT(IrisSprite, CUR_NODE, Bitmap);
		END_CREATE_OBJ()

		BEGIN_CREATE_OBJ(IrisColor)
		CREATE_OBJ(IrisColor,
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "R")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "G")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "B")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "A")))
		if (PAR_VALUE_EQUAL(IrisSprite))
			LINK_PARENT(IrisSprite, CUR_NODE, Color)
		else
			LINK_PARENT(IrisViewport, CUR_NODE, Color)
		END_CREATE_OBJ()

		BEGIN_CREATE_OBJ(IrisTone)
		CREATE_OBJ(IrisTone,
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "R")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "G")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "B")),
			stringToNum<int>(GET_ATTR_BY_ID(CUR_NODE, "G")))
		if(PAR_VALUE_EQUAL(IrisSprite))
			LINK_PARENT(IrisSprite, CUR_NODE, Tone)
		else
			LINK_PARENT(IrisViewport, CUR_NODE, Tone)
		END_CREATE_OBJ()

		BEGIN_CREATE_OBJ(IrisRect)
		CREATE_OBJ(IrisRect,
			stringToNum<float>(GET_ATTR_BY_ID(parent, "X")),
			stringToNum<float>(GET_ATTR_BY_ID(parent, "Y")),
			stringToNum<float>(GET_ATTR_BY_ID(parent, "Width")),
			stringToNum<float>(GET_ATTR_BY_ID(parent, "Height")))
		LINK_PARENT(IrisSprite, CUR_NODE, SrcRect);
		END_CREATE_OBJ()
	END_OBJECT_CREATE_DEAL()

	BEGIN_OBJECT_ATTR_DEAL()
		BEGIN_ATTR_JUDGE(IrisViewport, id)
		ATTR_JUDGE(Ox, stringToNum<float>(value))
		ATTR_JUDGE(Oy, stringToNum<float>(value))
		ATTR_JUDGE(Visible, value == string("true") ? true : false)
		END_ATTR_JUDGE()

		BEGIN_ATTR_JUDGE(IrisSprite, id)
		ATTR_JUDGE(Visible, value == string("true") ? true : false)
		ATTR_JUDGE(X, stringToNum<float>(value))
		ATTR_JUDGE(Y, stringToNum<float>(value))
		ATTR_JUDGE(Ox, stringToNum<float>(value))
		ATTR_JUDGE(Oy, stringToNum<float>(value))
		ATTR_JUDGE(ZoomX, stringToNum<float>(value))
		ATTR_JUDGE(ZoomY, stringToNum<float>(value))
		ATTR_JUDGE(Angle, stringToNum<float>(value))
		ATTR_JUDGE(WaveAmp, stringToNum<float>(value))
		ATTR_JUDGE(WaveLength, stringToNum<float>(value))
		ATTR_JUDGE(WaveSpeed, stringToNum<float>(value))
		ATTR_JUDGE(WavePhase, stringToNum<float>(value))
		ATTR_JUDGE(Mirror, value == string("true") ? true : false)
		ATTR_JUDGE(BushDepth, stringToNum<int>(value))
		ATTR_JUDGE(BushOpacity, stringToNum<int>(value))
		ATTR_JUDGE(BlendType, stringToNum<int>(value))
		END_ATTR_JUDGE()

		BEGIN_ATTR_JUDGE(IrisTone, id)
		ATTR_JUDGE(Red, stringToNum<int>(value))
		ATTR_JUDGE(Blue, stringToNum<int>(value))
		ATTR_JUDGE(Green, stringToNum<int>(value))
		ATTR_JUDGE(Alpha, stringToNum<int>(value))
		END_ATTR_JUDGE()

		BEGIN_ATTR_JUDGE(IrisColor, id)
		ATTR_JUDGE(Red, stringToNum<int>(value))
		ATTR_JUDGE(Blue, stringToNum<int>(value))
		ATTR_JUDGE(Green, stringToNum<int>(value))
		ATTR_JUDGE(Alpha, stringToNum<int>(value))
		END_ATTR_JUDGE()

		BEGIN_ATTR_JUDGE(IrisRect, id)
		ATTR_JUDGE(X, stringToNum<float>(value))
		ATTR_JUDGE(Y, stringToNum<float>(value))
		ATTR_JUDGE(Width, stringToNum<float>(value))
		ATTR_JUDGE(Height, stringToNum<float>(value))
		END_ATTR_JUDGE()
	END_OBJECT_ATTR_DEAL()

public:

	virtual void ReleaseXML(){
		RELEASE_SOURCE(IrisBitmap)
		RELEASE_SOURCE(IrisSprite)
		RELEASE_SOURCE(IrisViewport)
	}
};