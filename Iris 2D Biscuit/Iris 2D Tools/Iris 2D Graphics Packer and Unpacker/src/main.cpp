#include "IrisGraphicsPacker.h"
#include "IrisGraphicsUnpacker.h"
#include "IrisGraphicsSourceExtract.h"
#include <sstream>

//#define CROL(value, bits) ((value << bits) | (value >> (0x20 - bits)))
//#define CROR(value, bits) ((value >> bits) | (value << (0x20 - bits)))

#define CROL(value, bits, n) ((value >> (bits - n)) | (value >> n))
#define CROR(value, bits, n) ((value << (bits - n)) | (value >> n))

void EncodeFunction(const DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2);
void DecodeFunction(const DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2);

const DWORD c_dwKey1 = 0x20150422;
const DWORD c_dwKey2 = 0x00000003;

template <class Type>
Type StringToNum(const string& str){
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}


int main(int argc, char* argv[]){

	if (argc < 3) {
		cout << "Error Arguments !" << endl;
		return 0;
	}

	ULONG_PTR m_pGdiToken;
	GdiplusStartupInput m_gdiplusStartupInput;
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);
	
	string strIns(argv[1]);

	if (strIns == "-pack"){
		if (argc < 6) {
			return 0;
			cout << "Error Arguments !" << endl;
		}
		IrisGraphicsPacker igpPacker;
		string strPackageName(argv[2]);
		string strFolderPath(argv[3]);
		string strKey1(argv[4]);
		string strKey2(argv[5]);
		igpPacker.MakePackage(strPackageName, strFolderPath, StringToNum<DWORD>(strKey1), StringToNum<DWORD>(strKey2), EncodeFunction);
	}
	else if (strIns == "-unpack"){
		IrisGraphicsUnpacker iguUnpacker;
		string strPackageName(argv[2]);
		iguUnpacker.UnmakePackage(strPackageName, DecodeFunction);
	}
	cout << "All Operating Completed !" << endl;

	//string strPackageName("a.dat");
	//string strGraphPathName("image");

	//igpPacker.MakePackage(strPackageName, strGraphPathName, c_dwKey1, c_dwKey2, EncodeFunction);
	//igpPacker.MakePackage(strPackageName, strGraphPathName);

	//iguUnpacker.UnmakePackage(strPackageName, DecodeFunction);
	//iguUnpacker.UnmakePackage(strPackageName);

	//IrisGraphicsSourceExtract igseExtract;

	//igseExtract.InitPackageData("a.dat", DecodeFunction);
	//char* pImageData = NULL;
	//int nWidth = 0, nHeihght = 0;
	//if (igseExtract.GetBitmapData("image\\1.jpg", &pImageData, &nWidth, &nHeihght)){
	//	Bitmap bpBmp(nWidth, nHeihght, PixelFormat32bppARGB);
	//	BitmapData bmpdtData;
	//	Rect bpRect(0, 0, bpBmp.GetWidth(), bpBmp.GetHeight());
	//	bpBmp.LockBits(&bpRect, ImageLockModeWrite, PixelFormat32bppARGB, &bmpdtData);
	//	memcpy(bmpdtData.Scan0, pImageData, nWidth*nHeihght * 4);
	//	delete[] pImageData;
	//	bpBmp.UnlockBits(&bmpdtData);
	//	CLSID encoderClsid;
	//	IrisGraphicsUnpacker::GetEncoderClsid(L"image/jpeg", &encoderClsid);
	//	// Ð´µ½ÎÄ¼þ
	//	bpBmp.Save(L"1.jpg", &encoderClsid, NULL);
	//}

	GdiplusShutdown(m_pGdiToken);

	return 0;
}

void EncodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey1;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey2;
}

void DecodeFunction(DWORD dwSrcData, DWORD& dwDestData, const DWORD dwKey1, const DWORD dwKey2) {
	dwDestData = dwSrcData ^ dwKey2;
	dwDestData = ~dwDestData;
	dwDestData ^= dwKey1;
}