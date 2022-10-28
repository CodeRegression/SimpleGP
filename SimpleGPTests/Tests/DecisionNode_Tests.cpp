//--------------------------------------------------
// Unit Tests for class DecisionNode
//
// @author: Wild Boar
//
// @date: 2022-09-25
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Grammar/LiteralNode.h>
#include <SimpleGPLib/Grammar/DecisionNode.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the evaluation was correct
 */
TEST(DecisionNode_Test, verify_evaluation_true)
{
	// Setup: The parameters
	auto parameters = vector<double> { 2.0, 1.0 };
	auto names = vector<string> {"p1", "p2" };

	// Setup: The statement
	auto comparison = new Comparison(0, 1, Comparison::Operation::GREATER_THAN);
	auto statement = new BooleanStatement(comparison);

	// Setup: Create the node
	auto node = DecisionNode(statement);
	node.SetTrueNode(new LiteralNode(1));
	node.SetFalseNode(new LiteralNode(0));

	// Execute
	auto result = node.Evaluate(parameters);

	// Confirm
	ASSERT_EQ(result, 1);
}

/**
 * @brief Verify that the evaluation was correct
 */
TEST(DecisionNode_Test, verify_evaluation_false)
{
	// Setup: The parameters
	auto parameters = vector<double> { 2.0, 1.0 };
	auto names = vector<string> {"p1", "p2" };

	// Setup: The statement
	auto comparison = new Comparison(0, 1, Comparison::Operation::LESS_THAN);
	auto statement = new BooleanStatement(comparison);

	// Setup: Create the node
	auto node = DecisionNode(statement);
	node.SetTrueNode(new LiteralNode(1));
	node.SetFalseNode(new LiteralNode(0));

	// Execute
	auto result = node.Evaluate(parameters);

	// Confirm
	ASSERT_EQ(result, 0);
}

/**
 * @brief Verify that the code generation is correct
 */
TEST(DecisionNode_Test, verify_code)
{
	// Setup: The parameters
	auto parameters = vector<double> { 2.0, 1.0, 7.0 };
	auto names = vector<string> {"p1", "p2", "p3" };

	// Setup: The statement
	auto comparison = new Comparison(0, 1, Comparison::Operation::GREATER_THAN);
	auto statement = new BooleanStatement(comparison);

	// Setup: Create a subnode
	auto sub_comparison_1 = new Comparison(0, 2, Comparison::Operation::EQUALS);
	auto sub_comparison_2 = new Comparison(0, 1, Comparison::Operation::LESS_THAN);	
	auto sub_statement = new BooleanStatement(sub_comparison_1);
	sub_statement->AddComparison(BooleanStatement::Conjunction::OR, sub_comparison_2);
	auto sub_node = new DecisionNode(sub_statement);
	sub_node->SetTrueNode(new LiteralNode(1)); sub_node->SetFalseNode(new LiteralNode((int)0));

	// Setup: Create the node
	auto node = DecisionNode(statement);
	node.SetTrueNode(sub_node);
	node.SetFalseNode(new LiteralNode(2));

	// Setup: Expected Code
	auto expected = stringstream();
	expected << "if (p1 > p2)" << endl;
	expected << "{" << endl;
	expected << "\tif (p1 == p3 || p1 < p2)" << endl;
	expected << "\t{" << endl;
	expected << "\t\treturn 1;" << endl;
	expected << "\t}" << endl;
	expected << "\telse" << endl;
	expected << "\t{" << endl;
	expected << "\t\treturn 0;" << endl;
	expected << "\t}" << endl;
	expected << "}" << endl;
	expected << "else" << endl;
	expected << "{" << endl;
	expected << "\treturn 2;" << endl;
	expected << "}";

	// Execute
	auto actual = node.GetCode(names);

	// Confirm
	ASSERT_EQ(expected.str(), actual);
}

/**
 * @brief Confirm that the clone functionality is successful
 */
TEST(DecisionNode_Test, clone_functionality) 
{
	// Setup: The parameters
	auto parameters = vector<double> { 2.0, 1.0, 7.0 };
	auto names = vector<string> {"p1", "p2", "p3" };

	// Setup: The statement
	auto comparison = new Comparison(0, 1, Comparison::Operation::GREATER_THAN);
	auto statement = new BooleanStatement(comparison);

	// Setup: Create a subnode
	auto sub_comparison_1 = new Comparison(0, 2, Comparison::Operation::EQUALS);
	auto sub_comparison_2 = new Comparison(0, 1, Comparison::Operation::LESS_THAN);	
	auto sub_statement = new BooleanStatement(sub_comparison_1);
	sub_statement->AddComparison(BooleanStatement::Conjunction::OR, sub_comparison_2);
	auto sub_node = new DecisionNode(sub_statement);
	sub_node->SetTrueNode(new LiteralNode(1)); sub_node->SetFalseNode(new LiteralNode(0));

	// Setup: Create the node
	auto node = DecisionNode(statement);
	node.SetTrueNode(sub_node);
	node.SetFalseNode(new LiteralNode(2));

	// Setup: Abstraction
	auto cloneNode = node.Clone(); auto abstractNode = (DecisionNode *) cloneNode;
	ASSERT_EQ(cloneNode->GetChildren().size(), 2);
	ASSERT_EQ(cloneNode->GetChildren()[0], nullptr);
	ASSERT_EQ(cloneNode->GetChildren()[1], nullptr);
	ASSERT_EQ(abstractNode->GetTrueNode(), nullptr);
	ASSERT_EQ(abstractNode->GetFalseNode(), nullptr);

	// Setup: Add clones of the children
	abstractNode->SetFalseNode(node.GetFalseNode()->Clone());
	abstractNode->SetTrueNode(node.GetTrueNode()->Clone());
	((DecisionNode *)abstractNode->GetTrueNode())->SetTrueNode(sub_node->GetTrueNode()->Clone());
	((DecisionNode *)abstractNode->GetTrueNode())->SetFalseNode(sub_node->GetFalseNode()->Clone());

	// Setup: Expected Code
	auto expected = stringstream();
	expected << "if (p1 > p2)" << endl;
	expected << "{" << endl;
	expected << "\tif (p1 == p3 || p1 < p2)" << endl;
	expected << "\t{" << endl;
	expected << "\t\treturn 1;" << endl;
	expected << "\t}" << endl;
	expected << "\telse" << endl;
	expected << "\t{" << endl;
	expected << "\t\treturn 0;" << endl;
	expected << "\t}" << endl;
	expected << "}" << endl;
	expected << "else" << endl;
	expected << "{" << endl;
	expected << "\treturn 2;" << endl;
	expected << "}";

	// Execute
	auto actual = cloneNode->GetCode(names);

	// Confirm
	ASSERT_EQ(expected.str(), actual);

	// Free variables
	delete cloneNode;
}
