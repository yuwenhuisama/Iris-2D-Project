#ifndef _H_BITMAP_
#define _H_BITMAP_

#include "Proxy.h"
#include "IBitmap.h"

#undef DrawText

namespace Iris2D {

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
	* Iris 2D Bitmap ��
	*
	* һ�� Bitmap �����ڴ���һϵ�е����ص㣬��Щ���ص���ԴӴ����е�ͼ���ļ��д���Ҳ����ֱ�����ڴ����ֶ�������
	*
	* Iris 2D �е��κ�ͼ�γ������˵����һ�� Bitmap ���û��������Դ��� Bitmap �������Զ� Bitmap ����һЩ��������������ֵȡ�
	*/
	class Bitmap : public IBitmap, public Proxy<IBitmap> {
	public:
		/**
		* \~english
		* Create a bitmap from image file in hard disk.
		* @param wstrFileName The path of image file which can both be relative path and absolute path.
		* @return If bitmap has been created successfully pointer of BitmapDX will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* �Ӵ����е�ͼ���ļ��д���һ�� Bitmap ��
		* @param wstrFileName ͼ���ļ���·�����ȿ��������·��Ҳ�����Ǿ���·����
		* @return ����ɹ����� Bitmap ����ô���᷵�ظ� BitmapDX ��ָ�룬���򷵻� nullptr��
		*/
		static Bitmap* Create(const std::wstring& wstrFileName, IR_PARAM_RESULT);

		/**
		* \~english
		* Create a blank bitmap.
		* @param nWidth The pixel width of created bitmap.
		* @param nHeight The pixel height of created bitmap.
		* @return If bitmap has been created successfully pointer of BitmapDX will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* ����һ���հ׵�Bitmap��
		* @param nWidth ������ Bitmap �����ؿ�ȡ�
		* @param nHeight ������ Bitmap �����ظ߶ȡ�
		* @return ����ɹ����� Bitmap ����ô���᷵�ظ� BitmapDX ��ָ�룬���򷵻� nullptr��
		*/
		static Bitmap* Create(unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);

		/**
		* \~english
		* Generate a new bitmap by copying old bitmap.
		* @param pSrcBitmap The pointer to old bitmap.
		* @return If bitmap has been created successfully pointer of BitmapDX will be returned otherwise nullptr.
		* @see CopyFrom(BitmapDX* pSrcBitmap, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* ����һ���ϵ� Bitmap �Դ����µ� Bitmap��
		* @param pSrcBitmap ָ���ϵ� Bitmap ��ָ��
		* @return ����ɹ����� Bitmap ����ô���᷵�ظ� BitmapDX ��ָ�룬���򷵻� nullptr��
		* @see CopyFrom(BitmapDX* pSrcBitmap, IR_PARAM_RESULT)
		*/
		static Bitmap* Create(Bitmap* pSrcBitmap, IR_PARAM_RESULT);

		/**
		* \~english
		* Generate a new bitmap by copying old bitmap.
		* @param pSrcBitmap The pointer to old bitmap.
		* @return If bitmap has been created successfully pointer of BitmapDX will be returned otherwise nullptr.
		* @see CopyFrom(BitmapDX* pSrcBitmap, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* ����һ���ϵ� Bitmap �Դ����µ� Bitmap��
		* @param pSrcBitmap ָ���ϵ� Bitmap ��ָ��
		* @return ����ɹ����� Bitmap ����ô���᷵�ظ� BitmapDX ��ָ�룬���򷵻� nullptr��
		* @see Create(BitmapDX* pSrcBitmap, IR_PARAM_RESULT)
		*
		*/
		static Bitmap* CopyFrom(Bitmap* pSrcBitmap, IR_PARAM_RESULT);

		/**
		* \~english
		* Release a bitmap.
		* @param pBitmap A pointer to bitmap object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* �ͷ�һ�� Bitmap ��
		* @param pBitmap ָ��Ҫ���ͷŵ� Bitmap ��ָ�롣���ú���������֮�󣬴����ָ�뽫�ᱻ���ó� nullptr ��
		*/
		static void Release(Bitmap*& pBitmap);

