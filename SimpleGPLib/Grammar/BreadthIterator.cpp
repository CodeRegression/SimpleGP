//--------------------------------------------------
// Implementation of class BreadthIterator
//
// @author: Wild Boar
//
// @date: 2022-09-30
//--------------------------------------------------

#include "BreadthIterator.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param tree The tree that we traversing
 */
BreadthIterator::BreadthIterator(CodeTree * tree) : _tree(tree)
{
	_current.push(tree->GetRoot());
}

//--------------------------------------------------
// Next
//--------------------------------------------------

/**
 * @brief Get the next element in the list
 * @return NodeBase * Returns a NodeBase *
 */
NodeBase * BreadthIterator::Next()
{
	// Replenish current if it is empty
	if (_current.size() == 0) 
	{
		while (_next.size() > 0) 
		{
			auto node = _next.front(); 
			_current.push(node);
			_next.pop();
		}
	}

	// If we are still empty -> this means that nothing is left
	if (_current.size() == 0) return nullptr;

	// Otherwise pop the node and add the children
	auto result = _current.front(); _current.pop();
	for (auto child : result->GetChildren()) _next.push(child);
	return result;
}
