//--------------------------------------------------
// Utility: Implementation of the logic to find the score
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <NVLib/Formatter.h>
#include <GeneticLib/Utility/ScoreFinderBase.h>
#include "Candidate.h"

namespace NVL_AI
{
	class ScoreFinder : public ScoreFinderBase
	{
    private:
        vector<bool> _solution;
	public:

        /**
         * @brief Main Constructor
         * @param solution The solution that we want the system to find
         */
		ScoreFinder(vector<bool>& solution) : _solution(solution) {}

        /**
         * @brief Calculate the score associated with a given candidate
         * @param candidate The candidate that we are calculating the score for
         * @return double The score as a double
         */
		virtual double GetScore(CandidateBase * candidate) override 
        {
            // Intiailize working variables
            auto score = 0.0; auto workingSolution = (Candidate *) candidate;

            // Confirm that the size of the provided solution is correct
            if (_solution.size() != workingSolution->GetData().size()) throw runtime_error(NVLib::Formatter() << "The provide solution needs to be length: " << _solution.size());

            // Determine the score
            for (auto i = 0; i < _solution.size(); i++) 
            {
                if (_solution[i] == workingSolution->GetData()[i]) score++;
            }

            // Return the score
            return score;        
        }
		
        /**
         * @brief Check to see if our proposed solution to the problem is "optimal"
         * @param candidate The solution that we are checking
         * @return true It is an optimal solution (no need to continue searching for a better one)
         * @return false There is still room for improvement
         */
        virtual bool ProblemSolved(CandidateBase * candidate) override
        {
            // Initialize working variables
            auto workingSolution = (Candidate *) candidate;

            // Compare the score with the ideal value - if there is a mismatch then quit
            for (auto i = 0; i < _solution.size(); i++) 
            {
                if (_solution[i] != workingSolution->GetData()[i]) return false;
            }

            return true;
        }

        inline int GetDataSize() { return (int)_solution.size(); }
	};
}
