#--------------------------------------------------------
# CMake for generating the SimpleGPLib
#
# @author: Wild Boar
#
# Date Created: 2022-09-26
#--------------------------------------------------------

# Setup the includes for the libraries
include_directories("../" "${LIBRARY_BASE}/NVLib" "${LIBRARY_BASE}/GeneticLib" "${LIBRARY_BASE}/DBLib" )

# Create Library
add_library (SimpleGPLib STATIC
	ArgUtils.cpp
	Candidate.cpp
	CandidateFactory.cpp
	Mutation.cpp
	ScoreFinder.cpp
	ScoreUtils.cpp
	CodeDash.cpp
	DashLogger.cpp
	Socket.cpp
)