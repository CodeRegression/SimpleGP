//--------------------------------------------------
// Implementation of class CodeDash
//
// @author: Wild Boar
//
// @date: 2022-10-24
//--------------------------------------------------

#include "CodeDash.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param server The server that we are connecting to
 * @param port The port that we are connecting to
 */
CodeDash::CodeDash(const string& server, const string& port) : _server(server), _port(port)
{
	// Extra connection can come here
}

//--------------------------------------------------
// Session
//--------------------------------------------------

/**
 * @brief Logic to create a new session
 * @param algorithmCode The algorithm that is being run
 * @param problemCode The problem that the algorithm is being asked to solve
 * @param machineName The name of the machine that the session is being run from
 * @return int Returns a int
 */
int CodeDash::CreateSession(const string& algorithmCode, const string& problemCode, const string& machineName)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "CREATE";
	parameters["algorithm"] = algorithmCode;
	parameters["problem"] = problemCode;
	parameters["machine"] = machineName;
	
	auto response = FireRequest(parameters);

	if (response.Error != string()) throw runtime_error(response.Error);

	return response.SessionId;
}

/**
 * @brief Logic to start a session
 * @param sessionId The identifier of the session that we are running
 */
void CodeDash::StartSession(int sessionId)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "START";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

/**
 * @brief Logic to pause a session
 * @param sessionId The identifier of the session that we are running
 */
void CodeDash::PauseSession(int sessionId)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "PAUSE";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

/**
 * @brief Logic to terminate a session
 * @param sessionId The identifier of the session that we are running
 */
void CodeDash::EndSession(int sessionId)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "END";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

/**
 * @brief Logic to fail a session
 * @param sessionId The identifier of the session that we are running
 * @param message A description of why the session failed
 */
void CodeDash::FailSession(int sessionId, const string& message)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "FAIL";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	parameters["message"] = message;
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

//--------------------------------------------------
// Update
//--------------------------------------------------

/**
 * @brief Update the score in the session
 * @param sessionId The identifier of the session that we are running
 * @param epoch The current epoch that we are updating
 * @param score The actual score that we are updating
 */
void CodeDash::UpdateScore(int sessionId, int epoch, double score)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "SCORE";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	parameters["epoch"] = NVLib::StringUtils::Int2String(epoch);
	parameters["score"] = NVLib::StringUtils::Double2String(score);
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

/**
 * @brief Update best solution in the session
 * @param sessionId The identifier of the session that we are running
 * @param solution The best solution that we are setting
 */
void CodeDash::UpdateSolution(int sessionId, const string& solution)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "SOLUTION";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	parameters["solution"] = Escape(solution);
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

/**
 * @brief Update the message associated with the session
 * @param sessionId The identifier of the session that we are running
 * @param message The message that we are setting
 */
void CodeDash::SetMessage(int sessionId, const string& message)
{
	auto parameters = unordered_map<string, string>();
	parameters["operation"] = "MESSAGE";
	parameters["session"] = NVLib::StringUtils::Int2String(sessionId);
	parameters["message"] = message;
	auto response = FireRequest(parameters);
	if (response.Error != string()) throw runtime_error(response.Error);
}

//--------------------------------------------------
// Communication Helper
//--------------------------------------------------

/**
 * @brief Fires off requests and gets responses 
 * @param parameters The parameters that we are passing off
 * @return Response The response that we received
 */
CodeDash::Response CodeDash::FireRequest(const unordered_map<string, string>& parameters) 
{
	// Setup the socket
	string ip = Socket::ipFromHostName(_server); 
    string port = _port; 
    Socket *sock = new Socket(AF_INET, SOCK_STREAM, 0);  
    sock->connect(ip, port); 

	// Build up the parameter string
	auto paramString = BuildParamString(parameters);

	// Build the request
    auto request = stringstream();
    request << "POST /CodeDash/?current_page=dash_comms HTTP/1.1\r\n";
    request << "Host: " << _server << "\r\n";
    request << "Content-Type: application/x-www-form-urlencoded\r\n";
    request << "Content-Length: " << paramString.length() << "\r\n\r\n";
    request << paramString << "\r\n";

	// Fire off the request
    sock->socket_write(request.str());
    int seconds = 10;
    vector<Socket> reads(1);
    reads[0] = *sock;

	// Get the response
    if(sock->select(&reads, NULL, NULL, seconds) < 1)
    {
        return CodeDash::Response(-1, "No reply received - something went wrong");
    }
    else
    {
        string buffer;
        sock->socket_read(buffer, 1024);
        //cout << buffer << endl;
		return Parse(buffer);
    }
}

/**
 * @brief Build the associated result string 
 * @param parameters The parameter string
 * @return string The string that we were building
 */
string CodeDash::BuildParamString(const unordered_map<string, string>& parameters) 
{
	auto result = stringstream(); auto first = true;

	for (auto& pair : parameters) 
	{
		if (first) first = false; 
		else result << "&";
		result << pair.first << "=" << pair.second;
	}

	return result.str();
}

/**
 * @brief Perform the parsing of the application
 * @param value The value that we are parsing 
 * @return CodeDash::Response The response that we got
 */
CodeDash::Response CodeDash::Parse(const string& value) 
{
	// Create a reader
	auto reader = stringstream(value);

	// Create a line
	auto line = string();

	// Create place holders for variables
	auto sessionId = 0; auto message = string(); int found = 0;

	while(true) 
	{
		if (reader.eof() || found >= 2) break;

		getline(reader, line);

		if (NVLib::StringUtils::StartsWith(line, "<session_id>")) 
		{
			found++;
			auto content = GetTagContent(line);
			if (content != string()) sessionId = NVLib::StringUtils::String2Int(content); 
		}
		else if (NVLib::StringUtils::StartsWith(line, "<error>")) 
		{
			found++;
			message = GetTagContent(line);
		}
	}

	// Return the result
	return CodeDash::Response(sessionId, message);
}

/**
 * @brief Add the logic to get the tag content
 * @param tag The tag that we are getting the content for 
 * @return string The content of the tag
 */
string CodeDash::GetTagContent(const string& tag) 
{
	// Create working variables
	auto start = false; auto result = stringstream();

	// Loop thru the characters
	for (auto & character : tag) 
	{
		if (!start) 
		{
			if (character == '>') start = true;
		}
		else 
		{
			if (character == '<') break;
			result << character;
		}
	}

	// Return the result
	return result.str();
}

/**
 * @brief Add the logic to escape a string
 * @param value The value that we are escaping 
 * @return string The string value
 */
string CodeDash::Escape(const string& value) 
{
	auto result = stringstream();

	for (auto & character : value) 
	{
		if (character == '&') result << "%26";
		else if (character == ';') result << "%3B";
		else if (character == '<') result << "%3C";
		else if (character == '>') result << "%3E";
		else result << character;
	}

	return result.str();
}
