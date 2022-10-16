//--------------------------------------------------
// Defines a basic engine for a vanilla C++ project.
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/FileUtils.h>

#include <SimpleGPLib/Globals.h>
#include <SimpleGPLib/ArgUtils.h>
#include <SimpleGPLib/Logger.h>
#include <SimpleGPLib/DashLogger.h>
#include <SimpleGPLib/CodeDash.h>
#include <SimpleGPLib/ScoreFinder.h>
#include <SimpleGPLib/Mutation.h>
#include <SimpleGPLib/CandidateFactory.h>

#include <GeneticLib/Utility/GeneticRunner.h>

namespace NVL_App
{
	class Engine
	{
	private:
		int _sessionId;
		NVLib::Parameters * _parameters;
		Logger* _logger;
		NVL_AI::CodeDash * _codeDash;
		NVL_AI::ScoreFinder * _scoreFinder;
		NVL_AI::CandidateFactory * _candidateFactory;
	public:
		Engine(Logger* logger, NVLib::Parameters * parameters);
		~Engine();

		void Run();
	private:
		double PerformIteration();

		NVL_AI::ScoreFinder * LoadScoreFinder();
		NVL_AI::CandidateFactory * LoadCandidateFactory();
		void GetOutputs(vector<double>& outputs);
	};
}
