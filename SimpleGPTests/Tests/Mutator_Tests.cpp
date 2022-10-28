//--------------------------------------------------
// Unit Tests for class Mutator
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#include <gtest/gtest.h>

#include "../Helpers/TreeHelpers.h"

//--------------------------------------------------
// Override Mutator
//--------------------------------------------------

class TestMutator : public Mutator
{
private:
	int _position;
	vector<int> _selections;
public:
	TestMutator(const vector<int>& selections) : _selections(selections), _position(0), Mutator(0.1) {}
protected:
	virtual int GetSelection(const NVLib::Range<int>& range) override 
	{
		auto result = _selections[_position++];
		if (_position > _selections.size()) _position = 0;
		return result;
	}
};

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test the case in which nothing happens
 */
TEST(Mutator_Test, no_change)
{
	// Setup: Code Tree
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Setup Mutator
	auto mutator = TestMutator(vector<int> { 0 });
	
	// Execute
	auto updated = mutator.Mutate(&codeTree);
	auto actual = codeTree.GetCode();
	auto expected = TreeUtils::GetExpectedCode_1();

	// Confirm
	ASSERT_FALSE(updated);
	ASSERT_EQ(actual, expected);
}

/**
 * @brief Test the case when the mutator changes an operation
 */
TEST(Mutator_Test, operator_changed_1)
{
	// Setup: Code Tree
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Setup Mutator
	auto mutator = TestMutator(vector<int> { 1, 1, 0 });
	
	// Execute
	auto updated = mutator.Mutate(&codeTree);
	auto actual = codeTree.GetCode();
	auto expected = TreeUtils::GetExpectedCode_2();

	// Confirm
	ASSERT_TRUE(updated);
	ASSERT_EQ(actual, expected);
}

/**
 * @brief Test the case when the mutator changes an operation
 */
TEST(Mutator_Test, operator_changed_2)
{
	// Setup: Code Tree
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Setup Mutator
	auto mutator = TestMutator(vector<int> { 1, 0, 1, 0, 2 });
	
	// Execute
	auto updated = mutator.Mutate(&codeTree);
	auto actual = codeTree.GetCode();
	auto expected = TreeUtils::GetExpectedCode_3();

	// Confirm
	ASSERT_TRUE(updated);
	ASSERT_EQ(actual, expected);
}


/**
 * @brief Test the case when a conjunction is changed
 */
TEST(Mutator_Test, conjunction_changed)
{
	// Setup: Code Tree
	auto root = TreeUtils::BuildTree();
	auto codeTree = CodeTree(root, "Evaluate", vector<string> { "p1", "p2", "p3", "p4" }, vector<double> {1, 2});

	// Setup Mutator
	auto mutator = TestMutator(vector<int> { 1, 0, 0 });
	
	// Execute
	auto updated = mutator.Mutate(&codeTree);
	auto actual = codeTree.GetCode();
	auto expected = TreeUtils::GetExpectedCode_4();

	// Confirm
	ASSERT_TRUE(updated);
	ASSERT_EQ(actual, expected);
}