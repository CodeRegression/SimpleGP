//--------------------------------------------------
// Adds `mutations` to candidate solutions
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <SimpleGPLib/Grammar/Mutator.h>
#include <GeneticLib/Utility/MutationBase.h>

#include "Candidate.h"

namespace NVL_AI
{
	class Mutation : public MutationBase
	{
	private:
		Mutator * _mutator;
    public:
		Mutation(double probability);
		~Mutation();

        virtual void Mutate(CandidateBase * candidate) override;
	};
}
