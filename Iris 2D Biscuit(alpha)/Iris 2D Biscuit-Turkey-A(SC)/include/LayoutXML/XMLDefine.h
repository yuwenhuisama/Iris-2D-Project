#ifndef _XMLDEFINE_H_
#define _XMLDEFINE_H_

#include "tinyxml.h"
#include <sstream>
#include <map>
#include <list>
using namespace std;
/* Function Define */
template <class Type>
Type stringToNum(const string& str){
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

/* Macro Define */
#define PCHCMP(pch, value) pch == string(value)

#define GETTERCALL(obj, prnm, v) v = obj->Get##prnm();
#define SETTERCALL(obj, prnm, v) obj->Set##prnm(v);

#define DECLARE_MAPPING(pdtnm) map<string, pdtnm*> _xml2##pdtnm;
#define CALL_MAPPING(pdtnm, id) this->_xml2##pdtnm[id]
#define GET_ATTR_BY_ID(node, id) node->ToElement()->Attribute(id)

#define BEGIN_CREATE_OBJ(cppklass) if(PCHCMP(className, #cppklass)){
#ifndef _MSC_VER
#define CREATE_OBJ(cppklass, args...) cppklass* p = new cppklass(args);\
	CALL_MAPPING(cppklass, id) = p;
#endif
#ifdef _MSC_VER
#define CREATE_OBJ(cppklass, ...) cppklass* p = new cppklass(##__VA_ARGS__);\
	CALL_MAPPING(cppklass, id) = p;
#endif
#define LINK_PARENT(pttp, prnt, prop) CALL_MAPPING(pttp, GET_ATTR_BY_ID(prnt->Parent(), "ID"))->Set##prop(p);
#define END_CREATE_OBJ() }

#define BEGIN_ATTR_JUDGE(cppklass, id) \
if (PCHCMP(className, #cppklass)){ \
	cppklass* p = CALL_MAPPING(cppklass, id);

#define ATTR_JUDGE(cppattr, v) \
if (PCHCMP(attrName, #cppattr)){ \
	SETTERCALL(p, cppattr, v) \
}
#define END_ATTR_JUDGE() }

#define RELEASE_SOURCE(dtnm) \
	do { \
		map<string, dtnm*>::iterator it##dtnm; \
		for (it##dtnm = _xml2##dtnm.begin(); it##dtnm != _xml2##dtnm.end(); ++it##dtnm) \
			delete it##dtnm->second; \
	} while (0);

#define BEGIN_OBJECT_CREATE_DEAL() virtual void ObjectCreateDeal(string className, string id, TiXmlNode* parent) {
#define END_OBJECT_CREATE_DEAL() }
#define CUR_NODE parent
#define PAR_NODE parent->Parent()
#define PAR_VALUE_EQUAL(cppklass) PAR_NODE->ValueTStr() == string(#cppklass)

#define BEGIN_OBJECT_ATTR_DEAL() virtual void ObjectAttributeDeal(string className, string id, string attrName, string value, TiXmlNode* parent) {
#define END_OBJECT_ATTR_DEAL() }

/* Abstract Class Define */
class LayoutToObject{
private:

	TiXmlDocument* document;
	virtual void ObjectCreateDeal(string className, string id, TiXmlNode* parent) = 0;
	virtual void ObjectAttributeDeal(string className, string id, string attrName, string value, TiXmlNode* parent) = 0;

public:

	virtual void LoadXML(string xmlFile){
		this->document = new TiXmlDocument;
		this->document->LoadFile(xmlFile);
		TiXmlElement* rootElement = this->document->RootElement();
		ParseXML(rootElement);
	}
	virtual void ParseXML(TiXmlNode* pParent){
		if (!pParent)
			return;
		string objId(pParent->ToElement()->Attribute("ID"));
		ObjectCreateDeal(pParent->Value(), objId, pParent);
		TiXmlElement* elem = pParent->ToElement();
		TiXmlAttribute* attr = elem->FirstAttribute();
		while (attr){
			//******
			ObjectAttributeDeal(pParent->Value(), objId, attr->Name(), attr->Value(), pParent);
			//******
			attr = attr->Next();
		}
		TiXmlNode* pChild;
		for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
		{
			ParseXML(pChild);
		}
	}
	virtual void ReleaseXML() = 0;
};
#endif