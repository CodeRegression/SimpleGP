//--------------------------------------------------
// Unit Tests for class CandidateSelector
//
// @author: Wild Boar
//
// @date: 2022-02-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include "../Helpers/Candidate.h"

#include <GeneticLib/Utility/CandidateSelector.h>
using namespace NVL_AI;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bool CompareCandidates(CandidateBase * candidate_1, CandidateBase * candidate_2);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that we are selecting the correct ratio of elements
 */
TEST(CandidateSelector_Test, verify_selection_distrib)
{
	// Setup: Create a population
	auto population = vector<CandidateBase *>();
	for (auto i = 0; i < 100; i++) 
	{
		auto score = rand();
		auto data = vector<bool>(); 
		auto candidate = new Candidate(i, data); candidate->SetScore(score);
		population.push_back(candidate);
	}

	// Setup: Create a selector
	auto selector = CandidateSelector(10);

	// Execute: Perform the Tournanment	
	auto histogram = vector<int>(); for (auto i = 0; i < 100; i++) histogram.push_back(0);
	for (auto i = 0; i < 10000; i++) 
	{
		auto selected = selector.Select(population);
		histogram[selected->GetId()]++;
	}

	// Execute: Sort the array
	sort(population.begin(), population.end(), CompareCandidates);	
	
	// Find the winner of the tournament
	auto bestScore = histogram[0]; auto bestIndex = 0;
	for (auto i = 0; i < 100; i++) 
	{
		auto score = histogram[i];
		if (score > bestScore) { bestScore = score; bestIndex = i;}
	}

	// Confirm: The winder of the tournament is the one with the best score
	ASSERT_EQ(bestIndex, population[0]->GetId());

	// Teardown
	for (auto& candidate : population) delete candidate;
}

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------

/**
 * @brief A comparator between two candidate solutions
 * @param candidate_1 The first candidate
 * @param candidate_2 The second candidate
 * @return true Means that candidate one is "smaller"
 * @return false Means that candidate two is "smaller"
 */
bool CompareCandidates(CandidateBase * candidate_1, CandidateBase * candidate_2) 
{
	return candidate_1->GetScore() > candidate_2->GetScore();
}