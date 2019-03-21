//
// Created by Huisama on 2019-03-21.
//

#ifndef _H_SPRITESTATICTEST_
#define _H_SPRITESTATICTEST_


#include "TestUnit.h"

class SpriteStaticTest : public TestUnit {
protected:
    SpriteStatic* m_pSprite = nullptr;
    SpriteStatic* m_pSprite2 = nullptr;
    Bitmap* m_pBitmap = nullptr;
    Bitmap* m_pBitmap2 = nullptr;

public:
    SpriteStaticTest() = default;
    ~SpriteStaticTest() override = default;

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
    }

    void TestMain() override {
        auto pGraphics = AppFactory::GetGraphics();
        auto pApp = AppFactory::GetApplication();

        auto fAngle = 0.0f;
        while (!pApp->IsQuited()) {
            fAngle += 2.0f;
            m_pSprite->SetAngle(fAngle);
            pGraphics->Update();
        }
    }

    void TestTerminate() override {
        Bitmap::Release(m_pBitmap);
        Bitmap::Release(m_pBitmap2);
    }

};


#endif //_H_SPRITESTATICTEST_