	public:
		/**
		* \~english
		* Get the pixel width of current bitmap's image.
		* @return Pixel width of current bitmap's image.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Bitmap �����ؿ�ȡ�
		* @return ��ǰ Bitmap �����ؿ�ȡ�
		*/
		virtual unsigned int GetWidth() const;

		/**
		* \~english
		* Get the pixel height of current bitmap's image.
		* @return Pixel height of current bitmap's image.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Bitmap �����ظ߶ȡ�
		* @return ��ǰ Bitmap �����ظ߶ȡ�
		*/
		virtual unsigned int GetHeight() const;

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
		* ����Դ Btimap ��һ���ֵ�Ŀ�� Bitmap ֮�С�
		*
		* @param nDestX �� X Ŀ�� Bitmap �У�Դ Bitmap ��������������Ͻǵ� X ���ꡣ
		* @param nDestY �� Y Ŀ�� Bitmap �У�Դ Bitmap ��������������Ͻǵ� Y ���ꡣ
		* @param pSrcBitmap Դ Bitmap ��ָ�롣
		* @param pSrcRect Դ Bitmap �б�����������
		* @param fOpacity ���������ص�͸���ȣ���ֵ���� [0.0f, 255.0f]��
		* @return ������������ɹ������� true ���򷵻� false��
		*/
		virtual bool Blt(unsigned int nDestX, unsigned int nDestY, const Bitmap* pSrcBitmap, const IRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

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
		* ����Դ Btimap ��һ���ֵ�Ŀ�� Bitmap ֮�У���������Ŀ���������Դ����
		*
		* @param pDestRect ��ǰ Bitmap ��Ŀ������
		* @param pSrcBitmap Դ Bitmap ��ָ�롣
		* @param pSrcRect Դ Bitmap �б�����������
		* @param fOpacity ���������ص�͸���ȣ���ֵ���� [0.0f, 255.0f]��
		* @return ������������ɹ������� true ���򷵻� false��
		*/
		virtual bool StretchBlt(const IRect* pDestRect, const Bitmap* pSrcBitmap, const IRect* pSrcRect, float fOpacity, IR_PARAM_RESULT);

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
		* @see FilleRect(RectDX* pRect, ColorDX* pColor, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* ��ָ������ɫ��䵱ǰ Bitmap ��һ������
		*
		* @param nX	�������Ͻǵ� X ���ꡣ
		* @param nY �������Ͻǵ� Y ���ꡣ
		* @param nWidth ����Ŀ�ȡ�
		* @param nHeight ����ĸ߶ȡ�
		* @param pColor ������������ Color��
		* @return ����������ɹ������� true ���򷵻� false��
		* @see FilleRect(RectDX* pRect, ColorDX* pColor, IR_PARAM_RESULT)
		*/
		virtual bool FillRect(unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, const Color* pColor, IR_PARAM_RESULT);
		/**
		* \~english
		* Fill an area of current bitmap with specified color.
		*
		* @param pRect Rect used to describe the area.
		* @param pColor Color used to fill the area.
		* @return If fill operation has been successful true will be returned otherwise false.
		* @see FilleRect(RectDX* pRect, ColorDX* pColor, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* ��ָ������ɫ��䵱ǰ Bitmap ��һ������
		*
		* @param pRect ������������� Rect��
		* @param pColor ������������ Color��
		* @return ����������ɹ������� true ���򷵻� false��
		* @see FilleRect(RectDX* pRect, ColorDX* pColor, IR_PARAM_RESULT)
		*/
		virtual bool FillRect(const IRect* pRect, const Color* pColor, IR_PARAM_RESULT);

		/**
		* \~english
		* Clear current bitmap with color #00000000.
		* @return If clear operation has been successful true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* �� #00000000 �����ɫ��յ�ǰ Bitmap��
		* @return �����ղ����ɹ������� true ���򷵻� false��
		*/
		virtual bool Clear(IR_PARAM_RESULT);

		/**
		* \~english
		* Clear a rect area of current bitmap with color #00000000.
		*
		* @param nX X position of top left point of the area.
		* @param nY Y position of top left point of the area.
		* @param nWidth Width of the area.
		* @param nHeight Height of the area.
		* @return If clear operation has been successful true will be returned otherwise false.
		* @see ClearRect(RectDX* pRect, IR_PARAM_RESULT)
		*/
		/**
		* \~chinese
		* �� #00000000 �����ɫ�����ǰ Bitmap ��һ������
		*
		* @param nX	�������Ͻǵ� X ���ꡣ
		* @param nY �������Ͻǵ� Y ���ꡣ
		* @param nWidth ����Ŀ�ȡ�
		* @param nHeight ����ĸ߶ȡ�
		* @return �����ղ����ɹ������� true ���򷵻� false��
		* @see ClearRect(RectDX* pRect, IR_PARAM_RESULT)
		*/
		virtual bool ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
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
		* ʹ�� #00000000 �����ɫ ��յ�ǰ Bitmap ��һ�� Rect ����
		*
		* @param pRect ������������� Rect��
		* @return �����ղ����ɹ������� true ���򷵻� false��
		* @see ClearRect(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT)
		*/
		virtual bool ClearRect(const Rect* pRect, IR_PARAM_RESULT);

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
		* ��ȡ��ǰ Bitmap ָ����������ɫ��
		*
		* @param nX ��ǰ Bitmap ���ص� X ���ꡣ
		* @param nY ��ǰ Bitmap ���ص� Y ���ꡣ
		* @return ��� (nX, nY) �� Bitmap �ڲ��� ���᷵��(nX, nY) λ�������ص���ɫ�����򷵻�nullptr��
		*/
		virtual Color* GetPixel(unsigned int nX, unsigned int nY, IR_PARAM_RESULT) const;


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
		* @param nX ��ǰ Bitmap ���ص� X ���ꡣ
		* @param nY ��ǰ Bitmap ���ص� Y ���ꡣ
		* @param pColor ָ������ɫ��
		* @return ��� (nX, nY) �� Bitmap �ڲ����� Color ����Ч�ģ���ô�ͷ��� true ���򷵻� false��
		*/
		virtual bool SetPixel(unsigned int nX, unsigned int nY, const Color *pColor, IR_PARAM_RESULT);

		/**
		* \~english
		* Save current bitmap to a png file.
		*
		* @param wstrFilePath Path of the output png file.
		* @return If file is successfully generated true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* ����ǰ�� Bitmap ���浽һ�� png �ļ��С�
		*
		* @param wstrFilePath ����� png �ļ���·����
		* @return ����ļ��ɹ����ɣ����� true ���򷵻� false ��
		*/
		virtual bool SaveToFile(const std::wstring& wstrFilePath);

		/**
		* \~english
		* Change the hue value of current bitmap.
		*
		* @param fHue Hue value of current bitmap, using degree measure.
		* @return If hue value is changed successfully true will be returned otherwise false.
		*/
		/**
		* \~chinese
		* �ı䵱ǰ Bitmap ��ɫ��ֵ��
		*
		* @param fHue ��ǰ Bitmap ��ɫ��ֵ�����ýǶ��ơ�
		* @return ���ɫ��ֵ���ɹ��ı䷵�� true ���򷵻� false��
		*/
		virtual bool HueChange(float fHue, IR_PARAM_RESULT);

		virtual void SetFont(Font*& pFont);
		virtual Font* GetFont() const;

		virtual unsigned int TextSize(const Font* pFont, const std::wstring& wstrText, IR_PARAM_RESULT);
		virtual bool DrawText(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT);
		virtual bool DrawText(const Rect* pRect, const std::wstring& wstrText, AlignType nAlign, IR_PARAM_RESULT);

		virtual bool Dispose();

		private:
			Bitmap(IBitmap* pBitmap);
			~Bitmap() = default;
	};
};

#endif // !_H_BITMAP_
