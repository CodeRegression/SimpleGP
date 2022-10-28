//--------------------------------------------------
// Unit Tests for class CandidateSelector
//
// @author: Wild Boar
//
// @date: 2022-02-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Grammar/CodeTreeFactory.h>
using namespace NVL_AI;

//--------------------------------------------------
// TestNode definition
//--------------------------------------------------

class TestNode : public NodeBase 
{
	private:
		int _value;
	public:
		TestNode(int value) : _value(value) { GetChildren().clear(); }
	
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
// TestGeneSelector definition
//--------------------------------------------------

class TestGeneSelector : public GeneSelector
{
    private:
        int _position;
        vector<bool> _values;
    public:
        TestGeneSelector(const vector<bool>& values) : _values(values), _position(0) {}

        virtual bool Next() override 
        {
            auto result = _values[_position++];
            if (_position >= _values.size()) _position = 0;
            return result;
        }
};

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that the gene split works as expected
 */
TEST(BreedTest, controlled_gene_split)
{
    // Setup : Create nodes
	auto nodes = vector<TestNode *>(); for (auto i = 0; i < 14; i++) nodes.push_back(new TestNode(i));

    // Setup: Build the first mother tree
    nodes[0]->AddChildren(vector<NodeBase *> { nodes[1], nodes[2] });
    nodes[1]->AddChildren(vector<NodeBase *> { nodes[3], nodes[4] });
    auto mother = new CodeTree(nodes[0], "test", vector<string>(), vector<double>());

    // Setup: Build the father tree
    nodes[5]->AddChildren(vector<NodeBase *> { nodes[6], nodes[7] });
    nodes[6]->AddChildren(vector<NodeBase *> { nodes[8], nodes[9] });
    nodes[7]->AddChildren(vector<NodeBase *> { nodes[10], nodes[11] });
    nodes[8]->AddChildren(vector<NodeBase *> { nodes[12], nodes[13] });
    auto father = new CodeTree(nodes[5], "test", vector<string>(), vector<double>());

    // Setup: Selector
    auto selector = TestGeneSelector(vector <bool> {true, false, true, false, false, true, true} );

    // Execute
    auto child = CodeTreeFactory::Breed(mother, father, &selector);
    auto iterator = BreadthIterator(child);
    auto actual = vector<int>(); auto node = iterator.Next(); 
    while (node != nullptr) 
    { 
        auto value = node->Evaluate(vector<double>());
        actual.push_back (value);  
        node = iterator.Next(); 
    }

    // Test
    auto expected = vector<double> { 5, 1, 7, 3, 4, 10, 11 };
    ASSERT_EQ(actual.size(), 7);
    for (auto i = 0; i < actual.size(); i++) ASSERT_EQ(expected[i], actual[i]);

    // Free variables
    delete child; 
    delete mother;
    delete father;
}