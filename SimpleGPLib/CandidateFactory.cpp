//--------------------------------------------------
// Utility: A factory type utility for generating new candidates
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "CandidateFactory.h"
using namespace NVL_AI;

//--------------------------------------------------
// Perform Random Generation
//--------------------------------------------------

/**
 * @brief Generates a pure random solution
 * @param id The identifier of the element that we are generating
 * @return CandidateBase* The candidate that we are generating
 */
CandidateBase * CandidateFactory::PerformRandomGeneration(int id)
{
    auto scoreFinder = (ScoreFinder *) GetScoreFinder();
    auto tree = NVL_AI::CodeTreeFactory::BuildTree(_functionName, scoreFinder->GetFields(), _outputs, _depthLimit, _statementLimit);
    return new Candidate(id, tree);
}

//--------------------------------------------------
// Perform Breed Generation
//--------------------------------------------------

/**
 * @brief Generate a candidate using the "breeding" process
 * @param id The identifier of the element that we are generating
 * @param parent1 The first parent
 * @param parent2 The second parent
 * @return CandidateBase* The generated child from the process
 */
CandidateBase * CandidateFactory::PerformBreedGeneration(int id, CandidateBase * parent1, CandidateBase * parent2) 
{
    auto mother = (Candidate *) parent1;
    auto father = (Candidate *) parent2;
    auto tree = NVL_AI::CodeTreeFactory::Breed(mother->GetTree(), father->GetTree(), _selector);
    return new Candidate(id, tree);
}