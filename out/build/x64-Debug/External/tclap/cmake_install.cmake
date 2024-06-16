# Install script for directory: C:/Users/aleks/github-portfolio/Group_26/External/tclap

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tclap" TYPE FILE FILES "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/tclap/TCLAPConfig.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "doc" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc/html")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc" TYPE DIRECTORY FILES "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/docs/html")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "doc" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc/index.html;C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc/manual.html;C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc/style.css")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/aleks/github-portfolio/Group_26/out/install/x64-Debug/doc" TYPE FILE FILES
    "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/docs/index.html"
    "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/docs/manual.html"
    "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/docs/style.css"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/tclap.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP/TCLAPConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP/TCLAPConfig.cmake"
         "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/CMakeFiles/Export/e8a41b2a67c949aae103091eff34f64d/TCLAPConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP/TCLAPConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP/TCLAPConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP" TYPE FILE FILES "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/CMakeFiles/Export/e8a41b2a67c949aae103091eff34f64d/TCLAPConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TCLAP" TYPE FILE FILES "C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/TCLAPConfig-version.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/docs/cmake_install.cmake")
  include("C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/examples/cmake_install.cmake")
  include("C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/tests/cmake_install.cmake")
  include("C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/unittests/cmake_install.cmake")
  include("C:/Users/aleks/github-portfolio/Group_26/out/build/x64-Debug/External/tclap/include/tclap/cmake_install.cmake")

endif()

