//--------------------------------------------------
// Implementation of class CodeTreeFactory
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "CodeTreeFactory.h"
using namespace NVL_AI;

//--------------------------------------------------
// Entry Point
//--------------------------------------------------

/**
 * @brief Generates a random code tree
 * @param functionName The function that we are generating
 * @param paramNames The list of output parameter names
 * @param outputs The list of associated output values
 * @param depthLimit A description of the elements within the system
 * @param statementLimit A limit as to how long a statement can be
 * @return CodeTree * Returns a CodeTree *
 */
CodeTree * CodeTreeFactory::BuildTree(const string& functionName, const vector<string>& paramNames, const vector<double>& outputs, int depthLimit, int statementLimit)
{
	// Setup the root node
	auto root = GetDecisionNode(paramNames.size(), statementLimit); 
	
	// Setup the node tracking variables (for appending children)
	auto current = vector<DecisionNode *>(); current.push_back(root); auto next = vector<DecisionNode *>(); 

	for (auto i = 0; i < depthLimit; i++) 
	{
		auto selectedOutputs = vector<double>();

		if (i == depthLimit - 1) 
		{
			for (auto node : current) 
			{
				node->SetTrueNode(GetLiteralNode(outputs, selectedOutputs));
				node->SetFalseNode(GetLiteralNode(outputs, selectedOutputs));
			}
		}
		else 
		{
			for (auto node : current) 
			{
				auto child1 = GetRandomNode(paramNames.size(), outputs, statementLimit, selectedOutputs); 
				if (child1->NodeType() == "decision") next.push_back((DecisionNode *)child1);
				
				auto child2 = GetRandomNode(paramNames.size(), outputs, statementLimit, selectedOutputs); 
				if (child2->NodeType() == "decision") next.push_back((DecisionNode *)child2);
				
				node->SetTrueNode(child1); node->SetFalseNode(child2);
			}
		}

		// Update the current and clear the next lists
		current.clear(); for (auto node : next) current.push_back(node); next.clear();
	}

	// Return the result
	return new CodeTree(root, functionName, paramNames, outputs);
}

//--------------------------------------------------
// Bread Logic
//--------------------------------------------------

/**
 * @brief The breed that we are dealing with 
 * @param mother The mother tree
 * @param father The father tree
 * @param selector The selector
 * @return CodeTree* The code tree
 */
CodeTree * CodeTreeFactory::Breed(CodeTree * mother, CodeTree * father, GeneSelector * selector) 
{
	// Setup breeder logic
	auto iterator1 = BreadthIterator(mother); auto iterator2 = BreadthIterator(father);

	// Create a root node
	auto root = GetNextNode(&iterator1, &iterator2, selector, mother->GetOutputs());

	// Create the queues
	auto current = queue<NodeBase *>(); auto next = queue<NodeBase *>();

	// Add the root node since it is guaranteed to have have children
	current.push(root);

	// Add required children until children are not needed anymore
	while (true) 
	{
		// Loop thru the current list and assign children -> update next to contain nodes that need children
		auto currentSize = current.size(); if (currentSize == 0) break;
		for (auto i = 0; i < currentSize; i++) 
		{
			auto node = current.front(); current.pop();

			for (auto j = 0; j < node->GetChildren().size(); j++) 
			{
				auto child = GetNextNode(&iterator1, &iterator2, selector, mother->GetOutputs());
				node->GetChildren()[j] = child;	
				if (child->GetChildren().size() > 0) next.push(child);
			}
		}

		// Verify that the current is now empty
		assert(current.size() == 0); 
		
		// Make next the new current ()
		auto nextSize = next.size(); 	
		for (auto i = 0; i < nextSize; i++) 
		{
			current.push(next.front()); next.pop();
		}		
	}

	// Return the new child
	auto parameterNames = mother->GetParamNames();
	return new CodeTree(root, mother->GetFunctionName(), parameterNames, mother->GetOutputs());
}

/**
 * @brief Get the next node
 * @param i_1 The first iterator
 * @param i_2 The second iterator
 * @param select A selector
 * @param outputs The list of given outputs
 * @return NodeBase* The node that we are dealing with
 */
