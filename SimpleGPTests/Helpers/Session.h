//--------------------------------------------------
// Defines details about the session
//
// @author: Wild Boar
//
// @date: 2022-10-04
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_AI
{
	class Session
	{
		private:
			string _algorithm;
			string _problem;
			string _status;
			bool _focus;
		public:
			Session(const string& algorithm, const string& problem, const string& status, bool focus) :
				_algorithm(algorithm), _problem(problem), _status(status), _focus(focus) {}

			inline string& GetAlgorithm() { return _algorithm; }
			inline string& GetProblem() { return _problem; }
			inline string& GetStatus() { return _status; }
			inline bool GetFocus() { return _focus; }
	};
}
