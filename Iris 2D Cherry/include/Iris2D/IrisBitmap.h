#ifndef _H_IRISBITMAP_
#define _H_IRISBITMAP_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisTexture;

#if ENGLISH
	/**
	* Bitmap class of Iris 2D
	*
	* A bitmap is a sequence of pixels in memory which can be created from image files in hard disk or created manually in memory directly.
	*
	* Every image in Iris 2D application is abstractly a bitmap. User can not only create bitmap but also can do some oparation on it such as draw text and so on.
	*/
#elif CHINESE
	/**
	* Iris 2D Bitmap 类
	*
	* 一个 Bitmap 就是内存中一系列的像素点，这些像素点可以从磁盘中的图像文件中创建也可以直接在内存中手动创建。
	*
	* Iris 2D 中的任何图形抽象地来说都是一个 Bitmap 。用户不仅可以创建 Bitmap ，还可以对 Bitmap 进行一些操作，如绘制文字等。
	*/
#endif
	class IrisBitmap
	{
	private:
		IrisTexture* m_pTexture = nullptr;

	public:
#if ENGLISH
		/**
		* Create a bitmap from image file in hard disk.
		* @param wstrFileName The path of image file which can both be relative path and absolute path.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		*/
#elif CHINESE
		/**
		* 从磁盘中的图像文件中创建一个 Bitmap 。
		* @param wstrFileName 图像文件的路径，既可以是相对路径也可以是绝对路径。
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		*/
#endif
		static IrisBitmap* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);

#if ENGLISH
		/**
		* Create a blank bitmap.
		* @param nWidth The pixel width of created bitmap.
		* @param nHeight The pixel height of created bitmap.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		*/
#elif CHINESE
		/**
		* 创建一个空白的Bitmap。
		* @param nWidth 创建的 Bitmap 的像素宽度。
		* @param nHeight 创建的 Bitmap 的像素高度。
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		*/
#endif

		static IrisBitmap* Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

#if ENGLISH
		/**
		 * Release a bitmap.
		 * @param pBitmap A pointer to bitmap object to be released. After this function called, pointer taken will be set to nullptr.
		 */
#elif CHINESE
		/**
		* 释放一个 Bitmap 。
		* @param pBitmap 指向将要被释放的 Bitmap 的指针。当该函数被调用之后，传入的指针将会被设置成 nullptr 。
		*/
#endif
		static void Release(IrisBitmap*& pBitmap);

#if ENGLISH
		/**
		* Get the pixel width of current bitmap's image.
		* @return Pixel width of current bitmap's image.
		*/
#elif CHINESE
		/**
		* 获取当前 Bitmap 的像素宽度。
		* @return 当前 Bitmap 的像素宽度。
		*/
#endif
		unsigned int GetWidth();

#if ENGLISH
		/**
		* Get the pixel height of current bitmap's image.
		* @return Pixel height of current bitmap's image.
		*/
#elif CHINESE
		/**
		* 获取当前 Bitmap 的像素高度。
		* @return 当前 Bitmap 的像素高度。
		*/
#endif
		unsigned int GetHeight();

		IrisTexture* GetTexture();		
	private:
		IrisBitmap() = default;
		~IrisBitmap();
	};

}
#endif // !_H_IRISBITMAP_
