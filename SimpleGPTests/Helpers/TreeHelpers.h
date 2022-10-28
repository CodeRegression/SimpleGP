//--------------------------------------------------
// Utility: Add some helper methods for testing code trees
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#pragma once

#include <SimpleGPLib/Grammar/LiteralNode.h>
#include <SimpleGPLib/Grammar/DecisionNode.h>
#include <SimpleGPLib/Grammar/CodeTree.h>
#include <SimpleGPLib/Grammar/Mutator.h>
using namespace NVL_AI;

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------

class TreeUtils
{
public:

    /**
     * @brief Generate the tree that we are working with 
     * @return NodeBase* The root node of the tree
     */
    static NodeBase * BuildTree() 
    {
        // Defines statements for the IF clause
        auto statement1 = new BooleanStatement(new Comparison(0,1, Comparison::Operation::EQUALS));
        statement1->AddComparison(BooleanStatement::Conjunction::AND, new Comparison(1, 2, Comparison::Operation::LESS_THAN));
        auto statement2 = new BooleanStatement(new Comparison(2, 3, Comparison::Operation::GREATER_THAN));

        // Create the root if clause
        auto root = new DecisionNode(statement1);
        
        // Add the true node
        auto child1 = new LiteralNode(7);
        root->SetTrueNode(child1);

        // Add the false node
        auto child2 = new DecisionNode(statement2);
        root->SetFalseNode(child2);

        // Add the 3rd child
        auto child3 = new LiteralNode(8);
        child2->SetTrueNode(child3);

        // Add the 4th child
        auto child4 = new LiteralNode(1);
        child2->SetFalseNode(child4);

        // Return the result
        return root;
    }	

    /**
     * @brief Create the source code representation of the built tree for testing purposes
     * @return string The source code representation of the tree
     */
    static string GetExpectedCode_1() 
    {
        auto result = stringstream();

        result << "double Evaluate(double p1, double p2, double p3, double p4)" << endl;
        result << "{" << endl;
        result << "\tif (p1 == p2 && p2 < p3)" << endl; 
        result << "\t{" << endl;
        result << "\t\treturn 7;" << endl;
        result << "\t}" << endl;
        result << "\telse" << endl; 
        result << "\t{" << endl;
        result << "\t\tif (p3 > p4)" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 8;" << endl;
        result << "\t\t}" << endl;
        result << "\t\telse" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 1;" << endl;
        result << "\t\t}" << endl;
        result << "\t}" << endl;
        result << "}" << endl;

        return result.str();
    }

    /**
     * @brief Create the source code representation of the built tree for testing purposes
     * @return string The source code representation of the tree
     */
    static string GetExpectedCode_2() 
    {
        auto result = stringstream();

        result << "double Evaluate(double p1, double p2, double p3, double p4)" << endl;
        result << "{" << endl;
        result << "\tif (p1 == p2 && p2 < p3)" << endl; 
        result << "\t{" << endl;
        result << "\t\treturn 7;" << endl;
        result << "\t}" << endl;
        result << "\telse" << endl; 
        result << "\t{" << endl;
        result << "\t\tif (p3 == p4)" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 8;" << endl;
        result << "\t\t}" << endl;
        result << "\t\telse" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 1;" << endl;
        result << "\t\t}" << endl;
        result << "\t}" << endl;
        result << "}" << endl;

        return result.str();
    }

    /**
     * @brief Create the source code representation of the built tree for testing purposes
     * @return string The source code representation of the tree
     */
    static string GetExpectedCode_3() 
    {
        auto result = stringstream();

        result << "double Evaluate(double p1, double p2, double p3, double p4)" << endl;
        result << "{" << endl;
        result << "\tif (p1 < p2 && p2 < p3)" << endl; 
        result << "\t{" << endl;
        result << "\t\treturn 7;" << endl;
        result << "\t}" << endl;
        result << "\telse" << endl; 
        result << "\t{" << endl;
        result << "\t\tif (p3 > p4)" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 8;" << endl;
        result << "\t\t}" << endl;
        result << "\t\telse" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 1;" << endl;
        result << "\t\t}" << endl;
        result << "\t}" << endl;
        result << "}" << endl;

        return result.str();
    }

    /**
     * @brief Create the source code representation of the built tree for testing purposes
     * @return string The source code representation of the tree
     */
    static string GetExpectedCode_4() 
    {
        auto result = stringstream();

        result << "double Evaluate(double p1, double p2, double p3, double p4)" << endl;
        result << "{" << endl;
        result << "\tif (p1 == p2 || p2 < p3)" << endl; 
        result << "\t{" << endl;
        result << "\t\treturn 7;" << endl;
        result << "\t}" << endl;
        result << "\telse" << endl; 
        result << "\t{" << endl;
        result << "\t\tif (p3 > p4)" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 8;" << endl;
        result << "\t\t}" << endl;
        result << "\t\telse" << endl; 
        result << "\t\t{" << endl;
        result << "\t\t\treturn 1;" << endl;
        result << "\t\t}" << endl;
        result << "\t}" << endl;
        result << "}" << endl;

        return result.str();
    }

};