//--------------------------------------------------
// Implementation of class TestRepo
//
// @author: Wild Boar
//
// @date: 2022-10-04
//--------------------------------------------------

#include "TestRepo.h"
using namespace NVL_Test;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param connection Initialize variable <connection>
 */
TestRepo::TestRepo(DBConnection * connection)
{
	_connection = connection;
}

//--------------------------------------------------
// Clear
//--------------------------------------------------

/**
 * @brief Clear the database
 */
void TestRepo::Clear()
{
	// Create a repo
	auto repo = GenericRepository(_connection);

	// Clear the session table
	repo.FireUpdate("DELETE FROM `score`;");
	repo.FireUpdate("DELETE FROM `session`;");
}

//--------------------------------------------------
// Session
//--------------------------------------------------

/**
 * @brief Retrieve the associated session details 
 * @param sessionId The identifier of the session
 * @return Session The session details
 */
NVL_AI::Session * TestRepo::GetSessionDetails(int sessionId) 
{
	// Build the query
	auto query = stringstream();
	query << "SELECT `problem`.`name` as `problem`, `algorithm`.`name` as `algorithm`,"; 
	query << "`status`.`name` as `status`, `session`.`focus` as `focus`";
	query << "FROM `session`";
	query << "INNER JOIN `problem` ON `session`.`problem_id` = `problem`.`id`";
	query << "INNER JOIN `algorithm` ON `session`.`algorithm_id` = `algorithm`.`id`";
	query << "INNER JOIN `status` ON `session`.`status_id` = `status`.`id`";
	query << "WHERE `session`.`id` = " << sessionId << ";"; 
	
	// Fire the query
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Create the result
	NVL_AI::Session * result = nullptr;

	if (response->GetRowCount() == 1) 
	{
		auto problem = response->GetRow(0)->Get("problem").AsString();
		auto algorithm = response->GetRow(0)->Get("algorithm").AsString();
		auto status = response->GetRow(0)->Get("status").AsString();
		auto focus = response->GetRow(0)->Get("focus").AsInt() == 1;
		result = new NVL_AI::Session(algorithm, problem, status, focus);
	}

	// Free the memory
	delete response;

	return result;
}	

/**
 * @brief Retrieve the session status 
 * @param sessionId The identifier of the session
 * @return string The session status as a string
 */
string TestRepo::GetSessionStatus(int sessionId) 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `status`.`name` as `status` FROM `session` INNER JOIN `status` ";
	query << "ON `session`.`status_id` = `status`.`id` WHERE `session`.`id` = " << sessionId << ";";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = string("no result");
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsString();

	// Free response
	delete response;

	// return the result
	return result;
}	

/**
 * @brief Retrieve the session message 
 * @param sessionId The identifier of the session
 * @return string The message associated with the session
 */
string TestRepo::GetSessionMessage(int sessionId) 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `message` FROM `session` WHERE `session`.`id` = " << sessionId << ";";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = string("empty");
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsString();

	// Free response
	delete response;

	// return the result
	return result;
}

/**
 * @brief Get the identifier of the focus session 
 * @return int The identifier of the focus session
 */
int TestRepo::GetFocusSessionId() 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `id` FROM `session` WHERE `session`.`focus` = 1;";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = -1;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsInt();
	else if (response->GetRowCount() > 1) throw runtime_error("Cannot have multiple sessions with focus!");

	// Free response
	delete response;

	// return the result
	return result;
}

/**
 * @brief Retrieve the given session score 
 * @param sessionId The identifier associated with the session
 * @return double The given session score
 */
double TestRepo::GetSessionScore(int sessionId) 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `best_score` FROM `session` WHERE `session`.`id` = " << sessionId << ";";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = 0;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsDouble();

	// Free response
	delete response;

	// return the result
	return result;
}

/**
 * @brief Retrieve the session epoch 
 * @param sessionId The identifier associated with the session
 * @return int The epoch number associated with the session
 */
int TestRepo::GetSessionEpoch(int sessionId) 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `epoch` FROM `session` WHERE `session`.`id` = " << sessionId << ";";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = 0;
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsInt();

	// Free response
	delete response;

	// return the result
	return result;

}

/**
 * @brief Retrieve the best source code solution associated with the session 
 * @param sessionId The given session identifier
 * @return string The best source code solution
 */
string TestRepo::GetSessionCode(int sessionId) 
{
	// Build the status
	auto query = stringstream();
	query << "SELECT `best_solution` FROM `session` WHERE `session`.`id` = " << sessionId << ";";

	// Fire the query and get the response
	auto response = GenericRepository(_connection).FireQuery(query.str());

	// Get the bacon
	auto result = string("empty");
	if (response->GetRowCount() == 1) result = response->GetRow(0)->Get(0).AsString();

	// Free response
	delete response;

	// return the result
	return result;
}