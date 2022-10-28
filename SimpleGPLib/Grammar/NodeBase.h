//--------------------------------------------------
// A base class for a node within the system
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

namespace NVL_AI
{
	class NodeBase
	{
	private:
		vector<NodeBase *> _children;
	public:
		~NodeBase() 
		{ 
			for (auto& child : _children) 
			{
				if (child != nullptr) delete child;
			} 
		}

		virtual double Evaluate(const vector<double> & parameters) = 0;
		virtual string GetCode(const vector<string>& names, int tabLevel = 0) = 0;
		virtual string NodeType() = 0;
		virtual NodeBase * Clone() = 0;

		inline vector<NodeBase *>& GetChildren() { return _children; }

	protected:
		
		/**
		 * @brief A tab helper 
		 * @param count The number of tabs
		 * @return string The resultant
		 */
		inline string Tab(int count) 
		{
			auto result = stringstream();
			for (auto i = 0; i < count; i++) result << "\t";
			return result.str();
		}

		inline void AddChild(NodeBase * child) { _children.push_back(child); }
	};
}
