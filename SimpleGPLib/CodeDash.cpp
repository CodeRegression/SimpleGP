//--------------------------------------------------
// Implementation of class CodeDash
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#include "CodeDash.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param path A path to the configuration file
 */
CodeDash::CodeDash(const string& path)
{
	_connection = new DBConnection(path);
	_handleConnection = true;
}

/**
 * @brief Custom Constructor
 * @param connection The connection to the database
 */
CodeDash::CodeDash(DBConnection * connection)
{
	_connection = connection;
	_handleConnection = false;
}

/**
 * @brief Main Terminator
 */
CodeDash::~CodeDash()
{
	if (_handleConnection) delete _connection;
}

//--------------------------------------------------
// Session
//--------------------------------------------------

/**
 * @brief Create a new session
 * @param algorithmCode The identifier of the algorithm
 * @param problemCode The identifier of the problem
 * @return int Returns a int
 */
int CodeDash::CreateSession(const string& algorithmCode, const string& problemCode)
{
	// Get codes
	auto statusId = GetStatusId(Constants::STATUS_CREATED);
	auto algorithmId = GetAlgorithmId(algorithmCode);
	auto problemId = GetProblemId(problemCode);
	if (algorithmId == -1 || problemId == -1) throw runtime_error("Unregistered problem solver or problem");

	// Create the query
	auto query = stringstream();
	query << "INSERT INTO `session`(`algorithm_id`, `problem_id`, `status_id`,`epoch`,`best_score`,`focus`) ";
	query << "VALUES (";
	query << algorithmId << ", ";
	query << problemId << ", ";
	query << statusId << ", ";
	query << "0,0,0);"; 

	// Fire the query
	return GenericRepository(_connection).FireCreate(query.str());
}

/**
 * @brief Start a new session within the system 
 * @param sessionId The session identifier
 */
void CodeDash::StartSession(int sessionId) 
{
	// Get the status id
	auto statusId = GetStatusId(Constants::STATUS_START);

	// Create the query
	auto query = stringstream();
	query << "UPDATE `session` SET ";
	query << "`start` = '" << NVLib::StringUtils::GetDateTimeString() << "', ";
	query << "`status_id` = " << statusId << " WHERE id = " << sessionId << ";";

	// Fire the query
	GenericRepository(_connection).FireUpdate(query.str());
}

/**
 * @brief Add the logic to pause a given session 
 * @param sessionId The identifier of the session
 */
void CodeDash::PauseSession(int sessionId) 
{
	// Get the status id
	auto statusId = GetStatusId(Constants::STATUS_STOP);

	// Create the query
	auto query = stringstream();
	query << "UPDATE `session` SET ";
	query << "`end` = '" << NVLib::StringUtils::GetDateTimeString() << "', ";
	query << "`status_id` = " << statusId << " WHERE id = " << sessionId << ";";

	// Fire the query
	GenericRepository(_connection).FireUpdate(query.str());
}

/**
 * @brief End a session
 * @param sessionId The identifier of the session
 */
void CodeDash::TerminateSession(int sessionId)
{
	// Get the status id
	auto statusId = GetStatusId(Constants::STATUS_END);

	// Create the query
	auto query = stringstream();
	query << "UPDATE `session` SET ";
	query << "`end` = '" << NVLib::StringUtils::GetDateTimeString() << "', ";
	query << "`status_id` = " << statusId << " WHERE id = " << sessionId << ";";

	// Fire the query
	GenericRepository(_connection).FireUpdate(query.str());
}

/**
 * @brief Set a session to the main session
 * @param sessionId The identifier of the session
 */
void CodeDash::FocusSession(int sessionId)
{
	// Create a repo
	auto repo = GenericRepository(_connection);
	
	// Set no session to have focus
	repo.FireUpdate("UPDATE `session` SET `focus` = 0;");

	// Set the focus session to now have the focus
	auto query = stringstream();
	query << "UPDATE `session` SET `focus` = 1 WHERE `id` = " << sessionId << ";";
	repo.FireUpdate(query.str());
}

//--------------------------------------------------
// Update
//--------------------------------------------------

