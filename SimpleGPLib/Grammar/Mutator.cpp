//--------------------------------------------------
// Implementation of class Mutator
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#include "Mutator.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param treeProb The probability that the tree gets altered
 */
Mutator::Mutator(double treeProb) : _treeProb(treeProb)
{
	// Extra implementation can come here
}

//--------------------------------------------------
// Mutate
//--------------------------------------------------

/**
 * @brief Performs the mutation functionality on the given code tree
 * @param tree The code tree that we are mutating
 * @return bool Returns a bool
 */
bool Mutator::Mutate(CodeTree * tree)
{
	// Make sure that the prob is set to something
	if (_treeProb <= 0) return false;

	// Decide if we are going to do something about this tree
	auto max = (int)ceil(1.0 / _treeProb); 
	auto mutateTree = (max <= 1) ? true : GetSelection(NVLib::Range<int>(1, max)) == 1;
	if (!mutateTree) return false;

	// Select the node that we want to process
	auto nodes = vector<DecisionNode *>(); auto nodeCount = GetDecisionNodes(tree, nodes);
	if (nodeCount == 0) return false;
	auto selectedNode = nodeCount == 1 ? 0 : GetSelection(NVLib::Range<int>(0, nodeCount));

	// Find if we want conjunctions or operators
	auto toggleElement = 0; 
	auto statement = nodes[selectedNode]->GetStatement();
	auto conjunctionCount = statement->GetConjunctions().size();
	auto comparisonCount = statement->GetComparisons().size();
	if (conjunctionCount == 0 && comparisonCount == 0) return false;
	else if (conjunctionCount != 0 && comparisonCount != 0) toggleElement = GetSelection(NVLib::Range<int>(0,2));
	else if (conjunctionCount == 0) toggleElement = 1;

	// Deal with the various elements
	if (toggleElement == 1) // Toggle a comparision 
	{
		auto elementId = comparisonCount == 1 ? 0 : GetSelection(NVLib::Range<int>(0, comparisonCount));
		auto element = statement->GetComparisons()[elementId];

		auto newOperatorId = (int)element->GetOperation();
		while(newOperatorId == (int)element->GetOperation()) 
		{
			newOperatorId = GetSelection(NVLib::Range<int>(0, 3));
		}

		statement->GetComparisons()[elementId]->SetOperation((Comparison::Operation) newOperatorId);		
	}
	else  // Toggle a conjunction
	{
		auto elementId = conjunctionCount == 1 ? 0 : GetSelection(NVLib::Range<int>(0, conjunctionCount));
		auto element = statement->GetConjunctions()[elementId];

		statement->GetConjunctions()[elementId] = element == BooleanStatement::Conjunction::AND ? BooleanStatement::Conjunction::OR : BooleanStatement::Conjunction::AND;
	}

	return true;
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Retrieves the given selection
 * @param range The range of values to select from
 * @return bool Returns a bool
 */
int Mutator::GetSelection(const NVLib::Range<int>& range)
{
	return NVLib::RandomUtils::GetInteger(range);
}

/**
 * @brief Retrieves the list of decision nodes
 * @param tree The code tree that we are getting the values for
 * @return int Returns a int
 */
int Mutator::GetDecisionNodes(CodeTree * tree, vector<DecisionNode *>& nodes)
{
	// Create an interator
	auto iterator = BreadthIterator(tree);

	// Make sure that the resultant nodeset is clear
	nodes.clear();

	// The list of nodes that we are iterating thru
	while (true) 
	{
		auto node = iterator.Next();
		if (node == nullptr) break;
		if (node->NodeType() == "decision") nodes.push_back((DecisionNode *)node);
	}

	// Return the node count
	return (int)nodes.size();	
}
