#ifndef _H_IRISBITMAP_
#define _H_IRISBITMAP_

#include "../IrisCommon.h"

namespace Iris2D
{
	class IrisTexture;
	class IrisRect;
	class IrisColor;

	/**
	* \~english
	* Bitmap class of Iris 2D
	*
	* A bitmap is a sequence of pixels in memory which can be created from image files in hard disk or created manually in memory directly.
	*
	* Every image in Iris 2D application is abstractly a bitmap. User can not only create bitmap but also can do some oparation on it such as draw text and so on.
	*/
	/**
	* \~chinese
	* Iris 2D Bitmap 类
	*
	* 一个 Bitmap 就是内存中一系列的像素点，这些像素点可以从磁盘中的图像文件中创建也可以直接在内存中手动创建。
	*
	* Iris 2D 中的任何图形抽象地来说都是一个 Bitmap 。用户不仅可以创建 Bitmap ，还可以对 Bitmap 进行一些操作，如绘制文字等。
	*/
	class IrisBitmap
	{
	private:
		IrisTexture* m_pTexture = nullptr;

	public:

		/**
		* \~english
		* Create a bitmap from image file in hard disk.
		* @param wstrFileName The path of image file which can both be relative path and absolute path.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* 从磁盘中的图像文件中创建一个 Bitmap 。
		* @param wstrFileName 图像文件的路径，既可以是相对路径也可以是绝对路径。
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		*/
		static IrisBitmap* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);

		/**
		* \~english
		* Create a blank bitmap.
		* @param nWidth The pixel width of created bitmap.
		* @param nHeight The pixel height of created bitmap.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* 创建一个空白的Bitmap。
		* @param nWidth 创建的 Bitmap 的像素宽度。
		* @param nHeight 创建的 Bitmap 的像素高度。
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		*/
		static IrisBitmap* Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		/**
		* \~english
		* Release a bitmap.
		* @param pBitmap A pointer to bitmap object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* 释放一个 Bitmap 。
		* @param pBitmap 指向将要被释放的 Bitmap 的指针。当该函数被调用之后，传入的指针将会被设置成 nullptr 。
		*/
		static void Release(IrisBitmap*& pBitmap);

		/**
		* \~english
		* Get the pixel width of current bitmap's image.
		* @return Pixel width of current bitmap's image.
		*/
		/**
		* \~chinese
		* 获取当前 Bitmap 的像素宽度。
		* @return 当前 Bitmap 的像素宽度。
		*/
		unsigned int GetWidth();

		/**
		* \~english
		* Get the pixel height of current bitmap's image.
		* @return Pixel height of current bitmap's image.
		*/
		/**
		* \~chinese
		* 获取当前 Bitmap 的像素高度。
		* @return 当前 Bitmap 的像素高度。
		*/
		unsigned int GetHeight();

		/**
		* \~english
		* Copy part of source bitmap to destination bitmap.
		* 
		* @param nDestX X position in destination bitmap, which is the top left x position of copied area in source bitmap.
		* @param nDestY Y position in destination bitmap, which is the top left y position of copied area in source bitmap.
		* @param pSrcBitmap The pointer to source bitmap.
		* @param pSrcRect The copied area in source bitmap.
		* @param fOpacity The opacity of pixels in copied area whose value is in [0.0, 255.0f].
		* @return If copy operation has been successful true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 拷贝源 Btimap 的一部分到目标 Bitmap 之中。
		*
		* @param nDestX 在 X 目标 Bitmap 中，源 Bitmap 被拷贝区域的左上角的 X 坐标。
		* @param nDestY 在 Y 目标 Bitmap 中，源 Bitmap 被拷贝区域的左上角的 Y 坐标。
		* @param pSrcBitmap 源 Bitmap 的指针。
		* @param pSrcRect 源 Bitmap 中被拷贝的区域。
		* @param fOpacity 拷贝后像素的透明度，其值介于 [0.0f, 255.0f]。
		* @return 如果拷贝操作成功，返回 true 否则返回 false。
		*/
		bool Blt(unsigned int nDestX, unsigned int nDestY, IrisBitmap* pSrcBitmap, IrisRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

		/**
		* \~english
		* Copy part of source bitmap to destination bitmap allowing to scretch either destination area or source area.
		*
		* @param pDestRect The distination area in current bitmap.
		* @param pSrcBitmap The pointer to source bitmap.
		* @param pSrcRect The copied area in source bitmap.
		* @param fOpacity The opacity of pixels in copied area whose value is in [0.0, 255.0f].
		* @return If copy operation has been successful true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 拷贝源 Btimap 的一部分到目标 Bitmap 之中，允许拉伸目标区域或者源区域。
		*
		* @param pDestRect 当前 Bitmap 的目标区域。
		* @param pSrcBitmap 源 Bitmap 的指针。
		* @param pSrcRect 源 Bitmap 中被拷贝的区域。
		* @param fOpacity 拷贝后像素的透明度，其值介于 [0.0f, 255.0f]。
		* @return 如果拷贝操作成功，返回 true 否则返回 false。
		*/
		bool StretchBlt(IrisRect* pDestRect, IrisBitmap* pSrcBitmap, IrisRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

		/**
		* \~english
		* Fill an area of current bitmap with specified color.
		*
		* @param nX X position of top left point of the area.
		* @param nY Y position of top left point of the area.
		* @param nWidth Width of the area.
		* @param nHeight Height of the area.
		* @param pColor Color used to fill the area.
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 用指定的颜色填充当前 Bitmap 的一个区域。
		*
		* @param nX	区域左上角的 X 坐标。
		* @param nY 区域左上角的 Y 坐标。
		* @param nWidth 区域的宽度。
		* @param nHeight 区域的高度。
		* @param pColor 用来填充区域的 Color。
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, IrisColor* pColor, IR_PARAM_RESULT);
		/**
		* \~english
		* Fill an area of current bitmap with specified color.
		*
		* @param pRect Rect used to describe the area.
		* @param pColor Color used to fill the area.
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 用指定的颜色填充当前 Bitmap 的一个区域。
		*
		* @param pRect 用来描述区域的 Rect。
		* @param pColor 用来填充区域的 Color。
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		bool FillRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT);

		bool Clear(IR_PARAM_RESULT);

		bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		bool ClearRect(IrisRect* pRect, IR_PARAM_RESULT);

		IrisColor* GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT);
		void SetPixel(unsigned int nX, unsigned int nY, IrisColor *pColor, IR_PARAM_RESULT);

		void SaveToFile(const std::wstring& wstrFilePath);

		IrisTexture* GetTexture();		
	private:
		IrisBitmap() = default;
		~IrisBitmap();
	};

}
 // !_H_IRISBITMAP_
#endif