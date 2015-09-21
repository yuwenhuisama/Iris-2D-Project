#include "IrisFloatTag.h"


IrisFloatTag::IrisFloatTag()
{
}

IrisFloatTag::IrisFloatTag(double dFloat) : m_dFloat(dFloat) {
}

IrisFloatTag::IrisFloatTag(char* szLiterral) {
	stringstream sstream;
	sstream << szLiterral;
	sstream >> m_dFloat;
}

string IrisFloatTag::ToString() {
	stringstream ssstream;
	ssstream << m_dFloat;
	return ssstream.str();
}

IrisFloatTag IrisFloatTag::Add(IrisFloatTag& iftFloat) {
	IrisFloatTag iftTmp;
	iftTmp.m_dFloat = m_dFloat + iftFloat.m_dFloat;
	return iftTmp;
}

IrisFloatTag IrisFloatTag::Sub(IrisFloatTag& iftFloat) {
	IrisFloatTag iftTmp;
	iftTmp.m_dFloat = m_dFloat - iftFloat.m_dFloat;
	return iftTmp;
}

IrisFloatTag IrisFloatTag::Mul(IrisFloatTag& iftFloat) {
	IrisFloatTag iftTmp;
	iftTmp.m_dFloat = m_dFloat * iftFloat.m_dFloat;
	return iftTmp;
}

IrisFloatTag IrisFloatTag::Div(IrisFloatTag& iftFloat) {
	IrisFloatTag iftTmp;
	iftTmp.m_dFloat = m_dFloat / iftFloat.m_dFloat;
	return iftTmp;
}

IrisFloatTag IrisFloatTag::Power(IrisFloatTag& iftFloat) {
	IrisFloatTag iftTmp;
	iftTmp.m_dFloat = pow((double)m_dFloat, (double)iftFloat.m_dFloat);
	return iftTmp;
}

bool IrisFloatTag::Equal(IrisFloatTag& iftFloat) {
	return m_dFloat == iftFloat.m_dFloat;
}

bool IrisFloatTag::NotEqual(IrisFloatTag& iftFloat) {
	return !Equal(iftFloat);
}

bool IrisFloatTag::BigThan(IrisFloatTag& iftFloat) {
	return m_dFloat > iftFloat.m_dFloat;
}

bool IrisFloatTag::BigThanOrEqual(IrisFloatTag& iftFloat) {
	return m_dFloat >= iftFloat.m_dFloat;
}

bool IrisFloatTag::LessThan(IrisFloatTag& iftFloat){
	return !BigThanOrEqual(iftFloat);
}

bool IrisFloatTag::LessThanOrEqual(IrisFloatTag& iftFloat){
	return !BigThan(iftFloat);
}

IrisFloatTag IrisFloatTag::Plus() {
	return IrisFloatTag(m_dFloat);
}

IrisFloatTag IrisFloatTag::Minus() {
	return IrisFloatTag(-m_dFloat);
}

IrisFloatTag::~IrisFloatTag()
{
}
