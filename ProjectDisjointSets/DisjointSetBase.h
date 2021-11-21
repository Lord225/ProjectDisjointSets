#pragma once

template<typename T, typename EL_TYPE>
class DisjointSetBase
{
public:
	virtual EL_TYPE Find(EL_TYPE t) = 0;
	virtual void Union(EL_TYPE x, EL_TYPE y) = 0;
	virtual EL_TYPE MakeSet(T el) = 0;
};
