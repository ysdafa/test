# Install script for directory: /home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/apps/com.samsung.noa")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/apps/com.samsung.noa/bin/noa")
FILE(INSTALL DESTINATION "/usr/apps/com.samsung.noa/bin" TYPE EXECUTABLE FILES "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/src/noa")
  IF(EXISTS "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/apps/com.samsung.noa/bin/noa")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/apps/com.samsung.noa/res/images")
FILE(INSTALL DESTINATION "/usr/apps/com.samsung.noa/res" TYPE DIRECTORY FILES "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/res/images")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/applications/com.samsung.noa.desktop")
FILE(INSTALL DESTINATION "/usr/share/applications" TYPE FILE FILES "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/com.samsung.noa.desktop")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/packages/com.samsung.noa.xml")
FILE(INSTALL DESTINATION "/usr/share/packages" TYPE FILE FILES "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/com.samsung.noa.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/default/small/com.samsung.noa.png")
FILE(INSTALL DESTINATION "/usr/share/icons/default/small" TYPE FILE FILES "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/com.samsung.noa.png")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/apps/com.samsung.noa/data/")
FILE(INSTALL DESTINATION "/usr/apps/com.samsung.noa/data" TYPE DIRECTORY FILES "")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

