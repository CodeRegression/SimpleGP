//--------------------------------------------------
// Defines a factory for generating candidate solutions
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "Candidate.h"
#include "ScoreFinder.h"

#include <GeneticLib/Grammar/CodeTreeFactory.h>
#include <GeneticLib/Grammar/GeneSelector.h>

#include <GeneticLib/Utility/CandidateFactoryBase.h>

namespace NVL_AI
{
	class CandidateFactory : public CandidateFactoryBase
	{
	private:
		string _functionName;
		vector<double> _outputs;
		int _depthLimit;
		int _statementLimit;
		GeneSelector * _selector;
	public:
        CandidateFactory(	
							ScoreFinderBase * scoreFinder, 
							MutationBase * mutator, 
							const string& functionName,
							const vector<double>& outputs,
							int depthLimit,
							int statementLimit
						) 
		: CandidateFactoryBase(scoreFinder, mutator), _functionName(functionName), _outputs(outputs), _depthLimit(depthLimit), _statementLimit(statementLimit) 
		{
			_selector = new GeneSelector();
		} 

		~CandidateFactory() { delete _selector; }
    protected:
		virtual CandidateBase * PerformRandomGeneration(int id) override;
        virtual CandidateBase * PerformBreedGeneration(int id, CandidateBase * parent1, CandidateBase * parent2) override; 
	};
}
