//--------------------------------------------------
// A decision node within the system
//
// @author: Wild Boar
//
// @date: 2022-09-25
//--------------------------------------------------

#pragma once

#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

#include "NodeBase.h"
#include "BooleanStatement.h"

namespace NVL_AI
{
	class DecisionNode : public NodeBase
	{
	private:
		BooleanStatement * _statement;
	public:
		DecisionNode(BooleanStatement * statement);
		DecisionNode(DecisionNode * node);
		~DecisionNode();

		void SetTrueNode(NodeBase * node);
		void SetFalseNode(NodeBase * node);

		virtual double Evaluate(const vector<double> & parameters) override;
		virtual string GetCode(const vector<string> & names, int tabLevel = 0) override;
		virtual string NodeType() override { return "decision"; }
		virtual NodeBase * Clone() { return new DecisionNode(this); }

		inline BooleanStatement * GetStatement() { return _statement; }
		inline NodeBase * GetTrueNode() { return GetChildren().size() > 0 ? GetChildren()[0] : nullptr; }
		inline NodeBase * GetFalseNode() { return GetChildren().size() > 1 ? GetChildren()[1] : nullptr; }
	};
}
