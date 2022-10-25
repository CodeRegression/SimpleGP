//--------------------------------------------------
// The main logic for communicating with the code dash library
//
// @author: Wild Boar
//
// @date: 2022-10-24
//--------------------------------------------------

#pragma once

#include <sstream>
#include <unordered_map>
#include <iostream>
using namespace std;

#include <NVLib/StringUtils.h>

#include "Socket.h"

namespace NVL_AI
{
	class CodeDash
	{
	private:
		string _server;
		string _port;

		struct Response 
		{ 
			Response(int sessionId, const string& error) : SessionId(sessionId), Error(error) {}
			int SessionId; 
			string Error; 
		};

	public:
		CodeDash(const string& server, const string& port);

		int CreateSession(const string& algorithmCode, const string& problemCode, const string& machineName);
		void StartSession(int sessionId);
		void PauseSession(int sessionId);
		void EndSession(int sessionId);
		void FailSession(int sessionId, const string& message);

		void UpdateScore(int sessionId, int epoch, double score);
		void UpdateSolution(int sessionId, const string& solution);
		void SetMessage(int sessionId, const string& message);

		static CodeDash::Response Parse(const string& value);
	private:
		CodeDash::Response FireRequest(const unordered_map<string, string>& parameters);
		string BuildParamString(const unordered_map<string, string>& parameters);

		static string GetTagContent(const string& tag);

		static string Escape(const string& value);
	};
}
