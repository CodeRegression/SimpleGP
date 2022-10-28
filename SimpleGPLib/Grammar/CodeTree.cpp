//--------------------------------------------------
// Implementation of class CodeTree
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "CodeTree.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param root Initialize variable <root>
 * @param functionName Initialize variable <functionName>
 * @param paramNames Initialize variable <paramNames>
 * @param outputs The list of possible outputs that could come after system execution
 */
CodeTree::CodeTree(NodeBase * root, const string& functionName, const vector<string>& paramNames, const vector<double>& outputs)
{
	_root = root;
	_functionName = functionName;
	_paramNames = paramNames;
	_outputs = outputs;
}

/**
 * @brief Defines a copy constructor
 * @param tree  The tree that we are cloning
 */
CodeTree::CodeTree(CodeTree * tree) 
{
	_root = Clone(tree->_root);
	_functionName = tree->_functionName;
	_paramNames = tree->_paramNames;
	_outputs = tree->_outputs;
}

/**
 * @brief Main Terminator
 */
CodeTree::~CodeTree()
{
	if (_root != nullptr) delete _root;
}

//--------------------------------------------------
// Code Generation
//--------------------------------------------------

/**
 * @brief Generates the code for the function
 * @return string Returns a string
 */
string CodeTree::GetCode()
{
	// Make sure that we have a valid tree
	if (_root == nullptr) return string();

	// Create the value for holding the result
	auto result = stringstream();

	// Add the function start
	result << "double " << _functionName << "(";
	for (auto i = 0; i < _paramNames.size(); i++) 
	{
		if (i != 0) result << ", ";
		result << "double " << _paramNames[i];
	}
	result << ")" << endl << "{" << endl;

	// Build the result
	result << _root->GetCode(_paramNames, 1) << endl;

	// Add the function end
	result << "}" << endl;

	// Return the result
	return result.str();
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Evaluate the given solution
 * @param params The parameters that we are evaluating against
 * @return double Returns a double
 */
double CodeTree::Evaluate(vector<double> params)
{
	return _root->Evaluate(params);
}

//--------------------------------------------------
// Clone functionality
//--------------------------------------------------

/**
 * @brief Perform the cloning of the actual tree 
 * @param root The root node
 * @return NodeBase* The resultant tree
 */
NodeBase * CodeTree::Clone(NodeBase * root) 
{
	// Create a current and next
	auto current = queue<NodeBase *>(); auto current_new = queue<NodeBase *>();  
	auto next = queue<NodeBase *>(); auto next_new = queue<NodeBase *>();

	// Add a new root
	auto newRoot = root->Clone();
	current.push(root); current_new.push(newRoot);

	while (true) 
	{
		auto layerSize = current_new.size();
		for (auto i = 0; i < layerSize; i++) 
		{
			auto currentNode = current.front(); current.pop();
			auto newNode = current_new.front(); current_new.pop();

			for (auto childId = 0; childId < currentNode->GetChildren().size(); childId++) 
			{
				auto child = currentNode->GetChildren()[childId];
				auto newChild = child->Clone();
				AddChild(newNode, newChild);
				if (child->GetChildren().size() > 0) 
				{
					next.push(child); next_new.push(newChild); 
				}
			}
		}

		assert(current.size() == 0);

		auto nextSize = next_new.size();
		if (nextSize == 0) break;

		for (auto i = 0; i < nextSize; i++) 
		{
			auto node = next.front(); next.pop(); current.push(node);
			auto new_node = next_new.front(); next_new.pop(); current_new.push(new_node);
		}
	}

	return newRoot;
}

/**
 * @brief Defines the logic for adding a child 
 */
void CodeTree::AddChild(NodeBase * node, NodeBase* child) 
{
	for (auto i = 0; i < node->GetChildren().size(); i++) 
	{
		if (node->GetChildren()[i] == nullptr) 
		{
			node->GetChildren()[i] = child;
			return;
		}
	}
	node->GetChildren().push_back(child);
}