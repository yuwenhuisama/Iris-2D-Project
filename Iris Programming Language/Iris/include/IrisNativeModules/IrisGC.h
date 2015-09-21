#ifndef _H_IRISGC_
#define _H_IRISGC_

#include "IrisClass.h"
#include "IrisObject.h"
#include "IrisTree.h"

class IrisGC
{

private:
	static const int c_nThreshold = 512;

private:
	static int sm_nCurrentHeapSize;
	static int sm_nNextThresholdSize;

	static int sm_nCurrentContextEnvrionmentHeapSize;
	static int sm_nNextContextEnvrionmentThresholdSize;

	static bool sm_bFlag;

private:

	static void _ErgodicTreeAndMark(IrisTree<IrisModule*>::Node<IrisModule*>* pCurNode);

	static void _ClearMark();
	static void _Mark();
	static void _Sweep();

public:
	static void ResetNextThreshold();
	static void Start();
	static void ForceStart();
	static void SetGCFlag(bool bFlag);
	static void AddSize(int nSize);

	static void AddContextEnvironmentSize();
	static void ContextEnvironmentGC();

	IrisGC();
	~IrisGC();
};

#endif