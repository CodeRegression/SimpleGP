//--------------------------------------------------
// The logic to mutate a given code tree
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>

#include "CodeTree.h"
#include "BreadthIterator.h"
#include "DecisionNode.h"

namespace NVL_AI
{
	class Mutator
	{
	private:
		double _treeProb;
	public:
		Mutator(double treeProb);
		bool Mutate(CodeTree * tree);
	protected:
		virtual int GetSelection(const NVLib::Range<int>& range);
		int GetDecisionNodes(CodeTree * tree, vector<DecisionNode *>& nodes);
	};
}
