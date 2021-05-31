cmake_minimum_required(VERSION 3.12.4)


set(ReadEncoderVERSION 0.1.0)
if(ReadEncoderVERSION MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)")
	set(ReadEncoderVERSION_MAJOR "${CMAKE_MATCH_1}")
	set(ReadEncoderVERSION_MINOR "${CMAKE_MATCH_2}")
	set(ReadEncoderVERSION_PATCH "${CMAKE_MATCH_3}")
else()
	message(FATAL_ERROR "Failed to parse ReadEncoderVERSION='${ReadEncoderVERSION}'")
endif()
project(ReadEncoder VERSION ${ReadEncoderVERSION})


IF( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.1.0" )
	MESSAGE( STATUS "Not tested on older gcc than 11.1.0" )
ENDIF()


# specify the C++ standard and compilation options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O3 -m64 -march=native" )
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-DNDEBUG)
endif()
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(Doxygen REQUIRED dot)

# GLOB allows for wildcard additions
file(GLOB SOURCES "src/*.c")

# Find modbus library
find_path(Modbus_INCLUDE_DIR modbus/modbus.h
	HINTS
	/opt/libmodbus/include/
)
find_library(Modbus_LIBRARIES NAMES modbus
	HINTS
	/opt/libmodbus/lib/
)
include_directories(
	${Modbus_INCLUDE_DIR}/modbus
)

add_executable(ReadEncoder ${SOURCES})
target_link_libraries(ReadEncoder ${Modbus_LIBRARIES})

install(TARGETS ReadEncoder DESTINATION bin)

# Allow packaging with "make package"
if(BUILD_APT_PACKAGES)
  add_subdirectory(package)
endif()
