# Iris-2D-Project

## Introduce

Iris 2D is an open source 2D game engine, aimed at fast and lightly game development.

Iris 2D provides a much tidy function collection to support the most nessesary requirement in most cases, and also, provides extension-friendly APIs for implementing much more custom functions by developers themselves.

The major purpose of Iris 2D is to simplify operations of 2D game development, where developers do not need to think about things that have nothing to do with game itself and just write their logic code conveniently and intuitively.

Mostly, Iris does not provide a certain framework for game development, oppositely, developers will touch the basic element of the game such as game loop. However, this feature does not conflict with the major purpose of Iris 2D, and you will find everything will goes simplely if you actually have a experience with Iris 2D.

Usually, there are 3 developing ways of Iris 2D to choose :

- Develop with native Iris 2D APIs by C++;
- Develop with exported Iris 2D APIs by C/C++;
- Develop with Iris programming language.

**For the first way:**

You will work with the native C++ code of Iris 2D, and compile the whole Iris 2D code into developers' games' executable file finally. In this way, developer can easily debug into inside of Iris 2D and do what ever you want to do such customize core code. Oppositely, this way requires that the C++ compiler of developers must support C++ 11 as current Iris 2D is written by C++ 11. And also, this way can make size of your final executable file get larger.

**For the second way:**

Iris 2D's code will be compiled into an independent dynamic link library (.dll) with a exported APIs library. In this way, code of Iris 2D has been seperated from code of developer's game, and the final executable files's size will be much smaller than one in the first way. Oppositely, this way also means that developers cannot see what happend inside Iris 2D and can only use exported APIs of Iris 2D to develop game: actually most of developers do not need to know inside things.

Further more, this way allows develepers to use C/C++ to develop game instead of C++-only. Iris 2D can export 2 styles of APIs for C and C++ respectively:

>- In C++ style, APIs will be exported based on virtual function table such as what COM (Component Object Model) does (but not so complex), so develepers can use these APIs using OOP patern if they like.
>- In C Style, APIs will be exported with HANDLE style which is a bit like Win32 API does, so if develepers just want to write C code instead of C++, this way can be the best choice.

**For the last way:**

We also provide a way for developers to develope game just using script without compiling. 

First, this script laguange is Iris programming language which is a object-oriented dynamice language. For more infomation about this language, please see : http://doc.irislang.org/.

Then, Iris 2D exports its APIs to Iris programming language, and developers can just write scripts of Iris programming language and complete their games.

This way is provided for those develepers who wanna very quick and simplified game development.

## About Document

English Document: http://iris2d.irisine.com/en-us/html/index.html
Chinese Document: http://iris2d.irisine.com/zh-cn/html/index.html

## How to Start an Iris 2D Application with native C++ code

- clone Iris 2D from github:  
  ```git clone https://github.com/yuwenhuisama/Iris-2D-Project.git```
- Open **Iris 2D Cherry.sln** with Visual Studio ( Visual Studio 2017 is recommended, see: https://www.visualstudio.com ) 
  Current Iris 2D can only be compiled through MSVC compiler, so if you want to use other compiler you should modify some code.
- Select **main.cpp** from *Solution Resource Explorer* and clear the content of it.
- Write code :
```c++
#include "Iris2D.h"
using namespace Iris2D;
bool GameCallBack() {
    auto pGraphics = IrisGraphics::Instance();
    auto pApp = IrisApplication::Instance();
    while (!pApp->IsQuited()) {
      pGraphics->Update();
    }
    return true;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
    IrisApplication::IrisAppStartInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };
    auto pApp = IrisApplication::Instance(); 
    if (!pApp->Initialize(&iasiStartInfo)) {
      pApp->Release();
      return -1;
    }
    if (!pApp->Run()) {
      pApp->Release();
      return -1;
    }
    pApp->Release();
    return 0;
}
```
- Compile and Run.

This is the basic structure of Iris 2D Application. Usually, Developers' game logic code should be put in the GameCallBack() function.

For further information about development, you could see examples of Iris 2D.

## How to Start an Iris 2D Application with exported APIs

**\<Under construction\>**

## How to Start an Iris 2D Application with Iris Programming Language

**\<Under construction\>**

## About Old Version

As you can see, current Version of Iris 2D is called Cherry . Actually, Iris 2D has 3 previous versions but not recommended currently :

>- Iris 2D Amethyst (Iris 2D Amethyst - Steck is the Native code version while Iris 2D Amethyst - Potato is the DLL version);
>- Iris 2D Biscuit (Iris 2D Amethyst - Turkey is the Native code version while Iris 2D Biscuit - Potato is the DLL version, Iris 2D Biscuit - Watermelon is abandoned version);
>- Iris 2D Cerise (Precursor of Iris 2D Cherry, abandoned);

## Thanks for

**\<Under construction\>**
## Contact and Copyright

If you have any suggest or report about Iris 2D, please contact a1026121287@hotmail.com;

Iris 2D is an open source project under BSD2 lisence, for more infomation please see: https://opensource.org/licenses/BSD-2-Clause .
