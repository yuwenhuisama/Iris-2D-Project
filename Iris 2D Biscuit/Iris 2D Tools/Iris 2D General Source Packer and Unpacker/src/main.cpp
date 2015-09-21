#include "GeneralEncriptyMaker.h"
#include "GeneralEncriptyUnMaker.h"
#include <sstream>

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

	string strIns(argv[1]);

	if (strIns == "-pack"){
		if (argc < 6) {
			return 0;
			cout << "Error Arguments !" << endl;
		}
		GeneralEncriptyMaker igpPacker;
		string strPackageName(argv[2]);
		string strFolderPath(argv[3]);
		string strKey1(argv[4]);
		string strKey2(argv[5]);
		igpPacker.MakePackage(strPackageName, strFolderPath, StringToNum<DWORD>(strKey1), StringToNum<DWORD>(strKey2), EncodeFunction);
	}
	else if (strIns == "-unpack"){
		GeneralEncriptyUnmaker iguUnpacker;
		string strPackageName(argv[2]);
		iguUnpacker.UnmakePackage(strPackageName, DecodeFunction);
	}
	cout << "All Operating Completed !" << endl;

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