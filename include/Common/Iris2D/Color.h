#ifndef _H_COLOR_
#define _H_COLOR_

#include "Proxy.h"
#include "IColor.h"

namespace Iris2D {
	/**
	* \~english
	* Color class of Iris 2D
	*
	* A color is an object with R/G/B/A properties.
	*
	* Each property of a color is a byte valued [0, 255].
	*/
	/**
	* \~chinese
	* Iris 2D Color ��
	*
	* һ�� Color ��һ������ R/G/B/A ���ԵĶ���
	*
	* Color ÿ�����Զ���һ������ [0, 255] �� byte ��
	*/
	class Color : public IColor, public Proxy<IColor> {
	public:
		/**
		* \~english
		* Create a color object.
		* @param cRed Red property of created color.
		* @param cGreen Green property of created color.
		* @param cBlue Blue property of created color.
		* @param cAlpha Alpha property of created color.
		* @return If color has been created successfully pointer of ColorDX will be returned otherwise nullptr.
		*/
		/**
		* \~chinese
		* ����һ�� Color ����
		* @param cRed �������� Color ����� Red ����.
		* @param cGreen �������� Color ����� Green ����.
		* @param cBlue �������� Color ����� Blue ����.
		* @param cAlpha �������� Color ����� Alpha ����.
		* @return ��� Color ���󴴽��ɹ���ô��������ָ����򷵻� nullptr��
		*/
		static Color* Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);

		/**
		* \~english
		* Release a color.
		* @param pColor A pointer to color object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* �ͷ�һ�� Color ����
		* @param pColor ָ��Ҫ���ͷŵ� Color �����ָ�롣���ú���������֮�󣬴����ָ�뽫�ᱻ����Ϊ nullptr��
		*/
		static void Release(Color*& pColor);

	public:

		/**
		* \~english
		* Set the red property of current color.
		* @param cRed Value of red property.
		*/
		/**
		* \~chinese
		* ���õ�ǰ����� Red ���ԡ�
		* @param cRed Red ���Ե�ֵ��
		*/
		virtual void SetRed(unsigned char cRed);
		/**
		* \~english
		* Get the red property of current color.
		* @return The red property of current color.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Color �� Red ֵ��
		* @return ��ǰ Color �� Red ֵ��
		*/
		virtual unsigned char GetRed() const;

		/**
		* \~english
		* Set the green property of current color.
		* @param cGreen Value of green property.
		*/
		/**
		* \~chinese
		* ���õ�ǰ����� Green ���ԡ�
		* @param cGreen Green ���Ե�ֵ��
		*/
		virtual void SetGreen(unsigned char cGreen);
		/**
		* \~english
		* Get the green property of current color.
		* @return The green property of current color.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Color �� Green ֵ��
		* @return ��ǰ Color �� Green ֵ��
		*/
		virtual unsigned char GetGreen() const;

		/**
		* \~english
		* Set the blue property of current color.
		* @param cBlue Value of blue property.
		*/
		/**
		* \~chinese
		* ���õ�ǰ����� Blue ���ԡ�
		* @param cBlue Blue ���Ե�ֵ��
		*/
		virtual void SetBlue(unsigned char cBlue);
		/**
		* \~english
		* Get the blue property of current color.
		* @return The blue property of current color.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Color �� Blue ֵ��
		* @return ��ǰ Color �� Blue ֵ��
		*/
		virtual unsigned char GetBlue() const;

		/**
		* \~english
		* Set the alpha property of current color.
		* @param cAlpha Value of alpha property.
		*/
		/**
		* \~chinese
		* ���õ�ǰ����� Alpha ���ԡ�
		* @param cAlpha Alpha ���Ե�ֵ��
		*/
		virtual void SetAlpha(unsigned char cAlpha);
		/**
		* \~english
		* Get the alpha property of current color.
		* @return The alpha property of current color.
		*/
		/**
		* \~chinese
		* ��ȡ��ǰ Color �� Alpha ֵ��
		* @return ��ǰ Color �� Alpha ֵ��
		*/
		virtual unsigned char GetAlpha() const;

		/**
		* \~english
		* Set R/G/B/A properties of current color.
		* @param cRed Value of red property.
		* @param cGreen Value of green property.
		* @param cBlue Value of green property.
		* @param cAlpha Value of alpha property.
		*/
		/**
		* \~chinese
		* ���õ�ǰ Color ��R/G/B/A ���ԡ�
		* @param cRed Red ���Ե�ֵ��
		* @param cGreen Green ���Ե�ֵ��
		* @param cBlue Blue ���Ե�ֵ��
		* @param cAlpha Alpha ���Ե�ֵ��
		*/
		virtual void Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);

		private:
			Color() = delete;

			Color(IColor* pProxied);
			~Color() = default;
	};

};

#endif // !_H_COLOR_
