//--------------------------------------------------
// Defines a node for returning a literal
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#pragma once

#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

#include "NodeBase.h"

namespace NVL_AI
{
	class LiteralNode : public NodeBase
	{
	private:
		double _value;
	public:
		LiteralNode(double value);

		virtual double Evaluate(const vector<double> & parameters) override;
		virtual string GetCode(const vector<string>& names, int tabLevel = 0) override;
		virtual string NodeType() override { return "literal"; }
		virtual NodeBase * Clone() override { return new LiteralNode(_value); }
	};
}
