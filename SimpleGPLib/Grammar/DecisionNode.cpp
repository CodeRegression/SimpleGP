//--------------------------------------------------
// Implementation of class DecisionNode
//
// @author: Wild Boar
//
// @date: 2022-09-25
//--------------------------------------------------

#include "DecisionNode.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param statement The statement that the decision needs to evaluate
 * @param level The level of the node
 */
DecisionNode::DecisionNode(BooleanStatement * statement) : _statement(statement)
{
	AddChild(nullptr); AddChild(nullptr);
}

/**
 * @brief Copy Constructor
 * @param node The node that we are copying
 */
DecisionNode::DecisionNode(DecisionNode * node) 
{
	_statement = new BooleanStatement(node->_statement);
	AddChild(nullptr); AddChild(nullptr);
}

/**
 * @brief Main Terminator
 */
DecisionNode::~DecisionNode()
{
	delete _statement;
}

//--------------------------------------------------
// Node
//--------------------------------------------------

/**
 * @brief Sets the true node of the decision
 * @param node The node we are setting to the true node
 */
void DecisionNode::SetTrueNode(NodeBase * node)
{
	if (GetChildren().size() <= 0) AddChild(node);
	else 
	{
		if (GetChildren()[0] != nullptr) delete GetChildren()[0]; 
		GetChildren()[0] = node;
	}
}

/**
 * @brief Sets the false node of the decision
 * @param node The node we are setting to be the false node
 */
void DecisionNode::SetFalseNode(NodeBase * node)
{
	if (GetChildren().size() <= 1)  
	{
		if (GetChildren().size() == 0) AddChild(nullptr);
		AddChild(node);
	}
	else 
	{
		if (GetChildren()[1] != nullptr) delete GetChildren()[1]; 
		GetChildren()[1] = node;
	}
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Retrieve the value of the node
 * @param parameters The parameters associated with the application
 * @return double Returns a double
 */
double DecisionNode::Evaluate(const vector<double> & parameters)
{
	auto condition = _statement->Evaluate(parameters);

	if (condition) 
	{
		if (GetTrueNode() == nullptr) throw runtime_error("Evaluation failed because the true node has not been set");
		return GetTrueNode()->Evaluate(parameters);
	}
	else 
	{
		if (GetFalseNode() == nullptr) throw runtime_error("Evaluation failed because the false node has not been set");
		return GetFalseNode()->Evaluate(parameters);
	}
}

//--------------------------------------------------
// Methods
//--------------------------------------------------

/**
 * @brief Retrieve the source code snippet associated with this node
 * @param names The parameters associated with the application
 * @param tabLevel The current tab level
 * @return string A string representing of the code
 */
string DecisionNode::GetCode(const vector<string> & names, int tabLevel)
{
	if (GetTrueNode() == nullptr || GetFalseNode() == nullptr) throw runtime_error("Cannot generate code because child nodes have not been set!");

	auto result = stringstream();

	result << Tab(tabLevel) << "if (" << _statement->GenerateCode(names) << ")" << endl;
	result << Tab(tabLevel) << "{" << endl;
	result << GetTrueNode()->GetCode(names, tabLevel + 1) << endl;
	result << Tab(tabLevel) << "}" << endl;
	result << Tab(tabLevel) << "else" << endl;
	result << Tab(tabLevel) << "{" << endl;
	result << GetFalseNode()->GetCode(names, tabLevel + 1) << endl;
	result << Tab(tabLevel) << "}";

	return result.str();
}