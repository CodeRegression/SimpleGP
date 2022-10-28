//--------------------------------------------------
// A factory for generating random code trees
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>

#include "GeneSelector.h"
#include "BreadthIterator.h"

#include "CodeTree.h"
#include "DecisionNode.h"
#include "LiteralNode.h"

namespace NVL_AI
{
	class CodeTreeFactory
	{
	public:
		static CodeTree * BuildTree(const string& functionName, const vector<string>& paramNames, const vector<double>& outputs, int depthLimit, int statementLimit);
		static CodeTree * Breed(CodeTree * mother, CodeTree * father, GeneSelector * selector);
	private:
		static NodeBase * GetRandomNode(int paramCount, const vector<double>& outputs, int maxStatementLength, vector<double>& selectedOutputs);
		static BooleanStatement * GetStatement(int paramCount, int maxLength);
		static Comparison * GetComparison(int paramCount);
		static LiteralNode * GetLiteralNode(const vector<double>& outputs, vector<double>& selectedOutputs);
		static DecisionNode * GetDecisionNode(int paramCount, int maxStatementLength);
	
		static NodeBase * GetNextNode(BreadthIterator * i_1, BreadthIterator * i_2, GeneSelector * select, const vector<double>& outputs);
	};
}
