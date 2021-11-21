#pragma once

template<typename T, typename EL_TYPE>
class DisjointSetBase
{
public:
	virtual Find(EL_TYPE& t) = 0;
	virtual Union(EL_TYPE& x, EL_TYPE& y) = 0;
	virtual MakeSet(T& el) = 0;
};