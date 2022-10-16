//--------------------------------------------------
// Contains the interactions between the algorithm and code dash
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/StringUtils.h>

#include <DBLib/DBConnection.h>
#include <DBLib/GenericRepository.h>
using namespace NVL_DB;

#include "Globals.h"

namespace NVL_AI
{
	class CodeDash
	{
	private:
		bool _handleConnection;
		DBConnection * _connection;
	public:
		CodeDash(const string& path);
		CodeDash(DBConnection * connection);

		~CodeDash();

		int CreateSession(const string& algorithmCode, const string& problemCode);
		void StartSession(int sessionId);
		void PauseSession(int sessionId);
		void TerminateSession(int sessionId);
		void FocusSession(int sessionId);

		void UpdateScore(int sessionId, int epoch, double score);
		void SetBestCode(int sessionId, const string& code);
		void SetMessage(int sessionId, const string& message);
		void RaiseError(int sessionId, const string& message);

		string GetTrainingPath(const string& problemCode);
		string GetMeta(const string& key);
	private:
		int GetAlgorithmId(const string& code);
		int GetProblemId(const string& code);
		int GetStatusId(const string& code);
	};
}
