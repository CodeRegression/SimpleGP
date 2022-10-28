//--------------------------------------------------
// Utility: Adds `mutations` to candidate solutions
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <GeneticLib/Utility/MutationBase.h>

#include "Candidate.h"

namespace NVL_AI
{
	class Mutation : public MutationBase
	{
    public:

        Mutation() 
        {
            srand(20); // Set the random number seed as a hard value because this is unit testing
        }

        /**
         * @brief Add the logic to perform mutation
         * @param candidate The candidate that we are mutating
         */
        virtual void Mutate(CandidateBase * candidate) override
        {
            auto workingCandidate = (Candidate *) candidate; 

            auto dataSize = (int)workingCandidate->GetData().size();
            auto mutateCount = (int)round(dataSize * 0.05);
            if (mutateCount <= 0) return;

            for (auto i = 0; i < mutateCount; i++) 
            {
                if (rand() % 2 == 0) continue;
                auto index = rand() % (workingCandidate->GetData().size());
                workingCandidate->GetData()[index] = !workingCandidate->GetData()[index];  
            }
        }
	};
}
