//--------------------------------------------------
// Unit Tests for class BreadthIterator
//
// @author: Wild Boar
//
// @date: 2022-09-30
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Grammar/BreadthIterator.h>
using namespace NVL_AI;

//--------------------------------------------------
// TestNode definition
//--------------------------------------------------

class TestNode : public NodeBase 
{
	private:
		int _value;
	public:
		TestNode(int value) : _value(value) {}
	
		virtual double Evaluate(const vector<double>& parameters) override { return _value; }
		virtual string GetCode(const vector<string>& names, int tabLevel) override { return string(); }
		virtual string NodeType() override { return "TestNode"; }

        virtual NodeBase * Clone() override 
        { 
            auto result = new TestNode(_value);  
            for (auto i = 0; i < GetChildren().size(); i++) result->AddChild(nullptr);
            return result;
        }

		inline void AddChildren(const vector<NodeBase *>& children) 
		{
			for (auto child : children) AddChild(child);
		}
};

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the iteration is working correctly
 */
TEST(BreadthIterator_Test, test_iteration)
{
	// Setup : Create nodes
	auto nodes = vector<TestNode *>(); for (auto i = 0; i < 7; i++) nodes.push_back(new TestNode(i));

	// Setup: Link the nodes
	nodes[0]->AddChildren(vector<NodeBase *> { nodes[1], nodes[2] } );
	nodes[1]->AddChildren(vector<NodeBase *> { nodes[3], nodes[4] } );
	nodes[4]->AddChildren(vector<NodeBase *> { nodes[5], nodes[6] } );

	// Create the code tree
	auto tree = CodeTree(nodes[0], "test", vector<string>(), vector<double>());

	// Execute
	auto iterator = BreadthIterator(&tree); auto values = vector<double>(); auto params = vector<double>(); 
	
	while (true) 
	{
		auto node = iterator.Next();
		if (node == nullptr) break;
		values.push_back(node->Evaluate(params));
	}

	// Confirm
	ASSERT_EQ((int)values.size(), 7);
	for (auto i = 0; i < values.size(); i++) ASSERT_EQ(values[i], i);
}
