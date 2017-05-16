#ifndef _H_IRISBITMAP_
#define _H_IRISBITMAP_

#include "../IrisCommon.h"
#include "Iris2D Util/IrisRefCounter.h"

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
	class IrisBitmap : public IrisRefCounter
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
		* Generate a new bitmap by copying old bitmap.
		* @param pSrcBitmap The pointer to old bitmap.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		* @see CopyFrom(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 复制一个老的 Bitmap 以创建新的 Bitmap。
		* @param pSrcBitmap 指向老的 Bitmap 的指针
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		* @see CopyFrom(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT)
		*/
		static IrisBitmap* Create(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT);

		/**
		* \~english
		* Generate a new bitmap by copying old bitmap.
		* @param pSrcBitmap The pointer to old bitmap.
		* @return If bitmap has been created successfully pointer of IrisBitmap will be returned otherwise nullptr.
		* @see CopyFrom(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 复制一个老的 Bitmap 以创建新的 Bitmap。
		* @param pSrcBitmap 指向老的 Bitmap 的指针
		* @return 如果成功创建 Bitmap ，那么将会返回该 IrisBitmap 的指针，否则返回 nullptr。
		* @see Create(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT)
		*
		*/
		static IrisBitmap* CopyFrom(IrisBitmap* pSrcBitmap, IR_PARAM_RESULT);

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
		unsigned int GetWidth() const;

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
		unsigned int GetHeight() const;

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
		bool Blt(unsigned int nDestX, unsigned int nDestY,  const IrisBitmap* pSrcBitmap, const IrisRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

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
		bool StretchBlt(const IrisRect* pDestRect, const IrisBitmap* pSrcBitmap, const IrisRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

		/**
		* \~english
		* Fill an area of current bitmap with specified color.
		*
		* @param nX X position of top left point of the area.
		* @param nY Y position of top left point of the area.
		* @param nWidth Width of the area.
		* @param nHeight Height of the area.
		* @param pColor Color used to fill the area.
		* @return If fill operation has been successful true will be returned otherwise false.
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
		* @return 如果填充操作成功，返回 true 否则返回 false。
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const IrisColor* pColor, IR_PARAM_RESULT);
		/**
		* \~english
		* Fill an area of current bitmap with specified color.
		*
		* @param pRect Rect used to describe the area.
		* @param pColor Color used to fill the area.
		* @return If fill operation has been successful true will be returned otherwise false.
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 用指定的颜色填充当前 Bitmap 的一个区域。
		*
		* @param pRect 用来描述区域的 Rect。
		* @param pColor 用来填充区域的 Color。
		* @return 如果填充操作成功，返回 true 否则返回 false。
		* @see FilleRect(IrisRect* pRect, IrisColor* pColor, IR_PARAM_RESULT)
		*/
		bool FillRect(const IrisRect* pRect, const IrisColor* pColor, IR_PARAM_RESULT);
		
		/**
		* \~english
		* Clear current bitmap with color #00000000.
		* @return If clear operation has been successful true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 用 #00000000 这个颜色清空当前 Bitmap。
		* @return 如果清空操作成功，返回 true 否则返回 false。
		*/
		bool Clear(IR_PARAM_RESULT);
		
		/**
		* \~english
		* Clear a rect area of current bitmap with color #00000000.
		*
		* @param nX X position of top left point of the area.
		* @param nY Y position of top left point of the area.
		* @param nWidth Width of the area.
		* @param nHeight Height of the area.
		* @return If clear operation has been successful true will be returned otherwise false.
		* @see ClearRect(IrisRect* pRect, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 用 #00000000 这个颜色情况当前 Bitmap 的一个区域。
		*
		* @param nX	区域左上角的 X 坐标。
		* @param nY 区域左上角的 Y 坐标。
		* @param nWidth 区域的宽度。
		* @param nHeight 区域的高度。
		* @return 如果清空操作成功，返回 true 否则返回 false。
		* @see ClearRect(IrisRect* pRect, IR_PARAM_RESULT)
		*/
		bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		/**
		* \~english
		* Clear a rect area of current bitmap with color #00000000.
		*
		* @param pRect Rect used to describe the area.
		* @param pColor Color used to fill the area.
		* @return If clear operation has been successful true will be returned otherwise false.
		* @see ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* 使用 #00000000 这个颜色 清空当前 Bitmap 的一个 Rect 区域。
		*
		* @param pRect 用来描述区域的 Rect。
		* @param pColor 用来填充区域的 Color。
		* @return 如果清空操作成功，返回 true 否则返回 false。
		* @see ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT)
		*/
		bool ClearRect(const IrisRect* pRect, IR_PARAM_RESULT);

				/**
		* \~english
		* Get specified pixel's color of current bitmap.
		*
		* @param nX X position of the pixel of current bitmap.
		* @param nY Y position of the pixel of current bitmap.
		* @return If (nX, nY) is inside the bitmap, color of the pixel of position (nX, nY) will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* 获取当前 Bitmap 指定的像素颜色。
		*
		* @param nX 当前 Bitmap 像素的 X 坐标。
		* @param nY 当前 Bitmap 像素的 Y 坐标。
		* @return 如果 (nX, nY) 在 Bitmap 内部， 将会返回(nX, nY) 位置上像素的颜色，否则返回nullptr。
		*/
		IrisColor* GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const;


		/**
		* \~english
		* Get specified pixel's color of current bitmap.
		*
		* @param nX X position of the pixel of current bitmap.
		* @param nY Y position of the pixel of current bitmap.
		* @param pColor Specified color.
		* @return If (nX, nY) is in inside the bitmap and color taken is valid, true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 
		* @param nX 当前 Bitmap 像素的 X 坐标。
		* @param nY 当前 Bitmap 像素的 Y 坐标。
		* @param pColor 指定的颜色。
		* @return 如果 (nX, nY) 在 Bitmap 内部并且 Color 是有效的，那么就返回 true 否则返回 false。
		*/
		bool SetPixel(unsigned int nX, unsigned int nY, const IrisColor *pColor, IR_PARAM_RESULT);
		
		/**
		* \~english
		* Save current bitmap to a png file.
		*
		* @param wstrFilePath Path of the output png file.
		* @return If file is successfully generated true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 将当前的 Bitmap 保存到一个 png 文件中。
		*
		* @param wstrFilePath 输出的 png 文件的路径。
		* @return 如果文件成功生成，返回 true 否则返回 false 。
		*/
		bool SaveToFile(const std::wstring& wstrFilePath);


		/**
		* \~english
		* Change the hue value of current bitmap.
		*
		* @param fHue Hue value of current bitmap, using degree measure.
		* @return If hue value is changed successfully true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* 改变当前 Bitmap 的色调值。
		*
		* @param fHue 当前 Bitmap 的色调值，采用角度制。
		* @return 如果色调值被成功改变返回 true 否则返回 false。
		*/
		bool HueChange(float fHue, IR_PARAM_RESULT);

		bool Dispose();

		IrisTexture* GetTexture() const;
	private:
		IrisBitmap() = default;
		~IrisBitmap();
	};

}
 // !_H_IRISBITMAP_
#endif