//--------------------------------------------------
// Models the comparison between two parameters
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
	class Comparison
	{
	public:
		enum class Operation { EQUALS = 0, GREATER_THAN = 1, LESS_THAN = 2 };
	private:
		int _param1;
		int _param2;
		Operation _operation;
	public:
		Comparison(int param1, int param2, Operation operation) :
			_param1(param1), _param2(param2), _operation(operation) {}

		Comparison(Comparison * comparison) : 
			_param1(comparison->_param1), _param2(comparison->_param2), _operation(comparison->_operation) {}

		bool Evaluate(const vector<double>& params);
		string GetCode(const vector<string>& paramNames);

		inline int& GetParam1() { return _param1; }
		inline int& GetParam2() { return _param2; }
		inline Operation& GetOperation() { return _operation; }
		inline void SetOperation(Operation value) { _operation = value; } 
	};
}
