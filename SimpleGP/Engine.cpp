//--------------------------------------------------
// Implementation code for the Engine
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "Engine.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructor and Terminator
//--------------------------------------------------

/**
 * Main Constructor
 * @param logger The logger that we are using for the system
 * @param parameters The input parameters
 */
Engine::Engine(Logger* logger, NVLib::Parameters* parameters) 
{
    _logger = logger; _parameters = parameters;
    _codeDash = new NVL_AI::CodeDash("dbconnect.xml");
    _scoreFinder = LoadScoreFinder();
    _candidateFactory = LoadCandidateFactory();
}

/**
 * Main Terminator 
 */
Engine::~Engine() 
{
    delete _parameters;
    delete _codeDash;
    delete _scoreFinder;
    delete _candidateFactory;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    while(true) 
    {
        NVLib::RandomUtils::TimeSeedRandomNumbers();

        auto result = PerformIteration();
        if (result >= 100) break;
    }
}

/**
 * @brief Performs an operation of the GP to see if we can solve the problem
 * @return double The result of what was performed
 */
double Engine::PerformIteration() 
{
   // Load parameters
    auto populationSize = ArgUtils::GetInteger(_parameters, "population");
    auto sampleSize = ArgUtils::GetInteger(_parameters, "sample");
    auto iterationCount = ArgUtils::GetInteger(_parameters, "iteration"); 

    // Setup the session and give it focus
    auto problemCode = ArgUtils::GetString(_parameters, "problem");
    _sessionId = _codeDash->CreateSession(NVL_AI::Constants::ALGORITHM_CODE, problemCode);
    _codeDash->UpdateScore(_sessionId, 0, 0);
    _codeDash->FocusSession(_sessionId);

    // Kick off the execution
    auto runner = new NVL_AI::GeneticRunner(_candidateFactory, populationSize, sampleSize);
    
	// Add the logic to set the logger
    runner->SetLogger(new NVL_AI::DashLogger(_sessionId, _codeDash));

	// Execute
	runner->Run(iterationCount);

    // Get the resultant score
    auto bestScore = runner->GetBestScore();

    // Free the runner
    delete runner;

    // Return the result
    return bestScore;
}

//--------------------------------------------------
// Loader Helpers
//--------------------------------------------------

/**
 * @brief Defines the logic to load the score finder 
 * @return NVL_AI::ScoreFinder The score finder that we are loading
 */
NVL_AI::ScoreFinder * Engine::LoadScoreFinder() 
{
    // Get the website folder
    auto folder = _codeDash->GetMeta(NVL_AI::Constants::META_SITE_LOCATION);
    if (folder == string()) throw runtime_error("Unable to determine the website location");

    // Get the training file name
    auto problemCode = ArgUtils::GetString(_parameters, "problem");
    auto trainingFile = _codeDash->GetTrainingPath(problemCode);
    if (trainingFile == string()) throw runtime_error("Unable to find training code: " + problemCode);

    // Build the training file path
    auto trainingPath = NVLib::FileUtils::PathCombine(folder, trainingFile);

    // Return the score finder
    return new NVL_AI::ScoreFinder(trainingPath);
}

/**
 * @brief Add the functionality to add a candidate 
 * @return NVL_AI::CandidateFactory* 
 */
NVL_AI::CandidateFactory * Engine::LoadCandidateFactory() 
{
    // Get the input parameters
    auto functionName = ArgUtils::GetString(_parameters, "function");
    auto outputs = vector<double>(); GetOutputs(outputs);
    auto depthLimit = ArgUtils::GetInteger(_parameters, "depth_limit");
    auto statementLimit = ArgUtils::GetInteger(_parameters, "statement_limit");
    auto mutateProbability = ArgUtils::GetDouble(_parameters, "mutate_prob");

    // Determine the mutation
    auto mutator = new NVL_AI::Mutation(mutateProbability);

    // Return the result
    return new NVL_AI::CandidateFactory(_scoreFinder, mutator, functionName, outputs, depthLimit, statementLimit);
}

/**
 * @brief Add the functionality to get the outputs for the system 
 * @param outputs The list of outputs associated with the system
 */
void Engine::GetOutputs(vector<double>& outputs) 
{
    auto outputString = ArgUtils::GetString(_parameters, "outputs");
    auto parts = vector<string>(); NVLib::StringUtils::Split(outputString, ',', parts);

    for (auto& part : parts) 
    {
        auto value = NVLib::StringUtils::String2Double(part);
        outputs.push_back(value);
    }
}
