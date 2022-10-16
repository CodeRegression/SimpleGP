//--------------------------------------------------
// Implementation of the mutation logic
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "Mutation.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructor and Terminator
//--------------------------------------------------

/**
 * @brief Main Constructor
 * @param probability The probability of selecting a tree
 */
Mutation::Mutation(double probability) 
{
    _mutator = new NVL_AI::Mutator(probability);
}

/**
 * @brief Main Terminator
 */
Mutation::~Mutation() 
{
    delete _mutator;
}

//--------------------------------------------------
// Mutate
//--------------------------------------------------

/**
 * @brief Add the logic to perform mutation
 * @param candidate The candidate that we are mutating
 */
void Mutation::Mutate(CandidateBase * candidate)
{
    auto current = (Candidate *) candidate;
    _mutator->Mutate(current->GetTree());
}