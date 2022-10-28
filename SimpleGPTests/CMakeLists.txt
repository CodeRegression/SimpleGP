#--------------------------------------------------------
# CMake for generating SimpleGPLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2022-09-26
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../"  "${LIBRARY_BASE}/NVLib" "${LIBRARY_BASE}/GeneticLib" "${LIBRARY_BASE}/DBLib")

# Add the UnitTestLib library to the folder
add_library(UnitTestLib STATIC IMPORTED)
set_target_properties(UnitTestLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/UnitTestLib/build/UnitTestLib/libUnitTestLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/UnitTestLib"
)

# Create the executable
add_executable (SimpleGPTests
	Tests/ScoreUtils_Tests.cpp
    Tests/BooleanStatement_Tests.cpp
    Tests/BreadthIterator_Tests.cpp
    Tests/Breed_Tests.cpp
    Tests/CandidateSelector_Tests.cpp
    Tests/CodeTree_Tests.cpp
    Tests/CodeTreeFactory_Tests.cpp
    Tests/DecisionNode_Tests.cpp
    Tests/Memory_Tests.cpp
    Tests/Mutator_Tests.cpp
)

# Add link libraries
target_link_libraries(SimpleGPTests SimpleGPLib NVLib GeneticLib ${OpenCV_LIBS} ${LIBMYSQLCLIENT_LIBRARIES} UnitTestLib GTest::Main uuid)

# Find the associated unit tests
gtest_discover_tests(SimpleGPTests)