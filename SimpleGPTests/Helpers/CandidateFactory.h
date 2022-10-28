//--------------------------------------------------
// Utility: A factory type utility for generating new candidates
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "Candidate.h"
#include <GeneticLib/Utility/CandidateFactoryBase.h>

namespace NVL_AI
{
	class CandidateFactory : public CandidateFactoryBase
	{
	public:

        /**
         * @brief Main Constructor
         * @param scoreFinder A utility to "score" the candidate solution
         * @param mutator A utility to "mutate" a candidate solution
         */
		CandidateFactory(ScoreFinderBase * scoreFinder, MutationBase * mutator) : CandidateFactoryBase(scoreFinder, mutator) 
        {
            srand(10); // Set this to a given number because this is for unit testing!
        } 
    protected:

        /**
         * @brief Generates a pure random solution
         * @param id The identifier of the element that we are generating
         * @return CandidateBase* The candidate that we are generating
         */
		virtual CandidateBase * PerformRandomGeneration(int id) override 
        {
            auto solution = vector<bool>(); auto solutionSize = ((ScoreFinder *)GetScoreFinder())->GetDataSize();

            for (auto i = 0; i < solutionSize; i++) 
            {
                auto randomNumber = rand() % 2;
                auto value = randomNumber == 0;
                solution.push_back(value);
            }

            return new Candidate(id, solution);
        }
		
        /**
         * @brief Generate a candidate using the "breeding" process
         * @param id The identifier of the element that we are generating
         * @param parent1 The first parent
         * @param parent2 The second parent
         * @return CandidateBase* The generated child from the process
         */
        virtual CandidateBase * PerformBreedGeneration(int id, CandidateBase * parent1, CandidateBase * parent2) override 
        {
            auto solution = vector<bool>();

            auto p1 = (Candidate *) parent1; auto p2 = (Candidate *) parent2;

            for (auto i = 0; i < p1->GetData().size(); i++) 
            {
                auto randomNumber = rand() % 2;
                auto value = randomNumber == 0 ? p1->GetData()[i] : p2->GetData()[i];
                solution.push_back(value);
            }

            auto result = new Candidate(id, solution);
            return result;
        }
	};
}
