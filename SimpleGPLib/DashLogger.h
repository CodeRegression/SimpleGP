//--------------------------------------------------
// A logger for the CodeDash
//
// @author: Wild Boar
//
// @date: 2022-10-06
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <GeneticLib/Utility/GeneticLogger.h>

#include "CodeDash.h"

namespace NVL_AI
{
	class DashLogger : public GeneticLogger
	{
	private:
		int _sessionId;
		CodeDash * _codeDash;

	public:
		DashLogger(int sessionId, CodeDash * codeDash);

		virtual void Start() override;
		virtual void Stop() override;

		virtual void Message(const string& message) override;
		virtual void ShowResult(const string& result) override;
		virtual void RaiseError(const string& error) override;
		virtual void UpdateScore(int epoch, double score) override;
	};
}
