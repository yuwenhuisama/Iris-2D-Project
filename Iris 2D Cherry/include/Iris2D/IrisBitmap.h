#ifndef _H_IRISBITMAP_
#define _H_IRISBITMAP_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisTexture;
	class IrisBitmap
	{
	private:
		IrisTexture* m_pTexture = nullptr;

	public:
		static IrisBitmap* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);
		static void Release(IrisBitmap*& pBitmap);

		IrisTexture* GetTexture();

		unsigned int GetWidth();
		unsigned int GetHeight();
		
	private:
		IrisBitmap() = default;
		~IrisBitmap();
	};

}
#endif // !_H_IRISBITMAP_
