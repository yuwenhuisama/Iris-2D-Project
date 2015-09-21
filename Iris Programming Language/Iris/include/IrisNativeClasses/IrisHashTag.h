#ifndef _H_IRISHASHTAG_
#define _H_IRISHASHTAG_

#include "IrisInteger.h"
#include "IrisFloat.h"
#include "IrisString.h"
#include "IrisValue.h"
#include <unordered_map>
#include <math.h>  
using namespace std;

class IrisHashTag
{
private:
	struct IrisValueHash {
		size_t operator () (const IrisValue& ivValue) const {
			if (((IrisValue&)ivValue).GetObject()->GetClass()->GetClassName() == "Integer") {
				return size_t(IrisInteger::GetIntData((IrisValue&)ivValue));
			}
			else if (((IrisValue&)ivValue).GetObject()->GetClass()->GetClassName() == "Float") {
				int e = 0;
				double dValue = IrisFloat::GetFloatData((IrisValue&)ivValue);
				double tmp = dValue;
				if (dValue<0)
				{
					tmp = -dValue;
				}
				e = (int)ceil(log(dValue));
				return size_t((INT64_MAX + 1.0) * tmp * exp(-e));
			}
			else if (((IrisValue&)ivValue).GetObject()->GetClass()->GetClassName() == "String") {
				string& str = ::IrisString::GetString((IrisValue&)ivValue);
				size_t h = 0;
				for (size_t i = 0;i<str.length();++i)
				{
					h = (h << 5) - h + str[i];
				}
				return h;
			}
			else {
				return (size_t)((IrisValue&)ivValue).GetObject()->GetObjectID();
			}
		}
	};

	struct IrisValueCmp {
		bool operator()(const IrisValue& ivValue1, const IrisValue& ivValue2) const {
			if(((IrisValue&)ivValue1).GetObject()->GetClass()->GetClassName() == "Integer"
				&& ((IrisValue&)ivValue2).GetObject()->GetClass()->GetClassName() == "Integer") {
				return IrisInteger::GetIntData((IrisValue&)ivValue1) == IrisInteger::GetIntData((IrisValue&)ivValue2);
			}
			else if (((IrisValue&)ivValue1).GetObject()->GetClass()->GetClassName() == "Float"
				&& ((IrisValue&)ivValue2).GetObject()->GetClass()->GetClassName() == "Float") {
				return IrisFloat::GetFloatData((IrisValue&)ivValue1) == IrisFloat::GetFloatData((IrisValue&)ivValue2);
			}
			else if (((IrisValue&)ivValue1).GetObject()->GetClass()->GetClassName() == "String"
				&& ((IrisValue&)ivValue2).GetObject()->GetClass()->GetClassName() == "String") {
				return IrisString::GetString((IrisValue&)ivValue1) == IrisString::GetString((IrisValue&)ivValue2);
			}
			else {
				return ((IrisValue&)ivValue1).GetObject()->GetObjectID() == ((IrisValue&)ivValue2).GetObject()->GetObjectID();
			}
		}
	};

private:
	typedef unordered_map<IrisValue, IrisValue, IrisValueHash, IrisValueCmp> _IrisHash;
	//typedef pair<IrisValue, IrisValue> _IrisHashPair;

private:
	_IrisHash m_mpHash;

public:

	void Initialize(IrisValues* pValues);
	IrisValue At(const IrisValue& ivIndex);
	IrisValue Set(const IrisValue& ivKey, const IrisValue& ivValue);

	IrisHashTag();
	~IrisHashTag();

	friend class IrisHash;
	friend class IrisStatement;
};

#endif