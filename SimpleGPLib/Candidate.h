//--------------------------------------------------
// Model: A candidate solution for this test case
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <SimpleGPLib/Grammar/CodeTree.h>
#include <GeneticLib/Model/CandidateBase.h>

namespace NVL_AI
{
	class Candidate : public CandidateBase
	{
	private:
        CodeTree * _tree;
        string _code;
    public:
		Candidate(int id, CodeTree * tree);
        ~Candidate();

        virtual bool Equals(CandidateBase * candidate) override;
        virtual string ToString() override;
        virtual CandidateBase * Clone() override;

        inline CodeTree * GetTree() { return _tree; }
    };
}