/**
 * @brief Update the latest score in the current session
 * @param sessionId The identifier of the session
 * @param epoch The current epoch
 * @param score The score that we are updating
 */
void CodeDash::UpdateScore(int sessionId, int epoch, double score)
{
	// Create a repository
	auto repo = GenericRepository(_connection);

	// Set the focus session to now have the focus
	auto query = stringstream();
	query << "UPDATE `session` SET `epoch` = " << epoch << ", `best_score` = " << score << " WHERE `id` = " << sessionId << ";";

	// Fire the update
	repo.FireUpdate(query.str());

	// Set a query to update the score
	query = stringstream();
	query << "INSERT INTO `score`(`session_id`,`epoch`,`score`) VALUES (";
	query << sessionId << ", ";
	query << epoch << ", ";
	query << score << ")";

	// Fire the update
	repo.FireUpdate(query.str());
}

/**
 * @brief Set the current best score solution
 * @param sessionId The identifier of the session
 * @param code The code of the current best solution
 */
void CodeDash::SetBestCode(int sessionId, const string& code)
{
	// Set the focus session to now have the focus
	auto query = stringstream();
	query << "UPDATE `session` SET `best_solution` = '" << code << "' WHERE `id` = " << sessionId << ";";

	// Fire the update
	GenericRepository(_connection).FireUpdate(query.str());
}

/**
 * @brief Display an output message on the screen
 * @param sessionId The identifier of the session
 * @param message The message we are displaying
 */
void CodeDash::SetMessage(int sessionId, const string& message)
{
	// Set the focus session to now have the focus
	auto query = stringstream();
	query << "UPDATE `session` SET `message` = '" << message << "' WHERE `id` = " << sessionId << ";";

	// Fire the update
	GenericRepository(_connection).FireUpdate(query.str());
}

/**
 * @brief Raise an error for the system 
 * @param sessionId The session identifier
 * @param message The error message
 */
void CodeDash::RaiseError(int sessionId, const string& message) 
{
	auto statusId = GetStatusId(Constants::STATUS_FAIL);

	// Create the query
	auto query = stringstream();
	query << "UPDATE `session` SET ";
	query << "`message` = '" << message << "', ";
	query << "`status_id` = " << statusId << " WHERE id = " << sessionId << ";";

	// Fire the query
	GenericRepository(_connection).FireUpdate(query.str());
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Get the path to the training file
 * @param problemCode The associated problem code
 * @return string Returns a string
 */
string CodeDash::GetTrainingPath(const string& problemCode)
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `training_file` FROM `problem` WHERE `code` = '" << problemCode << "';";

	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Extract the solution
	auto result = string();
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsString();

	// Free data
	delete response;

	// Return the result
	return result;
}

/**
 * @brief Retrieve the algorithm identifier
 * @param code The code of the given algorithm 
 * @return int The identifier of the algorithm
 */
int CodeDash::GetAlgorithmId(const string& code) 
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `id` FROM `algorithm` WHERE `code` = '" << code << "';";

	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Extract the solution
	auto result = -1;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsInt();

	// Free data
	delete response;

	// Return the result
	return result;
}

/**
 * @brief Retrieve the problem identifier 
 * @param code The code of the given problem
 * @return int The identifier of the problem
 */
int CodeDash::GetProblemId(const string& code) 
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `id` FROM `problem` WHERE `code` = '" << code << "';";

	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Extract the solution
	auto result = -1;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsInt();

	// Free data
	delete response;

	// Return the result
	return result;
}

/**
 * @brief Retrieve the status identifier of the problem 
 * @param code The status code
 * @return int The identifier of the status
 */
int CodeDash::GetStatusId(const string& code) 
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `id` FROM `status` WHERE `code` = '" << code << "';";

	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Extract the solution
	auto result = -1;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsInt();

	// Free data
	delete response;

	// Return the result
	return result;
}

/**
 * @brief Retrieve meta data
 * @param key The key of the data we are retrieving 
 * @return string The value that is retrieved
 */
string CodeDash::GetMeta(const string& key) 
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `value` FROM `meta` WHERE `parameter` = '" << key << "';";

	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Extract the solution
	auto result = string();
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsString();

	// Free data
	delete response;

	// Return the result
	return result;
}