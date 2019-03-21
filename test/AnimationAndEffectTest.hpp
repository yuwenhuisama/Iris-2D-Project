#ifndef _H_ANIMATIONANDEFFECT_TEST_
#define _H_ANIMATIONANDEFFECT_TEST_
#include "TestUnit.h"

class AnimationAndEffectTest : public TestUnit {
protected:
    SpriteStatic* m_pSprite = nullptr;
    SpriteStatic* m_pSprite2 = nullptr;
    Bitmap* m_pBitmap = nullptr;
    Bitmap* m_pBitmap2 = nullptr;

    Color* m_pColor = nullptr;
    Effect::EffectFlash* m_pEffect= nullptr;
    Animation::AnimationAngleProperty *m_pAnimation = nullptr;
    Animation::AnimationPositionProperty *m_pAnimation2 = nullptr;
    Animation::AnimationZoomProperty *m_pAnimation3 = nullptr;
    Animation::AnimationSerialGroup* m_pAnimationGroup = nullptr;

public:
    AnimationAndEffectTest() = default;
    ~AnimationAndEffectTest() override = default;

    void TestInitialize() override {
        m_pBitmap = Bitmap::Create(L"image/kurumi.jpg");
        m_pSprite = SpriteStatic::Create();
        m_pSprite->SetBitmap(m_pBitmap);
        m_pSprite->SetZ(4.0f);

        m_pBitmap2 = Bitmap::Create(L"image/leimu.jpg");
        m_pSprite2 = SpriteStatic::Create();
        m_pSprite2->SetX(200.0f);
        m_pSprite2->SetBitmap(m_pBitmap2);
        m_pSprite2->SetZ(5.0f);

        m_pColor = Color::Create(255, 255, 255, 255);
        m_pEffect = Effect::EffectFlash::Create(m_pColor, 2, true);

        m_pSprite->SetEffect(m_pEffect);

        m_pAnimation = Animation::AnimationAngleProperty::Create(m_pSprite2);
        m_pAnimation->SetStartKeyFrame(0.0f);
        m_pAnimation->SetEndKeyFrame(360.0f);
        m_pAnimation->SetTotalTime(300);
        m_pAnimation->SetLoop(false);

        m_pAnimation2 = Animation::AnimationPositionProperty::Create(m_pSprite2);
        m_pAnimation2->SetStartKeyFrame({ 0, 0 });
        m_pAnimation2->SetEndKeyFrame({ 0, 0 });
        m_pAnimation2->SetTotalTime(400);
        m_pAnimation2->SetKeyFrameList({
        	{ 0.25f,{ 0, 400 } },
        	{ 0.5f,{ 400, 400 } },
        	{ 0.75f,{ 400, 0 } }
        	});
        m_pAnimation2->SetLoop(false);

        m_pAnimation3 = Animation::AnimationZoomProperty::Create(m_pSprite2);
        m_pAnimation3->SetStartKeyFrame({ 0.5, 0.5 });
        m_pAnimation3->SetEndKeyFrame({ 1.0, 1.0 });
        m_pAnimation3->SetTotalTime(400);
        m_pAnimation3->SetKeyFrameList({
        	{ 0.25f,{ 0.75, 0.5 } },
        	{ 0.5f,{ 0.75, 0.75 } },
        	{ 0.75f,{ 1.0, 0.75 } }
        	});
        m_pAnimation3->SetLoop(false);

        m_pAnimation3->AddCallBack(0.2f, [](float fProgress) -> void {
        	PrintFormatDebugMessageW(L"Call back at progress %1%", fProgress);
        });

        m_pAnimation3->AddCallBack(0.8f, [](float fProgress) -> void {
        	PrintFormatDebugMessageW(L"Call back at progress %1%", fProgress);
        });

        m_pAnimationGroup = Animation::AnimationSerialGroup::Create();
        m_pAnimationGroup->AddAnimation(m_pAnimation);
        m_pAnimationGroup->AddAnimation(m_pAnimation2);
        m_pAnimationGroup->AddAnimation(m_pAnimation3);
        m_pAnimationGroup->SetLoop(true);
    }

	void TestMain() override {

        auto pGraphics = AppFactory::GetGraphics();
        auto pApp = AppFactory::GetApplication();

        m_pAnimationGroup->Start();

        auto fAngle = 0.0f;
        while (!pApp->IsQuited()) {
            m_pAnimationGroup->Update();
            m_pEffect->Update();
            pGraphics->Update();
        }
	}

	void TestTerminate() override {
        SpriteStatic::Release(m_pSprite);
        SpriteStatic::Release(m_pSprite2);
        Bitmap::Release(m_pBitmap);
        Bitmap::Release(m_pBitmap2);

        Color::Release(m_pColor);
        Effect::EffectFlash::Release(m_pEffect);
        Animation::AnimationAngleProperty::Release(m_pAnimation);
        Animation::AnimationPositionProperty::Release(m_pAnimation2);
        Animation::AnimationZoomProperty::Release(m_pAnimation3);

    }

};

#endif