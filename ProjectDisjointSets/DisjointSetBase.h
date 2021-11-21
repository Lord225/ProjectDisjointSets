#pragma once

template<typename T, typename EL_TYPE>
class DisjointSetBase
{
public:
	/// <summary>
	/// TODO
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	virtual EL_TYPE Find(EL_TYPE t) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void Union(EL_TYPE x, EL_TYPE y) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="el"></param>
	/// <returns></returns>
	virtual EL_TYPE MakeSet(T el) = 0;
};
