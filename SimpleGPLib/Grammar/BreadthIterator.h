//--------------------------------------------------
// An iterator that does a breadth first traversal of a CodeTree
//
// @author: Wild Boar
//
// @date: 2022-09-30
//--------------------------------------------------

#pragma once

#include <queue>
#include <iostream>
using namespace std;

#include "CodeTree.h"

namespace NVL_AI
{
	class BreadthIterator
	{
	private:
		CodeTree * _tree;
		queue<NodeBase *> _current;
		queue<NodeBase *> _next;

	public:
		BreadthIterator(CodeTree * tree);

		NodeBase * Next();

		inline CodeTree * GetTree() { return _tree; }
	};
}
