//
// Created by Huisama on 2019-03-21.
//

#ifndef _H_SPRITEINDEXEDTEST_
#define _H_SPRITEINDEXEDTEST_


#include "TestUnit.h"

class SpriteIndexedTest : public TestUnit {
public:
    SpriteIndexedTest() = default;
    ~SpriteIndexedTest() override = default;

    SpriteIndexed* m_pSprite = nullptr;
    Bitmap* m_pBitmap = nullptr;

    void TestInitialize() override {
//        std::vector<SpriteIndexed*> vcSprites = {};
//        for (size_t i = 0; i < 5; ++i) {
            m_pBitmap = Bitmap::Create(L"image/awesomeface.png");

            m_pSprite = SpriteIndexed::Create(3, 3);
            m_pSprite->SetBitmap(m_pBitmap);
//            auto g = RandInRange(0.1f, 1.0f);
//            m_pSprite->SetX(RandInRange(0.0f, 1.0f) * 1600);
//            m_pSprite->SetY(RandInRange(0.0f, 1.0f) * 900);
//
//            const auto fZoomRate = RandInRange(0.5f, 4.0f);
//            m_pSprite->SetZoomX(fZoomRate);
//            m_pSprite->SetZoomY(fZoomRate);
//            m_pSprite->SetAngle(RandInRange(0.0f, 1.0f) * 360);
//            vcSprites.push_back(m_pSprite);
//        }

    }

    void TestMain() override {
        auto pGraphics = AppFactory::GetGraphics();
        auto pApp = AppFactory::GetApplication();

        while (!pApp->IsQuited()) {
            pGraphics->Update();
        }

    }

    void TestTerminate() override {
        SpriteIndexed::Release(m_pSprite);
        Bitmap::Release(m_pBitmap);
    }


};


#endif //_H_SPRITEINDEXEDTEST_
