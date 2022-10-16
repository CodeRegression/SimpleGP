//--------------------------------------------------
// A repository for testing purposes
//
// @author: Wild Boar
//
// @date: 2022-10-04
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <DBLib/DBConnection.h>
#include <DBLib/GenericRepository.h>
using namespace NVL_DB;

#include "Session.h"

namespace NVL_Test
{
	class TestRepo
	{
	private:
		DBConnection * _connection;
	public:
		TestRepo(DBConnection * connection);

		void Clear();

		NVL_AI::Session * GetSessionDetails(int sessionId);
		string GetSessionStatus(int sessionId);	
		string GetSessionMessage(int sessionId);
		int GetFocusSessionId();
		double GetSessionScore(int sessionId);
		int GetSessionEpoch(int sessionId);
		string GetSessionCode(int sessionId);
	};
}
