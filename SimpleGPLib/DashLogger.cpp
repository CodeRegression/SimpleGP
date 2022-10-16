//--------------------------------------------------
// Implementation of class DashLogger
//
// @author: Wild Boar
//
// @date: 2022-10-06
//--------------------------------------------------

#include "DashLogger.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param sessionId Initialize variable <sessionId>
 * @param codeDash Initialize variable <codeDash>
 */
DashLogger::DashLogger(int sessionId, CodeDash * codeDash) 
{
	_sessionId = sessionId;
	_codeDash = codeDash;
}

//--------------------------------------------------
// Start Stop
//--------------------------------------------------

/**
 * @brief Start a session
 */
void DashLogger::Start()
{
	_codeDash->StartSession(_sessionId);
}

/**
 * @brief Stop a session
 */
void DashLogger::Stop()
{
	_codeDash->TerminateSession(_sessionId);
}

//--------------------------------------------------
// Message
//--------------------------------------------------

/**
 * @brief Show a message
 * @param message The message that we are raising
 */
void DashLogger::Message(const string& message)
{
	_codeDash->SetMessage(_sessionId, message);
}

//--------------------------------------------------
// Show Result
//--------------------------------------------------

/**
 * @brief Show the best result on screen
 * @param result The result that we want to display in string form
 */
void DashLogger::ShowResult(const string& result)
{
	_codeDash->SetBestCode(_sessionId, result);
}

//--------------------------------------------------
// Raise Error
//--------------------------------------------------

/**
 * @brief Raise an error within the system
 * @param error The error that we are raising
 */
void DashLogger::RaiseError(const string& error)
{
	_codeDash->RaiseError(_sessionId, error);
}

//--------------------------------------------------
// Update Score
//--------------------------------------------------

/**
 * @brief Update the current score
 * @param epoch The epoch that we are updating the score for
 * @param score The actual score that we are updating
 */
void DashLogger::UpdateScore(int epoch, double score)
{
	_codeDash->UpdateScore(_sessionId, epoch, score);
}