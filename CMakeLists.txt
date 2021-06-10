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


IF( CMAKE_C_COMPILER_VERSION VERSION_LESS "11.1.0" )
    MESSAGE( STATUS "Not tested on older gcc than 11.1.0" )
ENDIF()


# specify the C standard and compilation options
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "-O3 -m64 -march=native" )
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-DNDEBUG)
endif()
add_compile_options(-Wall -Wextra -Wpedantic -Wformat=2 -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -Wjump-misses-init -Wlogical-op) # https://github.com/mcinglis/c-style#always-develop-and-compile-with-all-warnings-and-more-on


# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" OFF)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    if(BUILD_DOC)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    endif(BUILD_DOC)
    unset(BUILD_DOC CACHE)
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


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

# Find wcslib
# find_path(wcslib_INCLUDE_DIR wcslib/*.h
    # HINTS
    # /opt/wcslib/include/
# )
# find_library(wcslib_LIBRARIES NAMES wcs
    # HINTS
    # /opt/wcslib/lib/
# )
# include_directories(
    # ${Modbus_INCLUDE_DIR}/modbus/ ${wcslib_INCLUDE_DIR}/wcslib/
# )


add_executable(ReadEncoder ${SOURCES})
# target_link_libraries(ReadEncoder ${Modbus_LIBRARIES} ${wcslib_LIBRARIES})
target_link_libraries(ReadEncoder ${Modbus_LIBRARIES})

install(TARGETS ReadEncoder DESTINATION bin)

# Allow packaging with "make package"
if(BUILD_APT_PACKAGES)
  add_subdirectory(package)
endif()