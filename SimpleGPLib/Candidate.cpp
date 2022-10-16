//--------------------------------------------------
// Implementation of the candidate
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "Candidate.h"
using namespace NVL_AI;

//--------------------------------------------------
// Equality Check
//--------------------------------------------------

/**
 * @brief Main Constructor
 * @param id Candidate Identifier
 * @param tree The code tree representing this candidate
 */
Candidate::Candidate(int id, CodeTree * tree) : CandidateBase(id, 0), _tree(tree) 
{
    _code = (tree != nullptr) ? tree->GetCode() : string();
}

/**
 * @brief Main Terminator
 */
Candidate::~Candidate() 
{
    delete _tree;
}

//--------------------------------------------------
// Equality Check
//--------------------------------------------------

/**
 * @brief Equality check
 * @param candidate The candidate we are checking
 * @return true They are equal
 * @return false They are not equal
 */
bool Candidate::Equals(CandidateBase * candidate)
{
    return _code == candidate->ToString();
}

//--------------------------------------------------
// ToString
//--------------------------------------------------

/**
 * @brief Converts the solution to a string
 * @return string A string representation of the solution
 */
string Candidate::ToString() 
{
    return _code;
}

//--------------------------------------------------
// Clone
//--------------------------------------------------

/**
 * @brief Add the logic to clone a solution
 * @return CandidateBase* The cloned version of this solution
 */
CandidateBase * Candidate::Clone()
{
    auto id = GetId();
    auto tree = new CodeTree(_tree);
    auto result = new Candidate(id, tree);
    result->SetScore(GetScore());
    return result;
}