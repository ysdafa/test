# Install script for directory: /home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/noa-common

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
    SET(CMAKE_INSTALL_CONFIG_NAME "")
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
  FOREACH(file
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so.0.1"
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so.0"
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/apps/com.samsung.noa/lib/libnoa-common.so.0.1;/usr/apps/com.samsung.noa/lib/libnoa-common.so.0;/usr/apps/com.samsung.noa/lib/libnoa-common.so")
FILE(INSTALL DESTINATION "/usr/apps/com.samsung.noa/lib" TYPE SHARED_LIBRARY FILES
    "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/noa-common/libnoa-common.so.0.1"
    "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/noa-common/libnoa-common.so.0"
    "/home/abuild/rpmbuild/BUILD/com.samsung.noa-0.0.1/noa-common/libnoa-common.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so.0.1"
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so.0"
      "$ENV{DESTDIR}/usr/apps/com.samsung.noa/lib/libnoa-common.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

