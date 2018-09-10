#include "Common/Iris2D/Sprites/SpriteBase.h"

namespace Iris2D {

	ResultCode SpriteBase::SetBitmap(Bitmap *& pBitmap) {
		return GetAbstractProxied()->SetBitmap(pBitmap);
	}

	Bitmap * SpriteBase::GetBitmap() const {
		return GetAbstractProxied()->GetBitmap();
	}

	void SpriteBase::SetX(float fX) {
		GetAbstractProxied()->SetX(fX);
	}

	float SpriteBase::GetX() const {
		return GetAbstractProxied()->GetX();
	}

	void SpriteBase::SetY(float fY) {
		GetAbstractProxied()->SetY(fY);
	}

	float SpriteBase::GetY() const {
		return GetAbstractProxied()->GetY();
	}

	void SpriteBase::SetZ(float fZ) {
		GetAbstractProxied()->SetZ(fZ);
	}

	float SpriteBase::GetZ() const {
		return GetAbstractProxied()->GetZ();
	}

	void SpriteBase::SetAngle(float fAngle) {
		GetAbstractProxied()->SetAngle(fAngle);
	}

	float SpriteBase::GetAngle() const {
		return GetAbstractProxied()->GetAngle();
	}

	void SpriteBase::SetZoomX(float fZoomX) {
		GetAbstractProxied()->SetZoomX(fZoomX);
	}

	float SpriteBase::GetZoomX() const {
		return GetAbstractProxied()->GetZoomX();
	}

	void SpriteBase::SetZoomY(float fZoomY) {
		GetAbstractProxied()->SetZoomY(fZoomY);
	}

	float SpriteBase::GetZoomY() const {
		return GetAbstractProxied()->GetZoomY();
	}

	void SpriteBase::SetOX(float fOX) {
		GetAbstractProxied()->SetOX(fOX);
	}

	float SpriteBase::GetOX() const {
		return GetAbstractProxied()->GetOX();
	}

	void SpriteBase::SetOY(float fOY) {
		GetAbstractProxied()->SetOY(fOY);
	}

	float SpriteBase::GetOY() const {
		return GetAbstractProxied()->GetOY();
	}

	void SpriteBase::SetMirror(bool bMirror) {
		GetAbstractProxied()->SetMirror(bMirror);
	}

	bool SpriteBase::GetMirror() const {
		return GetAbstractProxied()->GetMirror();
	}

	void SpriteBase::SetVisible(bool bVisible) {
		GetAbstractProxied()->SetVisible(bVisible);
	}

	bool SpriteBase::GetVisible() const {
		return GetAbstractProxied()->GetVisible();
	}

	void SpriteBase::SetOpacity(float fOpacity) {
		GetAbstractProxied()->SetOpacity(fOpacity);
	}

	float SpriteBase::GetOpacity() const {
		return GetAbstractProxied()->GetOpacity();
	}

	void SpriteBase::SetTone(Tone *& pTone) {
		GetAbstractProxied()->SetTone(pTone);
	}

	Tone * SpriteBase::GetTone() const {
		return GetAbstractProxied()->GetTone();
	}

	ResultCode SpriteBase::Update() {
		return GetAbstractProxied()->Update();
	}

	ResultCode SpriteBase::SetEffect(Effect::EffectBase* pEffect) {
		return GetAbstractProxied()->SetEffect(pEffect);
	}
}
