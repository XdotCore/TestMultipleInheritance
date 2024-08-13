cmake_minimum_required (VERSION 3.8)

set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
cmake_policy(SET CMP0141 NEW)

project ("TestMultipleInheritance")

add_subdirectory ("TestMultipleInheritance")
