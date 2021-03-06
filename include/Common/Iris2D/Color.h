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
	* Iris 2D Color 类
	*
	* 一个 Color 是一个包括 R/G/B/A 属性的对象。
	*
	* Color 每个属性都是一个介于 [0, 255] 的 byte 。
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
		* 创建一个 Color 对象。
		* @param cRed 所创建的 Color 对象的 Red 分量.
		* @param cGreen 所创建的 Color 对象的 Green 分量.
		* @param cBlue 所创建的 Color 对象的 Blue 分量.
		* @param cAlpha 所创建的 Color 对象的 Alpha 分量.
		* @return 如果 Color 对象创建成功那么返回它的指针否则返回 nullptr。
		*/
		static Color* Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);

		/**
		* \~english
		* Release a color.
		* @param pColor A pointer to color object to be released. After this function called, pointer taken will be set to nullptr.
		*/
		/**
		* \~chinese
		* 释放一个 Color 对象。
		* @param pColor 指向将要被释放的 Color 对象的指针。当该函数被调用之后，传入的指针将会被设置为 nullptr。
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
		* 设置当前对象的 Red 属性。
		* @param cRed Red 属性的值。
		*/
		void SetRed(unsigned char cRed) override;
		/**
		* \~english
		* Get the red property of current color.
		* @return The red property of current color.
		*/
		/**
		* \~chinese
		* 获取当前 Color 的 Red 值。
		* @return 当前 Color 的 Red 值。
		*/
		unsigned char GetRed() const override;

		/**
		* \~english
		* Set the green property of current color.
		* @param cGreen Value of green property.
		*/
		/**
		* \~chinese
		* 设置当前对象的 Green 属性。
		* @param cGreen Green 属性的值。
		*/
		void SetGreen(unsigned char cGreen) override;
		/**
		* \~english
		* Get the green property of current color.
		* @return The green property of current color.
		*/
		/**
		* \~chinese
		* 获取当前 Color 的 Green 值。
		* @return 当前 Color 的 Green 值。
		*/
		unsigned char GetGreen() const override;

		/**
		* \~english
		* Set the blue property of current color.
		* @param cBlue Value of blue property.
		*/
		/**
		* \~chinese
		* 设置当前对象的 Blue 属性。
		* @param cBlue Blue 属性的值。
		*/
		void SetBlue(unsigned char cBlue) override;
		/**
		* \~english
		* Get the blue property of current color.
		* @return The blue property of current color.
		*/
		/**
		* \~chinese
		* 获取当前 Color 的 Blue 值。
		* @return 当前 Color 的 Blue 值。
		*/
		unsigned char GetBlue() const override;

		/**
		* \~english
		* Set the alpha property of current color.
		* @param cAlpha Value of alpha property.
		*/
		/**
		* \~chinese
		* 设置当前对象的 Alpha 属性。
		* @param cAlpha Alpha 属性的值。
		*/
		void SetAlpha(unsigned char cAlpha) override;
		/**
		* \~english
		* Get the alpha property of current color.
		* @return The alpha property of current color.
		*/
		/**
		* \~chinese
		* 获取当前 Color 的 Alpha 值。
		* @return 当前 Color 的 Alpha 值。
		*/
		unsigned char GetAlpha() const override;

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
		* 设置当前 Color 的R/G/B/A 属性。
		* @param cRed Red 属性的值。
		* @param cGreen Green 属性的值。
		* @param cBlue Blue 属性的值。
		* @param cAlpha Alpha 属性的值。
		*/
		void Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) override;

		private:
			Color(IColor* pProxied);
			~Color() = default;
	};

};

#endif // !_H_COLOR_
