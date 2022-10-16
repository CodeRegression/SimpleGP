//--------------------------------------------------
// Unit Tests for class CodeDash
//
// @author: Wild Boar
//
// @date: 2022-10-03
//--------------------------------------------------

#include <gtest/gtest.h>

#include <SimpleGPLib/Globals.h>
#include <SimpleGPLib/CodeDash.h>
using namespace NVL_AI;

#include "../Helpers/TestRepo.h"

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Tests the session handling
 */
TEST(CodeDash_Test, create_session)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto session = helperRepo.GetSessionDetails(sessionId);

	// Confirm
	ASSERT_EQ(session->GetProblem(), "Top Left Finder");
	ASSERT_EQ(session->GetAlgorithm(), "SimpleGP");
	ASSERT_EQ(session->GetStatus(), "CREATED");
	ASSERT_FALSE(session->GetFocus());

	// Teardown
	delete session;
}

/**
 * @brief Confirm the various setting of session statuses
 */
TEST(CodeDash_Test, session_statuses) 
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto status_1 = helperRepo.GetSessionStatus(sessionId);
	codeData.StartSession(sessionId);
	auto status_2 = helperRepo.GetSessionStatus(sessionId);
	codeData.PauseSession(sessionId);
	auto status_3 = helperRepo.GetSessionStatus(sessionId);
	codeData.TerminateSession(sessionId);
	auto status_4 = helperRepo.GetSessionStatus(sessionId);
	auto message_1 = helperRepo.GetSessionMessage(sessionId);
	codeData.RaiseError(sessionId, "Error Raised");
	auto status_5 = helperRepo.GetSessionStatus(sessionId);
	auto message_2 = helperRepo.GetSessionMessage(sessionId);

	// Confirm
	ASSERT_EQ(status_1, "CREATED");
	ASSERT_EQ(status_2, "STARTED");
	ASSERT_EQ(status_3, "PAUSED");
	ASSERT_EQ(status_4, "FINISHED");
	ASSERT_EQ(status_5, "FAILED");
	ASSERT_EQ(message_1, string());
	ASSERT_EQ(message_2, "Error Raised");
}

/**
 * @brief Confirm that we have the capability to give a session focus
 */
TEST(CodeDash_Test, focus_session) 
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId_1 = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto sessionId_2 = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto f_1 = helperRepo.GetFocusSessionId();
	codeData.FocusSession(sessionId_1);
	auto f_2 = helperRepo.GetFocusSessionId();
	codeData.FocusSession(sessionId_2);
	auto f_3 = helperRepo.GetFocusSessionId();

	// Confirm
	ASSERT_EQ(f_1, -1);
	ASSERT_EQ(f_2, sessionId_1);
	ASSERT_EQ(f_3, sessionId_2);
}

/**
 * @brief Update the current score
 */
TEST(CodeDash_Test, update_score)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto before_score = helperRepo.GetSessionScore(sessionId);
	auto before_epoch = helperRepo.GetSessionEpoch(sessionId);
	codeData.UpdateScore(sessionId, 1, 25);
	auto after_score = helperRepo.GetSessionScore(sessionId);
	auto after_epoch = helperRepo.GetSessionEpoch(sessionId);

	// Confirm
	ASSERT_EQ(before_score, 0);
	ASSERT_EQ(before_epoch, 0);
	ASSERT_EQ(after_score, 25);
	ASSERT_EQ(after_epoch, 1);
}

/**
 * @brief Update the best code flag
 */
TEST(CodeDash_Test, set_best_code)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto before = helperRepo.GetSessionCode(sessionId);
	codeData.SetBestCode(sessionId, "best solution");
	auto after = helperRepo.GetSessionCode(sessionId);

	// Confirm
	ASSERT_EQ(before, string());
	ASSERT_EQ(after, "best solution");
}

/**
 * @brief Set a message against the session
 */
TEST(CodeDash_Test, set_message)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto sessionId = codeData.CreateSession(Constants::ALGORITHM_CODE, Constants::PROBLEM_TOP_LEFT);
	auto before = helperRepo.GetSessionMessage(sessionId);
	codeData.SetMessage(sessionId, "hello world");
	auto after = helperRepo.GetSessionMessage(sessionId);

	// Confirm
	ASSERT_EQ(before, string());
	ASSERT_EQ(after, "hello world");
}

/**
 * @brief Retrieve the current training path
 */
TEST(CodeDash_Test, get_training_path)
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto training = codeData.GetTrainingPath(Constants::PROBLEM_TOP_LEFT);

	// Confirm
	ASSERT_EQ(training, "training/tlp_0000.txt");
}

/**
 * @brief Confirm that we can retrieve meta
 */
TEST(CodeDash_Test, get_meta) 
{
	// Setup: Connection
	auto connection = DBConnection("localhost", "trevor", "808Rkief$", "code_dash_test", 3306);

	// Setup: Create a test repository
	auto helperRepo = NVL_Test::TestRepo(&connection);

	// Setup: Setup the test database state
	helperRepo.Clear();

	// Setup: Create the working repository
	auto codeData = CodeDash(&connection);

	// Execute
	auto folder = codeData.GetMeta(Constants::META_SITE_LOCATION);

	// Confirm
	ASSERT_EQ(folder, "/home/trevor/Work/Research/Trevor/Code.Gen/Source/Code.Dash/build/Code.Dash");
}
