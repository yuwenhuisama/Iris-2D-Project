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
* \mainpage Iris 2D Cherry API �ĵ�
* \section intro_sec ���
*
* Iris 2D ��һ�Դ��2D��Ϸ���棬ּ���ڽ��п�����������Ϸ������
* 
* Iris 2D �ṩ��һ���ǳ����Ĺ��ܼ��ϣ��ܹ�֧�ִ������������Ҫ�Ŀ������󣬲��� Iris 2D Ҳ�ṩ�˶���չ��д��Ϊ�ѺõĽӿڣ��ÿ��������ܹ��Լ�ʵ�ָ���Ķ����Թ��ܡ�
*
* Iris 2D ����Ҫ��Ŀ���Ǽ� 2D ��Ϸ�����Ĳ����������߲���Ҫ��������Ϸ�����޹ص����飬ֻ��Ҫ�����ֱ�۵ر�д���ǵ��߼����롣
*
* ���������£� Iris �����ṩһ��ȷ�е���Ϸ������ܣ��෴�������߽��ᴥ������Ϸ�Ļ���Ԫ�ر�����Ϸѭ����Ȼ����������Ժ� Iris 2D ����ҪĿ�겢����ͻ�������ʵ�ʵ�����һ�� Iris 2D �Ļ�����ᷢ��һ�ж����еúܺá�
*
* ͨ������£�Iris 2D �ṩ��3�ֿ�����ʽ��ѡ��
*
* \li ʹ�� C++ �Լ� Iris 2D ��ԭ��������п���;
* \li ʹ�� C/C++ �Լ� Iris 2D ������ API ���п���;
* \li ʹ�� Iris programming language ������
* 
* \par ���ڵ�һ�ַ�ʽ��
* ������ Iris 2D ��ԭ�� C++ ����һ�������������ս����� Iris 2D �Ĵ�����뵽��������Ϸ�Ŀ�ִ���ļ�֮�С�ʹ�����ַ����������߿������׵ص��Խ� Iris 2D ���ڲ������ܹ����κ����������飨�����Զ��� Iris 2D �ĺ��Ĺ��ܣ�����Եģ����ַ�ʽ��Ҫ�����ߵ� C++  ������֧�� C++ 11 ����Ϊ��ǰ�� Iris 2D ��ʹ�� C++ 11 �����ġ�ͬʱ�����ַ�ʽ�����������յĿ�ִ���ļ������ô�
* \par ���ڵڶ��ַ�ʽ��
* Iris 2D �Ĵ��뽫�ᱻ�����һ����̬���ӿ⣨.dll��֮�в��Ҹ���һ�����������⡣ʹ�����ַ�ʽ��Iris 2D �Ĵ����ӿ����ߵ���Ϸ�����з���������������յĿ�ִ���ļ�����������ʹ�÷�ʽ1�õ��Ŀ�ִ���ļ�С�öࡣ��Եģ��������ַ�ʽҲ����ζ�ſ������޷����� Iris 2D �ڲ�������ʲô����ֻ�ܹ�ʹ�� Iris 2D ������ API ������Ϸ���� �� ��ʵ�ϴ����������Ҳ������Ҫ֪����Щ�ڲ�������
* \par
* ���⣬���ַ�ʽ�������߲��� C/C++ ��������Ϸ��������ֻ��ʹ�� C++ ��Iris 2D ���Էֱ�Ϊ C �� C++ ����2�ַ��� API��
* \par
* \li ���� C++ ���API �����Ի����麯����ķ�ʽ������������ͬ COM (Component Object Model) ������������������û������ô���ӣ����������������ϲ�� OOP ��ģʽ����ô�Ϳ���ʹ������ API ��
* \li ���� C ���API ����ʹ�� HANDLE �ķ�񱻵����������ͬ Win32 API �������������������������ֻ��Ҫ��д C ��������� C++ ���룬��ô�����ʽ��������õ�ѡ�
*
* \par ���ڵ����ַ�ʽ��
* ����ҲΪ���������ṩ��һ�ֽ���ʹ�ýű����������ͽ�����Ϸ�����ķ�ʽ��
* ���ȣ����Žű����Ծ��� Iris programming language ������һ���������Ķ�̬���ԡ����ڸ����Եĸ�����Ϣ������ʣ�http://doc.irislang.org/ ��
* \par
* ��Σ�Iris 2D ������ API �������� Iris programming language�����ǿ����߿���ֻ��д Iris programming language �Ľű����ܹ�������ǵ���Ϸ��
* \par
* ���ַ�ʽ���ṩ����Щ��Ҫ�ǳ����ٺͼ򻯵���Ϸ�����Ŀ������ǡ�
* \section install_sec_1 ���ʹ��ԭ�� C++ ���뿪ʼһ�� Iris 2D Ӧ��
* 
* \li ��github��clone���� \n <tt> git clone https://github.com/yuwenhuisama/Iris-2D-Project.git </tt>.
* \li ʹ�� Visual Studio ��<em> Iris 2D Cherry.sln </em>���Ƽ�ʹ�� Visual Studio 2017��������Ϣ����ʣ�https://www.visualstudio.com )
* \n <b> ��ǰ�� Iris 2D ֻ�ܹ��� MSVC �ϱ���ͨ���������������Ҫʹ�������������Ļ�������Ҫ�޸�һЩ���롣</b>
* \li ��<tt> ������������� </tt> ��ѡ��<em> main.cpp </em>�������������ݡ�
* \li ��д���� :
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
* \li ���벢����.
*
* ���Ͼ��� Iris 2D Ӧ�õĻ����ṹ��ͨ�����ԣ������ߵ���Ϸ�߼�����Ӧ�ñ����� GameCallBack() �������档
* ���ڸ���Ĺ��ڿ�������Ϣ���������Ķ� Iris 2D �ķ�����
* 
* \section install_sec_2 ���ʹ�õ����� API ��ʼһ�� Iris 2D Ӧ��
* \par
* \<\b Under \b construction>
* 
* \section install_sec_3 ���ʹ�� Iris programming language ��ʼһ�� Iris 2D Ӧ�á�
* \par
* \<\b Under \b construction>
*
* \section name_stg ���ھɰ汾
* �����������ģ���ǰ Iris 2D �İ汾������Ϊ <b> Cherry </b>����ʵ�ϣ�Iris 2D ӵ��3���ɰ汾�������Ѿ����ٱ��Ƽ���
*
* \li Iris 2D Amethyst (Iris 2D Amethyst - Steck ��ԭ������汾 �� Iris 2D Amethyst - Potato �� DLL �汾);
* \li Iris 2D Biscuit (Iris 2D Amethyst - Turkey ��ԭ������汾 �� Iris 2D Biscuit - Potato �� DLL �汾, Iris 2D Biscuit - Watermelon �Ǳ����õİ汾);
* \li Iris 2D Cerise (Iris 2D Cherry ��ǰ��, ������);
* 
* \section thanks ��л
* \par
* \<\b Under \b construction>
*
* \section cont_cprt ��ϵ��ʽ�Լ���Ȩ
* \par
* ������� Iris 2D ���κν�����߱��棬����ϵ a1026121287@hotmail.com��
* \par
* Iris 2D ��һ����Դ��Ŀ������ BSD2 ���֤������� https://opensource.org/licenses/BSD-2-Clause �Ի�ø�����Ϣ��
*/