//--------------------------------------------------
// A heirarchy of if statements designed to solve some problem
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <cassert>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

#include "NodeBase.h"

namespace NVL_AI
{
	class CodeTree
	{
	private:
		NodeBase * _root;
		string _functionName;
		vector<string> _paramNames;
		vector<double> _outputs;
	public:
		CodeTree(NodeBase * root, const string& functionName, const vector<string>& paramNames, const vector<double>& outputs);
		CodeTree(CodeTree * tree);
		~CodeTree();

		string GetCode();
		double Evaluate(vector<double> params);

		inline NodeBase * GetRoot() { return _root; }
		inline string& GetFunctionName() { return _functionName; }
		inline vector<string>& GetParamNames() { return _paramNames; }
		inline vector<double>& GetOutputs() { return _outputs; }
	private:
		NodeBase * Clone(NodeBase * root);
		void AddChild(NodeBase * node, NodeBase* child);
	};
}
