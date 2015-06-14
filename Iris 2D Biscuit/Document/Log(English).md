# Iris 2D Biscuit Update Log
---

###Version v2.06.13.1
>**Update Date : 2015.6.13**

</br>

>####Iris 2D Biscuit-Turkey(SC)####
>#####Globol#####
>>`Append:`
 **(Essential）** 1. Append the new namespace of **Iris2D**, optimize and adjust the sturcture of including of header files, and a lot of functions are globolly appended a new parameter of **IrisResult** which is used to check the result of calling and relevant exception-dealing macro of this paramter.
2. Correct the problem of capital and low case letters of variable names.(to unify all the function name to start with capital letter)
3. Delete some useless member variables, and modify the access authority of ones to be convenient for extending and inheritting.

>#####IrisEncripedResourceManager#####
>>`Append:`
1. Append the class of **IrisEncripedResourceManager** to manage the archive data(using the tool in *Iris Tools*).

>#####IrisApp#####
>>`Append:`
1. Append the function of **ToggleWindowMode()** to swicth between full-screen mode and windowed mode affiliated with functions of *OnDeviceLost()* and *OndDeviceRecover()* and a member of *curD3DParameters*.

>#####IrisSprite#####
>>`Modify:`
1. Use *Shader* to achieve the function of **Flash()** getting a better effect.
2. Delete the useless function of **SetDevice()**
3. The achievement of **BlendType**
4. ***IrisBitmp* object inside will not be disposed when disposing *IrisSprite* object.**
5. **Some of *Set* functions are appended a new parameter to control whether the object saved before will be released.**

>#####IrisBitmap#####
>>`Append:`
1. Increase the offset of pixel of 0.5f to solve the problem of pixel-alignment.
2. Append the constructure of **IrisBitmap(char*, int, int)** to be convenient for construct *IrisBitmap* object with memory data.
>>`Modify:`
1. Currect the probable problem using *limiteRect* in functions of *Draw* and *MakeTexture*.
2. Currect the problem of invalidation of the font size set in function of *IrisDrawText* 
3. Change the pixel copying algorithm in functions of *MakeTexture* and *IrisBitmapBitBlt* back as before to correct the pixel copying problem when copying pixel under the circumstance of using limited rect field.
4. Objects of *IrisBitmap* will be recorded and released uniformity.

>#####IrisViewport#####
>>`Append:`
1. Append the functions of **BeginBatchSpriteProcess()** and **IrisViewportEndBatchSpriteProcess()** and corresponding micros of **BEGIN_SPRITE_BATCH_PROCESS()** and **END_SPRITE_BATCH_PROCESS()** to accelarate the processing speed when appending new sprites into a viewport.

>#####IrisShader和SpriteShader.hlsl#####
>>`Append:`
1. The achievement of *Blend*.
`Modify:`
1. Correct the problem of wrong setting of *ox, oy*.

>#####ModuleIrisGraphics#####
>>`Append:`
1.The achiement of all the function of function of *Transition()* (**Thanks for the help of Ancurio**, without his enthusiastic help the effect of the parameter of *Vague* in function of *Transition* cannot be achieved.)
2. Increase the offset of pixel of 0.5f to solve the problem of pixel-alignment.
`Modify:`
1. Modify function of *Update()* to solve the problem of device losing when switch to desktop in full-screen mode and append the operating of *Update* towarding audio.

>#####ModueleIrisAudio#####
>>`Append:`
1. **Append the function of *Update()* to solve the problem of invalidation playing audio.**

</br>

>####Iris 2D Biscuit-Onion(API)####
>> **Sync the version the same as Edition Iris 2D Biscuit-Turkey(SC)**

</br>

>####Iris 2D Tools####
>>**Module of *Tools* are appended from v2.06.13.1 to provide a series of auxiliary tools to make it convinient for using Iris 2D.**
>`Append:`
> 1. **Iris 2D Graphics Packer and Unpacker**：For Archiving the graphics data.(can also define custom encrypting method) 
2. **Iris2D General Source Packer and Unpacker**：：For Archiving the custom data such as *XML File*.(can also define custom encrypting method)

--------

###Version v1.11.15.1###
>**Update Date：2014.11.15**

</br>

>####Iris 2D Biscuit-Turkey(SC):####
>#####Global：#####
>>`新增：`
1. Append macro pairs of **BEGIN_IRIS_SAFE_WHILE()/END_IRIS_SAFE_WHILE()** and **BEGIN_IRIS_SAFE_WHILE_WITH_CONDITION()/END_IRIS_SAFE_WHILE_WITH_CONDITION()**，which is suggested to be used to ensure the normal exiting of Iris 2D program.

>####ModuleIrisGraphics####
>>`Append：`
1. the realize of **freeze()** and **transition()**.

>####IrisShader、SpriteShader.hlsl、TransitionShader.hlsl：####
>>`Modify:`
1. Delete spriteBrightnessHandle of IrisShader and straightly use light and material to realize brightness on backbuffer.
2. Delete variable of Brightness in *SpriteShader.hlsl*.
`Append:`
1. Append the *TransitionShader.hlsl* to realize transition with transition image.

>####IrisBitmap####
>>`Modify:`
1. Modify the algorithm of pixel-copying，and use memcpy() directly to accelarate the speed of copying.
2. Delete the function of SetOpacity(), for it will have no usage in this edition.

>####IrisSprite####
>>`修改：`
1. Modify the function of SetOpacity() not changing Bitmap's Opacity anymore.

-------

###Version v1.10.05.1###
>**Update Date：2014.11.05**

</br>

>**Iris 2D Biscuit Release**
>>**Notice:** This vision belongs to alpha version, so there are some functions are still uncompleted.

>**Edition Biscuit Features**
>>`Global:`
1. (Important)Use programmable render pipeline(hlsl) to replace fixed render pipeline in Iris 2D Amethyst, leading to higher efficiency of render and lower resource usage when running.
2. Modify and optimizes some functions which can lead to problems of efficiency.
3. Modify the realize of ModuleIrisGraphics::Update to repair possible problem of frame missing.