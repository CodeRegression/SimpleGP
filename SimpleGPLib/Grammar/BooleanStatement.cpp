//--------------------------------------------------
// Implementation of class BooleanStatement
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#include "BooleanStatement.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param comparison A comparison of parameters
 */
BooleanStatement::BooleanStatement(Comparison * comparison)
{
	_comparisons.push_back(comparison);
}

/**
 * @brief Clone constructor
 * @param statement The statement that we are cloning
 */
BooleanStatement::BooleanStatement(BooleanStatement* statement) 
{
	// Clone the comparisons
	_comparisons = vector<Comparison *>();
	for (auto comparison : statement->_comparisons) _comparisons.push_back(new Comparison(comparison));		
		
	// Clone the junctions	
	_conjunctions = vector<Conjunction>();
	for (auto conjunction : statement->_conjunctions) _conjunctions.push_back(conjunction);
}

/**
 * @brief Main Terminator
 */
BooleanStatement::~BooleanStatement()
{
	for (auto comparison : _comparisons) delete comparison;
}

//--------------------------------------------------
// Add
//--------------------------------------------------

/**
 * @brief Add a new comparison to the statement
 * @param conjunction The conjunction relating this statement with the previous one
 * @param comparison The new comparison that we are adding
 */
void BooleanStatement::AddComparison(Conjunction conjunction, Comparison * comparison)
{
	_conjunctions.push_back(conjunction); _comparisons.push_back(comparison);
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Evaluate the statement
 * @param params The associated input parameters
 * @return bool Returns a bool
 */
bool BooleanStatement::Evaluate(const vector<double>& params)
{
	bool result = _comparisons[0]->Evaluate(params);

	for (auto i = 1; i < _comparisons.size(); i++) 
	{
		auto operation = _conjunctions[i - 1];
		auto value = _comparisons[i]->Evaluate(params);

		if (operation == Conjunction::AND) result &= value;
		else result |= value;

	}

	return result;
}

//--------------------------------------------------
// Generate Code
//--------------------------------------------------

/**
 * @brief Generate the code version of the system
 * @param paramNames The names of the parameters that we are using to perform the evaluation
 * @return string Returns a string
 */
string BooleanStatement::GenerateCode(const vector<string>& paramNames)
{
	auto result = stringstream(); result << _comparisons[0]->GetCode(paramNames);

	for (auto i = 1; i < _comparisons.size(); i++) 
	{
		auto operation = _conjunctions[i - 1];
		auto subCode = _comparisons[i]->GetCode(paramNames);

		if (operation == Conjunction::AND) result << " && " << subCode;
		else result << " || " << subCode;
	}

	return result.str();
}