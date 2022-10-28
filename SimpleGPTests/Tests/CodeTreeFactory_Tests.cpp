//--------------------------------------------------
// Unit Tests for class CodeTreeFactory
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/FileUtils.h>

#include <SimpleGPLib/Grammar/Mutator.h>
#include <SimpleGPLib/Grammar/CodeTreeFactory.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the respect of a level 1 depth limit
 */
TEST(CodeTreeFactory_Test, depth_limit_1)
{
	// Setup
	srand(1);
	auto code = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2 }, 1, 2);

	// Confirm
	ASSERT_EQ(code->GetRoot()->NodeType(), "decision");
	auto root = (DecisionNode *) code->GetRoot();
	ASSERT_EQ(root->GetTrueNode()->NodeType(), "literal");
	ASSERT_EQ(root->GetFalseNode()->NodeType(), "literal");

	// Debug write the program to disk
	NVLib::FileUtils::WriteFile("output.cpp", code->GetCode());

	// Teardown
	delete code;
}

/**
 * @brief Confirm the respect of a level n depth limit
 */
TEST(CodeTreeFactory_Test, depth_limit_n)
{
	// Setup
	srand(1);
	auto code = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2, 7 }, 5, 2);

	// Debug write the program to disk
	NVLib::FileUtils::WriteFile("output_2.cpp", code->GetCode());

	// Teardown
	delete code;
}

/**
 * @brief Test out breeding
 */
TEST(CodeTreeFactory_Test, breed_test) 
{
	// Setup
	srand(1);
	auto selector = GeneSelector();
	auto mother = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2, 3, 4 }, 5, 2);
	auto father = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2, 3, 4 }, 5, 2);
	auto child = CodeTreeFactory::Breed(mother, father, &selector);

	// Debug write the program to disk
	NVLib::FileUtils::WriteFile("mother.cpp", mother->GetCode());
	NVLib::FileUtils::WriteFile("father.cpp", father->GetCode());
	NVLib::FileUtils::WriteFile("child.cpp", child->GetCode());

	// Teardown
	delete mother; delete father; delete child;
}

/**
 * @brief Test out breeding
 */
TEST(CodeTreeFactory_Test, breed_test_with_mutation) 
{
	// Setup
	srand(1);
	auto selector = GeneSelector();
	auto mother = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2, 3, 4 }, 5, 2);
	auto father = CodeTreeFactory::BuildTree("Test", vector<string> { "p1", "p2", "p3" }, vector<double> { 1, 2, 3, 4 }, 5, 2);
	auto child = CodeTreeFactory::Breed(mother, father, &selector);
	
	// Perform some mutation
	auto mutator = Mutator(1); 
	auto changed = mutator.Mutate(child);
	ASSERT_TRUE(changed);

	// Debug write the program to disk
	NVLib::FileUtils::WriteFile("mother_mutation.cpp", mother->GetCode());
	NVLib::FileUtils::WriteFile("father_mutation.cpp", father->GetCode());
	NVLib::FileUtils::WriteFile("child_mutation.cpp", child->GetCode());

	// Teardown
	delete mother; delete father; delete child;
}