NodeBase * CodeTreeFactory::GetNextNode(BreadthIterator * i_1, BreadthIterator * i_2, GeneSelector * select, const vector<double>& outputs) 
{
	auto option1 = i_1->Next();
	auto option2 = i_2->Next();

	if (option1 == nullptr && option2 == nullptr) 
	{
		auto list = vector<double>(); 
		return GetLiteralNode(outputs, list);
	}
	else if (option1 == nullptr) return option2->Clone();
	else if (option2 == nullptr) return option1->Clone();

	auto selection = select->Next();

	return selection ? option2->Clone() : option1->Clone();
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Generate a random node
 * @param paramNames The names of the parameters that we are working with
 * @param outputs The outputs that a literal can be assigned 
 * @param maxStatementLength The maximum size that a conditional statement can be 
 * @param selectedOutput A list of all the outputs already selected to avoid duplicates
 * @return NodeBase* The resultant node that was created
 */
NodeBase * CodeTreeFactory::GetRandomNode(int paramCount, const vector<double>& outputs, int maxStatementLength, vector<double>& selectedOutput) 
{
	auto selection = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, 2));

	if (selection == 0) return GetLiteralNode(outputs, selectedOutput);
	else return GetDecisionNode(paramCount, maxStatementLength);
}

/**
 * @brief Generate a statement
 * @param paramCount The number of parameters we have access to
 * @param maxLength A limit on the number of statements we can have
 * @return BooleanStatement * Returns a BooleanStatement *
 */
BooleanStatement * CodeTreeFactory::GetStatement(int paramCount, int maxLength)
{
	auto firstComparison = GetComparison(paramCount);
	auto statement = new BooleanStatement(firstComparison);
	auto length = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, maxLength));

	for (auto i = 0; i < length; i++) 
	{
		auto conjunctionId = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, 2));
		auto conjunction = (BooleanStatement::Conjunction) conjunctionId;
		auto comparision = GetComparison(paramCount); 
		statement->AddComparison(conjunction, comparision);
	}

	return statement;
}

/**
 * @brief Retrieve a comparison node
 * @param paramCount The number of parameters 
 * @return Comparison* The resultant comparison
 */
Comparison * CodeTreeFactory::GetComparison(int paramCount) 
{
	auto id_1 = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, paramCount));

	auto id_2 = 0;
	if (paramCount == 1) id_2 = id_1;
	else 
	{
		id_2 = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, paramCount));
		while (id_2 == id_1) id_2 = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, paramCount));
	}
	
	auto operationIndex = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, 3));
	auto operation = (Comparison::Operation) operationIndex;
	return new Comparison(id_1, id_2, operation);
}

/**
 * @brief Generate a literal node
 * @param outputs A list of legal outputs
 * @param selectedOutputs To avoid duplicates
 * @return LiteralNode * Returns a LiteralNode *
 */
LiteralNode * CodeTreeFactory::GetLiteralNode(const vector<double>& outputs, vector<double>& selectedOutputs)
{
	// Added extra logic to try and avoid duplicate literals on children
	auto selection = 0.0;
	if (selectedOutputs.size() >= outputs.size()) 
	{
		selection = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, outputs.size()));
		selectedOutputs.push_back(selection);
	}
	else 
	{
		auto contains = unordered_set<double>(); for (auto& entry : selectedOutputs) contains.insert(entry);
		selection = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, outputs.size()));
		while (contains.find(selection) != contains.end()) selection = NVLib::RandomUtils::GetInteger(NVLib::Range<int>(0, outputs.size()));		
		selectedOutputs.push_back(selection);
	}
	
	auto value = outputs[selection];
	return new LiteralNode(value);
}

/**
 * @brief Generate a decision node
 * @param paramCount A limit on the number of input parameters
 * @param maxStatementLength The limit on statement size
 * @return DecisionNode * Returns a DecisionNode *
 */
DecisionNode * CodeTreeFactory::GetDecisionNode(int paramCount, int maxStatementLength)
{
	auto statement = GetStatement(paramCount, maxStatementLength);
	return new DecisionNode(statement);
}