# Iris 2D Biscuit 更新日志
---

###版本号 v2.06.13.1
>**更新日期：2015.6.13**

</br>

>####Iris 2D Biscuit-Turkey(SC)####
>#####全局#####
>>`新增:`

>>**(重要）** 1. 新增Iris2D命名空间，头文件包含结构优化调整，全局范围内的许多函数加上了执行结果查询的参数**IrisResult* _rResult**，以及相关的错误处理宏。
2. 修正了函数名大小写的问题。
3. 删除了一些类中某些无用的成员变量，修改了成员变量的访问权限，以便于扩展继承。

>#####IrisEncripedResourceManager#####
>>`新增`

>>1. 新增了**IrisEncripedResourceManager**类用于对封包数据的管理（配合Iris Tools中的工具）。

>#####IrisApp#####
>>`新增：`

>>1. 增加了**ToggleWindowMode()**函数，用于切换全屏/窗口（附属OnDeviceLost()和OnDeviceRecover()两个函数，以及一个curD3DParameters成员）以提供全屏/窗口切换。

>#####IrisSprite#####
>>`修改：`

>>1. 用Shader实现了**Flash()**函数，效果更佳。
2. 删除了**SetDevice()**这个无用函数。
3. 实现了**BlendType**。
4. **现在释放IrisSprite对象不会释放其内部的IrisBitmap了。**
5. **对部分Set函数提供了新的用于控制是否释放Set之前已经保存的对象的参数。**

>#####IrisBitmap#####
>>`新增：`

>>1. 增加了0.5f的像素偏移以解决像素对齐问题。
2. 增加了**IrisBitmap(char*, int, int)**构造函数，方便直接用内存数据构造IrisBitmap对象。
增加了全屏切换时的资源释放/恢复接口。

>>`修改：`

>>1. 修正了Draw函数和MakeTexture函数关于limitRect的使用可能存在的问题。
2. 修正了IrisDrawText函数的设置的字体大小无效的问题
3. 把MakeTexture和IrisBitmapBitBlt的像素拷贝算法改了回去，修正在有限制矩形区域的情况下出现的像素拷贝问题。
4. 统一进行IrisBitmap对象的记录和释放。

>#####IrisViewport#####
>>`新增：`

>>1. 增加了**BeginBatchSpriteProcess()**和**IrisViewportEndBatchSpriteProcess()**，以及对应的**BEGIN_SPRITE_BATCH_PROCESS()**和**END_SPRITE_BATCH_PROCESS()**宏用于加快对一个Viewport添加精灵时的处理速度。

>#####IrisShader和SpriteShader.hlsl#####
>>`新增：`

>>1. 新增了Blend的实现。

>>`修改：`

>>1. 修正了ox,oy的错误设置问题。


>#####ModuleIrisGraphics#####
>>`新增：`

>>1. 实现了Transition()函数的全部功能。（**感谢Ancurio的帮助**，没有他的热情帮助Transition函数的Vague参数所产生的效果将难以实现）
2. 增加了0.5f的像素偏移以解决像素对齐问题。

>>`修改：`

>>1. 修改了Update()以用于解决全屏模式下强行切回桌面设备丢失的问题，同时加入了对音频的Update操作。

>#####ModueleIrisAudio#####
>>`新增`

>>1. **新增了Update()函数，用于解决音效播放失效的问题。**

</br>

>####Iris 2D Biscuit-Onion(API)####
>> **同步更新到Iris 2D Biscuit-Turkey(SC)版本。**

</br>

>####Iris 2D Tools####
>> **从v2.06.13.1开始，Iris 2D 新增了Tools模块，用于提供辅助使用Iris 2D的一系列便利工具。**

>>`新增：`

>> 1. **Iris 2D Graphics Packer and Unpacker**：用于对图片数据的封包（可自定义加密方法）。
2. **Iris2D General Source Packer and Unpacker**：用于对用户自定义数据的封包，如XML文件等（可自定义加密方法）。

--------

###版本号 v1.11.15.1###
>**更新日期：2014.11.15**

</br>

>####Iris 2D Biscuit-Turkey(SC)####
>#####全局：#####
>>`新增：`

>>1. **BEGIN_IRIS_SAFE_WHILE()/END_IRIS_SAFE_WHILE()** 和 **BEGIN_IRIS_SAFE_WHILE_WITH_CONDITION()/END_IRIS_SAFE_WHILE_WITH_CONDITION()** 宏对，建议使用此宏以保证Iris 2D程序的正常退出。

>####ModuleIrisGraphics####
>>`新增：`

>>1. **freeze**和**transition**函数实现。

>####IrisShader、SpriteShader.hlsl、TransitionShader.hlsl：####
>>`修改：`

>>1. 删除IrisShader的spriteBrightnessHandle，改用材质与光照直接在backbuffer上实现brightness。
2. SpriteShader.hlsl 删除Brightness变量。

>>`新增：`

>>1. 增加了TransitionShader.hlsl用于实现渐变图渐变。

>####IrisBitmap####
>>`修改：`

>>1. 修改了像素复制的算法，直接改用memcpy，加快复制速度。
2. 移除了SetOpacity方法，在此版本中此函数已经没有作用。

>####IrisSprite####
>>`修改：`

>>1. 修改了SetOpacity方法，不再对Bitmap进行Opacity的修改。

-------

###版本号 v1.11.05.1###
>**更新日期：2014.11.15**

</br>

>**Iris 2D Biscuit 发布**
>>该版本为测试版本，所以有些功能没有完善，一些函数也没有实现，这一点请注意。

>**Biscuit版本特性**

>>`全局：`

>>1. 采用可编程管线代替 Iris 2D Amethyst 的固定管线，渲染效率更高，程序运行时占用更低。
2. 修改并优化了 Iris 2D Amethyst 版本中存在效率问题的几个函数。
3. 修改了 ModuleIrisGraphics::Update 的实现，可能存在掉帧问题也被修复。