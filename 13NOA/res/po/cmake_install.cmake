# Install script for directory: /home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/opt/apps/com.samsung.daemon")
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
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/de_DE/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/de_DE/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/de_DE.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/el_GR/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/el_GR/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/el_GR.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/en/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/en/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/en.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/es_ES/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/es_ES/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/es_ES.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/fr_FR/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/fr_FR/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/fr_FR.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/it_IT/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/it_IT/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/it_IT.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/ja_JP/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/ja_JP/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/ja_JP.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/ko_KR/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/ko_KR/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/ko_KR.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/nl_NL/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/nl_NL/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/nl_NL.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/pt_PT/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/pt_PT/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/pt_PT.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/ru_RU/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/ru_RU/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/ru_RU.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/tr_TR/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/tr_TR/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/tr_TR.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/zh_CN/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/zh_CN/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/zh_CN.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/zh_HK/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/zh_HK/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/zh_HK.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/opt/apps/com.samsung.daemon/res/locale/zh_TW/LC_MESSAGES/daemon.mo")
FILE(INSTALL DESTINATION "/opt/apps/com.samsung.daemon/res/locale/zh_TW/LC_MESSAGES" TYPE FILE RENAME "daemon.mo" FILES "/home/abuild/rpmbuild/BUILD/com.samsung.daemon-0.1.0/res/po/zh_TW.mo")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

