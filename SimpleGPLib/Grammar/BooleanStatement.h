//--------------------------------------------------
// A boolean statement that an if statement can evaluate
//
// @author: Wild Boar
//
// @date: 2022-09-24
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "Comparison.h"

namespace NVL_AI
{
	class BooleanStatement
	{
	public:	
		enum class Conjunction { AND=1, OR=2 };
	private:
		vector<Comparison *> _comparisons;
		vector<Conjunction> _conjunctions;
	public:
		BooleanStatement(Comparison * comparison);
		BooleanStatement(BooleanStatement* statement);
		~BooleanStatement();

		void AddComparison(Conjunction conjunction, Comparison * comparison);
		bool Evaluate(const vector<double>& params);
		string GenerateCode(const vector<string>& paramNames);

		inline vector<Comparison *>& GetComparisons() { return _comparisons; }
		inline vector<Conjunction>& GetConjunctions() { return _conjunctions; }
	};
}
