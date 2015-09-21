#include "IrisIntegerTag.h"
#include "IrisFloatTag.h"

IrisIntegerTag::operator IrisFloatTag() {
	IrisFloatTag iftFloat;
	iftFloat.m_dFloat = (double)m_nInteger;
	return iftFloat;
}

string IrisIntegerTag::ToString() {
	stringstream ssstream;
	ssstream << m_nInteger;
	return ssstream.str();
}

IrisIntegerTag::IrisIntegerTag() : m_nInteger(0) {

}

IrisIntegerTag::IrisIntegerTag(int nInteger) : m_nInteger(nInteger) {
}

IrisIntegerTag::IrisIntegerTag(char* szLiterral)
{
	stringstream sstream;
	sstream << szLiterral;
	sstream >> m_nInteger;
}

IrisIntegerTag IrisIntegerTag::Add(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = m_nInteger + iitInteger.m_nInteger;
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::Sub(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = m_nInteger - iitInteger.m_nInteger;
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::Mul(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = m_nInteger * iitInteger.m_nInteger;
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::Div(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = m_nInteger / iitInteger.m_nInteger;
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::Mod(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = m_nInteger % iitInteger.m_nInteger;
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::Power(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (int)pow((double)m_nInteger, (double)iitInteger.m_nInteger);
	return iitTmp;
}

// Âß¼­ÒÆÎ» ÎŞ·ûºÅÊı;ËãÊõÒÆÎ» ÓĞ·ûºÅÊı
// Âß¼­ÓÒÒÆ
IrisIntegerTag IrisIntegerTag::Shr(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (((unsigned int)m_nInteger) >> iitInteger.m_nInteger);
	return iitTmp;
}

// Âß¼­×óÒÆ
IrisIntegerTag IrisIntegerTag::Shl(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (((unsigned int)m_nInteger) << iitInteger.m_nInteger);
	return iitTmp;
}

// ËãÊõÓÒÒÆ
IrisIntegerTag IrisIntegerTag::Sar(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (m_nInteger >> iitInteger.m_nInteger);
	return iitTmp;
}

// ËãÊõ×óÒÆ
IrisIntegerTag IrisIntegerTag::Sal(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (m_nInteger << iitInteger.m_nInteger);
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::BitXor(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (((unsigned int)m_nInteger) ^ ((unsigned int)iitInteger.m_nInteger));
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::BitAnd(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (((unsigned int)m_nInteger) & ((unsigned int)iitInteger.m_nInteger));
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::BitOr(IrisIntegerTag& iitInteger) {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = (((unsigned int)m_nInteger) | ((unsigned int)iitInteger.m_nInteger));
	return iitTmp;
}

IrisIntegerTag IrisIntegerTag::BitNot() {
	IrisIntegerTag iitTmp;
	iitTmp.m_nInteger = ~(unsigned int)m_nInteger;
	return iitTmp;
}

bool IrisIntegerTag::Equal(IrisIntegerTag& iitInteger) {
	return m_nInteger == iitInteger.m_nInteger;
}

bool IrisIntegerTag::NotEqual(IrisIntegerTag& iitInteger) {
	return !Equal(iitInteger);
}

bool IrisIntegerTag::BigThan(IrisIntegerTag& iitInteger){
	return m_nInteger > iitInteger.m_nInteger;
}

bool IrisIntegerTag::BigThanOrEqual(IrisIntegerTag& iitInteger){
	return m_nInteger >= iitInteger.m_nInteger;
}

bool IrisIntegerTag::LessThan(IrisIntegerTag& iitInteger){
	return !BigThanOrEqual(iitInteger);
}

bool IrisIntegerTag::LessThanOrEqual(IrisIntegerTag& iitInteger){
	return !BigThan(iitInteger);
}

IrisIntegerTag IrisIntegerTag::Plus() {
	return IrisIntegerTag(m_nInteger);
}

IrisIntegerTag IrisIntegerTag::Minus() {
	return IrisIntegerTag(-m_nInteger);
}

IrisIntegerTag::~IrisIntegerTag()
{
}
