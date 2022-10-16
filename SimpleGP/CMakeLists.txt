#--------------------------------------------------------
# CMake for generating the main executable
#
# @author: Wild Boar
#
# Date Created: 2022-09-26
#--------------------------------------------------------

# Setup the includes
include_directories("../" "${LIBRARY_BASE}/NVLib" "${LIBRARY_BASE}/GeneticLib" "${LIBRARY_BASE}/DBLib" )

# Create the executable
add_executable(SimpleGP
    Engine.cpp
    Source.cpp
)

# Add link libraries                               
target_link_libraries(SimpleGP SimpleGPLib NVLib GeneticLib DBLib ${OpenCV_LIBS} ${LIBMYSQLCLIENT_LIBRARIES} uuid)

# Copy Resources across
add_custom_target(resource_copy ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/SimpleGP 
    DEPENDS ${MY_TARGET}
)