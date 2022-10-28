//--------------------------------------------------
// Unit Tests for class CodeTree
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include "../Helpers/TreeHelpers.h"

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Evaluate the algorithms ability to generate code
 */
TEST(CodeTree_Test, generate_code)
{
	// Setup
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Execute
	auto actual = codeTree.GetCode();
	auto expected = TreeUtils::GetExpectedCode_1();

	// Confirm
	ASSERT_EQ(actual, expected);
}

/**
 * @brief Verify the evaluation
 */
TEST(CodeTree_Test, evaluate)
{
	// Setup
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});
	auto values = vector<double> {1, 5, 2, 1};

	// Execute
	auto actual = codeTree.Evaluate(values);
	auto expected = 8.0;

	// Confirm
	ASSERT_EQ(actual, expected);
}

/**
 * @brief Confirm the clone functionality of a tree node
 */
TEST(CodeTree_Test, clone) 
{
	// Setup the initial tree
	auto root = TreeUtils::BuildTree();
	auto codeTree = new CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Generate code from this tree
	auto expected = codeTree->GetCode();
	cout << expected << endl;

	// Now clone the tree
	auto clone = new CodeTree(codeTree);

	// Delete the original code tree
	delete codeTree;

	// Generate the code for the new tree
	auto actual = clone->GetCode();

	// Confirm that they are identical
	ASSERT_EQ(expected, actual);

	// Delete clone
	delete clone;
}