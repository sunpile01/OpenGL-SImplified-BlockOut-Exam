# Install script for directory: C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tclap" TYPE FILE FILES
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/Arg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ArgContainer.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ArgException.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ArgGroup.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ArgTraits.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/CmdLine.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/CmdLineInterface.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/CmdLineOutput.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/Constraint.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/DeferDelete.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/DocBookOutput.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/HelpVisitor.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/IgnoreRestVisitor.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/MultiArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/MultiSwitchArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/OptionalUnlabeledTracker.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/StandardTraits.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/StdOutput.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/SwitchArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/UnlabeledMultiArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/UnlabeledValueArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ValueArg.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/ValuesConstraint.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/VersionVisitor.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/Visitor.h"
    "C:/Users/aleks/github-portfolio/Group_26/External/tclap/include/tclap/sstream.h"
    )
endif()

