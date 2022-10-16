//--------------------------------------------------
// Basic Global variables
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_AI
{
	class Constants
	{
    public:
		// Defines the algorithm code
        inline static const string ALGORITHM_CODE = "GP_1";

		// The current list of available problems
		inline static const string PROBLEM_TOP_LEFT = "TLP_0000";

		// Session Statuses
		inline static const string STATUS_CREATED = "CREATE";
		inline static const string STATUS_START = "START";
		inline static const string STATUS_STOP = "STOP";
		inline static const string STATUS_END = "END";
		inline static const string STATUS_FAIL = "FAIL";

		// Meta
		inline static const string META_SITE_LOCATION = "SITE_LOCATION";
	};
}
