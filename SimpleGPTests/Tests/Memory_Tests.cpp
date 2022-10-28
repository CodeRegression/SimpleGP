//--------------------------------------------------
// Unit Tests for class Checks the functionality for a memory leak
//
// @author: Wild Boar
//
// @date: 2022-02-11
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Grammar/DecisionNode.h>
#include <SimpleGPLib/Grammar/LiteralNode.h>

#include "../Helpers/TreeHelpers.h"
//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that the memory is working correctly
 */
TEST(Memory_Test, basic_memory_test) 
{
    // Create a tree
    auto tree = TreeUtils::BuildTree();

    // Perform the delete functionality
    delete tree;
}