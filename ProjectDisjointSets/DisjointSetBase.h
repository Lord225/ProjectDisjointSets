#pragma once

template<typename T, typename EL_TYPE>
class DisjointSetBase
{
public:
	virtual ~DisjointSetBase() = default;

	// Type of value that will uniquely represents any element inside the struct. 
	using NodeType = EL_TYPE;

	/// <summary>
	/// Finds an NodeType that represents the Set
	/// </summary>
	/// <param name="t">Any element of the set</param>
	/// <returns>An NodeType that represents set that contains value 't'</returns>
	virtual NodeType Find(NodeType t) = 0;

	/// <summary>
	/// Makes an Union of two sets. 
	/// </summary>
	/// <param name="x">Any element of set to merge</param>
	/// <param name="y">Any element of diffrent set to merge</param>
	virtual void Union(NodeType x, NodeType y) = 0;

	/// <summary>
	/// Adds new element and creates new set.
	/// </summary>
	/// <param name="el"></param>
	/// <returns></returns>
	virtual NodeType MakeSet(T el) = 0;

	/// <summary>
	/// Returns value of giver NodeType.
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	virtual T GetElement(NodeType t) = 0;
};
