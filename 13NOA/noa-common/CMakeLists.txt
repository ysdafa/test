SET(LIBRARY_NAME ${LIB_NAME_COM})
#lib
SET(LIB_SRCS
        src/noa_fwk_util.c
        src/noa_fwk_widget.c
        src/noa_fwk_view.c
        src/noa_fwk_sound.c
        src/noa_fwk_alarmmgr.c
        src/noa_fwk_icu.c
        src/noa_fwk_effect.c
)

#set define
SET(ALARMRING_PKGNAME ${PKGNAME_RING})

# dependency
INCLUDE(FindPkgConfig)
pkg_check_modules(noa_com_pkgs REQUIRED
                       elementary appcore-efl
                       gobject-2.0 gmodule-2.0 dlog
                       utilX vconf
					   icu-i18n
                       mm-sound mm-player
                       ui-gadget-1 bundle aul
                       alarm-service alarm-engine
                       ecore-imf ecore-x ecore ecore-file ecore-input
)

# CFlags
FOREACH(flag ${noa_com_pkgs_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)
#SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -finstrument-functions")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC ${EXTRA_CFLAGS}")
ADD_DEFINITIONS("-fpie")
#ADD_DEFINITIONS("-DTARGET")
ADD_DEFINITIONS("-DDEBUG")
ADD_DEFINITIONS("-DPACKAGE=\"${PACKAGE}\"")
ADD_DEFINITIONS("-DEDJDIR=\"${EDJDIR}\"")
ADD_DEFINITIONS("-DALARMRING_PKGNAME=\"${PKGNAME_RING}\"")

FIND_PROGRAM(UNAME NAMES uname)
EXEC_PROGRAM("${UNAME}" ARGS "-m" OUTPUT_VARIABLE "ARCH")
IF("${ARCH}" STREQUAL "arm")
    ADD_DEFINITIONS("-DTARGET")
    MESSAGE("add -DTARGET")
ENDIF("${ARCH}" STREQUAL "arm")

#SET(LIB_SO -L/usr/lib -licui18n -licuuc -licudata -lm)
#lib
ADD_LIBRARY(${LIBRARY_NAME} SHARED ${LIB_SRCS})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES SOVERSION ${SO_VERSION_MAJOR})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES VERSION ${SO_VERSION})
TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${noa_com_pkgs_LDFLAGS})
#TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${LIB_SO})

#lib
INSTALL(TARGETS ${LIBRARY_NAME} DESTINATION ${LIBDIR})
