# CMakeList.txt : CMake project for File_archiver, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (File_archiver "File_archiver.cpp" "File_archiver.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET File_archiver PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
