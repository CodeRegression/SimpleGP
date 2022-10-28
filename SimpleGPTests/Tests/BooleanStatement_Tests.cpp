//--------------------------------------------------
// Unit Tests for class BooleanStatement
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Grammar/BooleanStatement.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that evaluation works correctly
 */
TEST(BooleanStatement_Test, evaluation_test)
{
	// Setup
	auto params = vector<double> { 2, 5, 3, 1, 6 };
	auto names = vector<string> { "p1", "p2", "p3", "p4", "p5" };

	// Execute
	auto statement = BooleanStatement(new Comparison(0, 1, Comparison::Operation::EQUALS));
	statement.AddComparison(BooleanStatement::Conjunction::OR, new Comparison(2, 0, Comparison::Operation::GREATER_THAN));
	statement.AddComparison(BooleanStatement::Conjunction::AND, new Comparison(3, 4, Comparison::Operation::LESS_THAN));

	// Confirm
	ASSERT_TRUE(statement.Evaluate(params));
}

/**
 * @brief Confirm that the code regeneration works correctly
 */
TEST(BooleanStatement_Test, code_generation_test)
{
	// Setup
	auto params = vector<double> { 2, 5, 3, 1, 6 };
	auto names = vector<string> { "p1", "p2", "p3", "p4", "p5" };

	// Execute
	auto statement = BooleanStatement(new Comparison(0, 1, Comparison::Operation::EQUALS));
	statement.AddComparison(BooleanStatement::Conjunction::OR, new Comparison(2, 0, Comparison::Operation::GREATER_THAN));
	statement.AddComparison(BooleanStatement::Conjunction::AND, new Comparison(3, 4, Comparison::Operation::LESS_THAN));
	auto code = statement.GenerateCode(names);

	// Confirm
	ASSERT_EQ(code, "p1 == p2 || p3 > p1 && p4 < p5");
}