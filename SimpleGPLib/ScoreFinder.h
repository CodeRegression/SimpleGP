//--------------------------------------------------
// Implementation of the logic to find the score
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/Formatter.h>

#include <GeneticLib/Utility/ScoreFinderBase.h>

#include "Candidate.h"
#include "ScoreUtils.h"

namespace NVL_AI
{
	class ScoreFinder : public ScoreFinderBase
	{
	private:
		Mat _testCases;
		vector<string> _fields;
	public:
		ScoreFinder(const string& trainingPath);

		virtual double GetScore(CandidateBase * candidate) override;		
        virtual bool ProblemSolved(CandidateBase * candidate) override;
	
		inline vector<string>& GetFields() { return _fields; }
	};
}
