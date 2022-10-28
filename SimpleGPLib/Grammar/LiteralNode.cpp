//--------------------------------------------------
// Implementation of class LiteralNode
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#include "LiteralNode.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param value The value that this literal node needs to return
 */
LiteralNode::LiteralNode(double value) : _value(value)
{
	// Extra implementation can go here
}

//--------------------------------------------------
// Methods
//--------------------------------------------------

/**
 * @brief Retrieve the value of the node
 * @param parameters The parameters associated with the application
 * @return double Returns a double
 */
double LiteralNode::Evaluate(const vector<double> & parameters)
{
	return _value;
}

/**
 * @brief Retrieve the source code snippet associated with this node
 * @param names The names of parameters (that are not used in this case)
 * @param tabLevel The number of tables to render
 * @return string Return the resultant string
 */
string LiteralNode::GetCode(const vector<string>& names, int tabLevel)
{
	auto result = stringstream();
	result << Tab(tabLevel) << "return " << _value << ";";
	return result.str();	
}