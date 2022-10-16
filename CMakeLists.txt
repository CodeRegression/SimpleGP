#--------------------------------------------------------
# Top-Level: SimpleGP
#
# @author: Wild Boar
#
# @Date Created: 2022-09-26
#--------------------------------------------------------

# Create the main application
cmake_minimum_required(VERSION 3.0.0)
project(SimpleGP VERSION 0.1.0)

# Enable Testing
enable_testing()

# Set the correct version of C++
set(CMAKE_CXX_STANDARD 17)

# Setup base directory
set(LIBRARY_BASE $ENV{HOME}/Libraries)

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Add the GeneticLib to the folder
add_library(GeneticLib STATIC IMPORTED)
set_target_properties(GeneticLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/GeneticLib/build/GeneticLib/libGeneticLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/GeneticLib"
)

# Add the DBLib library to the project
add_library(DBLib STATIC IMPORTED)
set_target_properties(DBLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/DBLib/build/DBLib/libDBLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/DBLib"
)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Search for modules
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)

# Find all the mysql components
foreach(FLAG ${LIBMYSQLCLIENT_CFLAGS_OTHER})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()

# Add the available subfolders
add_subdirectory(SimpleGPLib)
add_subdirectory(SimpleGPTests)
add_subdirectory(SimpleGP)