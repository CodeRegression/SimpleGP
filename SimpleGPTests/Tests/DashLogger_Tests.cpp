//--------------------------------------------------
// Unit Tests for class DashLogger
//
// @author: Wild Boar
//
// @date: 2022-10-06
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/DashLogger.h>
#include <SimpleGPLib/Globals.h>
#include <SimpleGPLib/CodeDash.h>
using namespace NVL_AI;

#include "../Helpers/TestRepo.h"

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the various messages
 */
TEST(DashLogger_Test, confirm_messaging)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository and the logger
	auto codeData = CodeDash(&connection);
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto logger = DashLogger(sessionId, &codeData);

	// Execute
	logger.Message("test");
	auto message_1 = helperRepo.GetSessionMessage(sessionId);

	// Confirm
	ASSERT_EQ(message_1, "test");
}

/**
 * @brief Confirm the updating of score
 */
TEST(DashLogger_Test, confirm_score_update)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository and the logger
	auto codeData = CodeDash(&connection);
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto logger = DashLogger(sessionId, &codeData);

	// Execute
	logger.UpdateScore(1, 100);
	logger.ShowResult("result");

	auto score = helperRepo.GetSessionScore(sessionId);
	auto epoch = helperRepo.GetSessionEpoch(sessionId);
	auto code = helperRepo.GetSessionCode(sessionId);

	// Confirm
	ASSERT_EQ(score, 100);
	ASSERT_EQ(epoch, 1);
	ASSERT_EQ(code, "result");
}

/**
 * @brief Confirm start stop functionality
 */
TEST(DashLogger_Test, confirm_start_stop)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository and the logger
	auto codeData = CodeDash(&connection);
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto logger = DashLogger(sessionId, &codeData);

	// Execute
	logger.Start();
	auto status_1 = helperRepo.GetSessionStatus(sessionId);
	logger.Stop();
	auto status_2 = helperRepo.GetSessionStatus(sessionId);

	// Confirm
	ASSERT_EQ(status_1, "STARTED");
	ASSERT_EQ(status_2, "FINISHED");
}

/**
 * @brief Confirm raising an error
 */
TEST(DashLogger_Test, confirm_error)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository and the logger
	auto codeData = CodeDash(&connection);
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto logger = DashLogger(sessionId, &codeData);

	// Execute
	logger.RaiseError("Error");

	auto message = helperRepo.GetSessionMessage(sessionId);
	auto status = helperRepo.GetSessionStatus(sessionId);

	// Confirm
	ASSERT_EQ(message, "Error");
	ASSERT_EQ(status, "FAILED");
}
