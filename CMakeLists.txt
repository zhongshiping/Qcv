cmake_minimum_required(VERSION 3.5.0)
project(Qcv)

# Parallel building
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
endif()

# Compiler Debug info in Release mode
if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

# install
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${Qcv_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${Qcv_BINARY_DIR}/bin/Release)
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
set(INSTALL_DIR ${PROJECT_BINARY_DIR}/install)

# cmake
include(cmake/msvs.cmake) # visual studio
add_definitions("/wd4819 /wd4251 /wd4996")

# OpenMP
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#fin opencv package
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Find the Qt5Widget module (if you need other packages from Qt, it is all the same. Example with Qt5Network: add 'find_package(Qt5Network)'
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Concurrent REQUIRED)

set(QT_LIBS Qt5::Widgets Qt5::Sql Qt5::Core Qt5::Concurrent)

add_subdirectory(app)
add_subdirectory(core)
add_subdirectory(lib)