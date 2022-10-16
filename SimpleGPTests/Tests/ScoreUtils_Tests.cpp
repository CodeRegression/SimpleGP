//--------------------------------------------------
// Unit Tests for class ScoreUtils
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/FileUtils.h>

#include <SimpleGPLib/ScoreUtils.h>
using namespace NVL_AI;

#include <GeneticLib/Grammar/DecisionNode.h>
#include <GeneticLib/Grammar/LiteralNode.h>

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
string BuildData();

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that loading is happening correctly
 */
TEST(ScoreUtils_Test, load_test)
{
	// Setup
	auto data = BuildData();
	NVLib::FileUtils::WriteFile("test_file.arff", data);

	// Execute
	auto fieldNames = vector<string>();
	Mat input = ScoreUtils::LoadARFF("test_file.arff", fieldNames);
	auto inputData = (double *) input.data;

	// Confirm
	ASSERT_EQ(input.rows, 3);
	ASSERT_EQ(input.cols, 4);

	ASSERT_EQ(fieldNames.size(), 3);
	ASSERT_EQ(fieldNames[0], "p1");
	ASSERT_EQ(fieldNames[1], "p2");
	ASSERT_EQ(fieldNames[2], "p3");

	ASSERT_EQ(inputData[0], 1);
	ASSERT_EQ(inputData[1], 2);
	ASSERT_EQ(inputData[2], 3);
	ASSERT_EQ(inputData[3], 1);

	ASSERT_EQ(inputData[4], 2);
	ASSERT_EQ(inputData[5], 3);
	ASSERT_EQ(inputData[6], 4);
	ASSERT_EQ(inputData[7], 1);

	ASSERT_EQ(inputData[8], 2);
	ASSERT_EQ(inputData[9], 3);
	ASSERT_EQ(inputData[10], 1);
	ASSERT_EQ(inputData[11], 0);
}

/**
 * @brief Confirm that evaluation is happening correctly
 */
TEST(ScoreUtils_Test, evaluate_test)
{
	// Setup: Data
	auto data = BuildData();
	NVLib::FileUtils::WriteFile("test_file.arff", data);

	// Setup: Code
	auto comparison = new Comparison(0, 1, Comparison::Operation::LESS_THAN);
	auto statement = new BooleanStatement(comparison);
	auto root = new DecisionNode(statement);
	root->SetTrueNode(new LiteralNode(1)); 
	root->SetFalseNode(new LiteralNode(0));

	// Execute
	auto fieldNames = vector<string>();
	auto codeTree = CodeTree(root, "Eval", fieldNames, vector<double>());
	Mat testData = ScoreUtils::LoadARFF("test_file.arff", fieldNames);
	auto score = ScoreUtils::Evaluate(testData, &codeTree);

	// Confirm
	ASSERT_NEAR(score, 2.0 / 3.0, 1e-8);
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Generate a test data file
 * @return string The content of the data file
 */
string BuildData() 
{
	// Create a writer
	auto result = stringstream();

	// Write the header
	result << "@RELATION test" << endl << endl;
	result << "@ATTRIBUTE p1 NUMERIC" << endl;
	result << "@ATTRIBUTE p2 NUMERIC" << endl;
	result << "@ATTRIBUTE p3 NUMERIC" << endl;
	result << "@ATTRIBUTE class {0, 1}" << endl << endl;

	// Write the data
	result << "@DATA" << endl;
	result << "1,2,3,1" << endl;
	result << "2,3,4,1" << endl;
	result << "2,3,1,0" << endl;

	// Return the content
	return result.str();
}
