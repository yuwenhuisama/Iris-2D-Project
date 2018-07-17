/**
* \~english
* \mainpage Iris 2D Cherry API Document
* \section intro_sec Introduce
*
* Iris 2D is an open source 2D game engine, aimed at fast and lightly game development.
* 
* Iris 2D provides a much tidy function collection to support the most nessesary requirement in most cases, and also, provides extension-friendly APIs for implementing much more custom functions by developers themselves.
*
* The major purpose of Iris 2D is to simplify operations of 2D game development, where developers do not need to think about things that have nothing to do with game itself and just write their logic code conveniently and intuitively.
*
* Mostly, Iris does not provide a certain framework for game development, oppositely, developers will touch the basic element of the game such as game loop. However, this feature does not conflict with the major purpose of Iris 2D, and you will find everything will goes simplely if you actually have a experience with Iris 2D.
*
* Usually, there are 3 developing ways of Iris 2D to choose :
*
* \li Develop with native Iris 2D APIs by C++;
* \li Develop with exported Iris 2D APIs by C/C++;
* \li Develop with Iris programming language.
* 
* \par For the first way:
* You will work with the native C++ code of Iris 2D, and compile the whole Iris 2D code into developers' games' executable file finally. In this way, developer can easily debug into inside of Iris 2D and do what ever you want to do such customize core code. Oppositely, this way requires that the C++ compiler of developers must support C++ 11 as current Iris 2D is written by C++ 11. And also, this way can make size of your final executable file get larger.
* \par For the second way:
* Iris 2D's code will be compiled into an independent dynamic link library (.dll) with a exported APIs library. In this way, code of Iris 2D has been seperated from code of developer's game, and the final executable files's size will be much smaller than one in the first way. Oppositely, this way also means that developers cannot see what happend inside Iris 2D and can only use exported APIs of Iris 2D to develop game: actually most of developers do not need to know inside things.
* \par
* Further more, this way allows develepers to use C/C++ to develop game instead of C++-only. Iris 2D can export 2 styles of APIs for C and C++ respectively:
* \par
* \li In C++ style, APIs will be exported based on virtual function table such as what COM (Component Object Model) does (but not so complex), so develepers can use these APIs using OOP patern if they like.
* \li In C Style, APIs will be exported with HANDLE style which is a bit like Win32 API does, so if develepers just want to write C code instead of C++, this way can be the best choice.
*
* \par For the last way:
* We also provide a way for developers to develope game just using script without compiling.
* First, this script laguange is Iris programming language which is a object-oriented dynamice language. For more infomation about this language, please see : http://doc.irislang.org/.
* \par
* Then, Iris 2D exports its APIs to Iris programming language, and developers can just write scripts of Iris programming language and complete their games.
* \par
* This way is provided for those develepers who wanna very quick and simplified game development.
* \section install_sec_1 How to Start an Iris 2D Application with native C++ code
* 
* \li clone Iris 2D from github: \n <tt> git clone https://github.com/yuwenhuisama/Iris-2D-Project.git </tt>.
* \li Open <em> Iris 2D Cherry.sln </em> with Visual Studio ( Visual Studio 2017 is recommended, see: https://www.visualstudio.com )
* \n <b> Current Iris 2D can only be compiled through MSVC compiler, so if you want to use other compiler you should modify some code. </b>
* \li Select <em> main.cpp </em> from <tt> Solution Resource Explorer </tt> and clear the content of it.
* \li Write code :
* \code {.cpp}
* #include "Iris2D.h"
* using namespace Iris2D;
* 
* bool GameCallBack() {
*	  auto pGraphics = IrisGraphics::Instance();
*	  auto pApp = IrisApplication::Instance();
*	  while (!pApp->IsQuited()) {
*		  pGraphics->Update();
*	  }
*	  return true;
* }
*
* int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
*	  IrisApplication::IrisAppStartInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };
*	  auto pApp = IrisApplication::Instance(); 
*
*	  if (!pApp->Initialize(&iasiStartInfo)) {
*		  pApp->Release();
*		  return -1;
*  	  }
*
*	  if (!pApp->Run()) {
*		  pApp->Release();
*		  return -1;
*	  }
*
*	  pApp->Release();
*	  return 0;
* }
* \endcode
* \li Compile and Run.
*
* This is the basic structure of Iris 2D Application. Usually, Developers' game logic code should be put in the GameCallBack() function.
*
* For further information about development, you could see examples of Iris 2D.
* 
* \section install_sec_2 How to Start an Iris 2D Application with exported APIs
* \par
* \<\b Under \b construction>
* 
* \section install_sec_3 How to Start an Iris 2D Application with Iris Programming Language
* \par
* \<\b Under \b construction>
*
* \section name_stg About Old Version
* As you can see, current Version of Iris 2D is called <b> Cherry </b>. Actually, Iris 2D has 3 previous versions but not recommended currently :
*
* \li Iris 2D Amethyst (Iris 2D Amethyst - Steck is the Native code version while Iris 2D Amethyst - Potato is the DLL version);
* \li Iris 2D Biscuit (Iris 2D Amethyst - Turkey is the Native code version while Iris 2D Biscuit - Potato is the DLL version, Iris 2D Biscuit - Watermelon is abandoned version);
* \li Iris 2D Cerise (Precursor of Iris 2D Cherry, abandoned);
* 
* \section thanks Thanks for
* \par
* \<\b Under \b construction>
*
* \section cont_cprt Contact and Copyright
* \par
* If you have any suggest or report about Iris 2D, please contact a1026121287@hotmail.com;
* \par
* Iris 2D is an open source project under BSD2 lisence, for more infomation please see: https://opensource.org/licenses/BSD-2-Clause .
*/
/**
* \~chinese
* \mainpage Iris 2D Cherry API 文档
* \section intro_sec 简介
*
* Iris 2D 是一款开源的2D游戏引擎，旨在于进行快速轻量的游戏开发。
* 
* Iris 2D 提供了一个非常简洁的功能集合，能够支持大多数情况下最必要的开发需求，并且 Iris 2D 也提供了对扩展编写较为友好的接口，让开发或者能够自己实现更多的定制性功能。
*
* Iris 2D 最主要的目的是简化 2D 游戏开发的操作，开发者不需要考虑与游戏本身无关的事情，只需要方便而直观地编写他们的逻辑代码。
*
* 大多数情况下， Iris 不会提供一个确切的游戏开发框架，相反，开发者将会触碰到游戏的基本元素比如游戏循环。然而，这个特性和 Iris 2D 的主要目标并不冲突，如果您实际地体验一下 Iris 2D 的话，你会发现一切都运行得很好。
*
* 通常情况下，Iris 2D 提供了3种开发方式供选择：
*
* \li 使用 C++ 以及 Iris 2D 的原生代码进行开发;
* \li 使用 C/C++ 以及 Iris 2D 导出的 API 进行开发;
* \li 使用 Iris programming language 开发。
* 
* \par 对于第一种方式：
* 您会与 Iris 2D 的原生 C++ 代码一起工作，并且最终将整个 Iris 2D 的代码编译到开发者游戏的可执行文件之中。使用这种方法，开发者可以轻易地调试进 Iris 2D 的内部并且能够做任何想做的事情（比如自定义 Iris 2D 的核心功能）。相对的，这种方式需要开发者的 C++  编译器支持 C++ 11 ，因为当前的 Iris 2D 是使用 C++ 11 开发的。同时，这种方式将会让您最终的可执行文件体积变得大。
* \par 对于第二种方式：
* Iris 2D 的代码将会被编译进一个动态链接库（.dll）之中并且附带一个导出函数库。使用这种方式，Iris 2D 的代码会从开发者的游戏代码中分离出来，并且最终的可执行文件的体积将会比使用方式1得到的可执行文件小得多。相对的，采用这种方式也就意味着开发者无法看到 Iris 2D 内部发生了什么并且只能够使用 Iris 2D 导出的 API 进行游戏开发 ： 事实上大多数开发者也并不需要知道这些内部工作。
* \par
* 此外，这种方式允许开发者采用 C/C++ 来开发游戏，而不是只能使用 C++ 。Iris 2D 可以分别为 C 和 C++ 导出2种风格的 API：
* \par
* \li 对于 C++ 风格，API 将会以基于虚函数表的方式被导出，就如同 COM (Component Object Model) 所做的那样（不过并没有它那么复杂），所以如果开发者喜欢 OOP 的模式，那么就可以使用这套 API 。
* \li 对于 C 风格，API 将会使用 HANDLE 的风格被导出，这就如同 Win32 API 所做的那样，所以如果开发者只想要编写 C 代码而不是 C++ 代码，那么这个方式将会是最好的选项。
*
* \par 对于第三种方式：
* 我们也为开发或者提供了一种仅仅使用脚本而无需编译就进行游戏开发的方式。
* 首先，这门脚本语言就是 Iris programming language ，这是一门面向对象的动态语言。对于该语言的更多信息，请访问：http://doc.irislang.org/ 。
* \par
* 其次，Iris 2D 将它的 API 导出给了 Iris programming language，于是开发者可以只编写 Iris programming language 的脚本就能够完成他们的游戏。
* \par
* 这种方式被提供给那些需要非常快速和简化的游戏开发的开发者们。
* \section install_sec_1 如何使用原生 C++ 代码开始一个 Iris 2D 应用
* 
* \li 从github上clone工程 \n <tt> git clone https://github.com/yuwenhuisama/Iris-2D-Project.git </tt>.
* \li 使用 Visual Studio 打开<em> Iris 2D Cherry.sln </em>（推荐使用 Visual Studio 2017，更多信息请访问：https://www.visualstudio.com )
* \n <b> 当前的 Iris 2D 只能够在 MSVC 上编译通过，所以如果您想要使用其他编译器的话，您需要修改一些代码。</b>
* \li 在<tt> 解决方案管理器 </tt> 中选择<em> main.cpp </em>并清空里面的内容。
* \li 编写代码 :
* \code {.cpp}
* #include "Iris2D.h"
* using namespace Iris2D;
* 
* bool GameCallBack() {
*	  auto pGraphics = IrisGraphics::Instance();
*	  auto pApp = IrisApplication::Instance();
*	  while (!pApp->IsQuited()) {
*		  pGraphics->Update();
*	  }
*	  return true;
* }
*
* int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
*	  IrisApplication::IrisAppStartInfo iasiStartInfo = { hInstance, showCmd, 60, 60, 1600, 900, GameCallBack, L"My Iris App" };
*	  auto pApp = IrisApplication::Instance(); 
*
*	  if (!pApp->Initialize(&iasiStartInfo)) {
*		  pApp->Release();
*		  return -1;
*  	  }
*
*	  if (!pApp->Run()) {
*		  pApp->Release();
*		  return -1;
*	  }
*
*	  pApp->Release();
*	  return 0;
* }
* \endcode
* \li 编译并运行.
*
* 以上就是 Iris 2D 应用的基本结构。通常而言，开发者的游戏逻辑代码应该被放在 GameCallBack() 方法里面。
* 对于更多的关于开发的信息，您可以阅读 Iris 2D 的范例。
* 
* \section install_sec_2 如何使用导出的 API 开始一个 Iris 2D 应用
* \par
* \<\b Under \b construction>
* 
* \section install_sec_3 如何使用 Iris programming language 开始一个 Iris 2D 应用。
* \par
* \<\b Under \b construction>
*
* \section name_stg 关于旧版本
* 正如您所见的，当前 Iris 2D 的版本被命名为 <b> Cherry </b>。事实上，Iris 2D 拥有3个旧版本，但是已经不再被推荐：
*
* \li Iris 2D Amethyst (Iris 2D Amethyst - Steck 是原生代码版本 而 Iris 2D Amethyst - Potato 是 DLL 版本);
* \li Iris 2D Biscuit (Iris 2D Amethyst - Turkey 是原生代码版本 而 Iris 2D Biscuit - Potato 是 DLL 版本, Iris 2D Biscuit - Watermelon 是被弃用的版本);
* \li Iris 2D Cerise (Iris 2D Cherry 的前身, 已弃用);
* 
* \section thanks 感谢
* \par
* \<\b Under \b construction>
*
* \section cont_cprt 联系方式以及版权
* \par
* 如果您对 Iris 2D 有任何建议或者报告，请联系 a1026121287@hotmail.com；
* \par
* Iris 2D 是一个开源项目，基于 BSD2 许可证，请访问 https://opensource.org/licenses/BSD-2-Clause 以获得更多信息。
*/