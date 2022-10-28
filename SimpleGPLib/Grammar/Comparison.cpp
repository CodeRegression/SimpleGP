//--------------------------------------------------
// Implementation of class Comparison
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#include "Comparison.h"
using namespace NVL_AI;

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Evaluate the comparison expression
 * @param params The parameters that we are evaluating
 * @return bool Returns a bool
 */
bool Comparison::Evaluate(const vector<double>& params)
{
	auto value1 = params[_param1];
	auto value2 = params[_param2];

	switch(_operation) 
	{
		case Operation::EQUALS: return abs(value1 - value2) < 1e4;
		case Operation::GREATER_THAN: return value1 > value2;
		case Operation::LESS_THAN: return value1 < value2;
	}

	return false;
}

//--------------------------------------------------
// Code
//--------------------------------------------------

/**
 * @brief Retrieve a code value of the expression
 * @param paramNames The names of the parameters that we want to use in our code
 * @return string Returns a string
 */
string Comparison::GetCode(const vector<string>& paramNames)
{
	// Retrieve the names of the parameters
	auto name1 = paramNames[_param1];
	auto name2 = paramNames[_param2];

	// Start a string to capture the result
	auto result = stringstream();

	// Add the first name to the string
	result << name1;

	// Add the operation to the string
	switch(_operation) 
	{
		case Operation::EQUALS: result << " == "; break;
		case Operation::GREATER_THAN: result << " > "; break;
		case Operation::LESS_THAN: result << " < "; break;
		default: throw runtime_error("Unknown operation!");
	}

	// Add the second parameter to the result
	result << name2;

	// Return the result
	return result.str();
}
