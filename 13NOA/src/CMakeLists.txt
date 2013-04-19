INCLUDE(FindPkgConfig)

SET(RSRC_DIR ./res)
SET(EDC_DIR ./edc)
SET(IMG_DIR ./images)
SET(LIB_DIR ./lib)
# c file
SET(SRCS
	noa.c
	noamain.c
	gengrid_gridtext.c
	gengrid_default.c
	gengrid_groupindex.c
)

IF("${CMAKE_BUILD_TYPE}" STREQUAL "")
	SET(CMAKE_BUILD_TYPE "Debug")
ENDIF("${CMAKE_BUILD_TYPE}" STREQUAL "")
MESSAGE("Build type: ${CMAKE_BUILD_TYPE}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

pkg_check_modules(pkgs REQUIRED
					appcore-common
					appsvc
					appcore-efl
					elementary
					dlog
					ecore-input
					ecore-imf
					ecore-x
					ecore
					eina
					bundle
					evas
					edje
					ecore-file
					capi-appfw-application
					capi-appfw-app-manager 
					capi-base-common	
					ui-gadget-1
				   )
FOREACH(flag ${pkgs_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror-implicit-function-declaration -Wl,--unresolved-symbols=ignore-in-shared-libs -Wl,-zdefs")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_C_FLAGS_RELEASE "-O2")

FIND_PROGRAM(UNAME NAMES uname)
EXEC_PROGRAM("${UNAME}" ARGS "-m" OUTPUT_VARIABLE "ARCH")
IF("${ARCH}" STREQUAL "arm")
	ADD_DEFINITIONS("-DTARGET")
	MESSAGE("add -DTARGET")
ENDIF("${ARCH}" STREQUAL "arm")

ADD_DEFINITIONS("-DPREFIX=\"${PREFIX}\"")
ADD_DEFINITIONS("-DBINDIR=\"${BINDIR}\"")
ADD_DEFINITIONS("-DLIBDIR=\"${LIBDIR}\"")
ADD_DEFINITIONS("-DINCLUDEDIR=\"${INCLUDEDIR}\"")

ADD_DEFINITIONS("-DVENDOR=\"${VENDOR}\"")
ADD_DEFINITIONS("-DPACKAGE=\"${PACKAGE}\"")
ADD_DEFINITIONS("-DPACKAGE_NAME=\"${PKGNAME}\"")

ADD_DEFINITIONS("-DRESDIR=\"${RESDIR}\"")
ADD_DEFINITIONS("-DDATADIR=\"${DATADIR}\"")
ADD_DEFINITIONS("-DDATADIR=\"${DBDIR}\"")
ADD_DEFINITIONS("-DLOCALEDIR=\"${LOCALEDIR}\"")
ADD_DEFINITIONS("-DICONDIR=\"${ICONDIR}\"")
ADD_DEFINITIONS("-DEDJDIR=\"${EDJDIR}\"")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--rpath=/usr/apps/com.samsung.noa/lib -Wl,--as-needed")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-common -Wstrict-prototypes -O0 -g3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor")

SET(LIB_SO	-L${CMAKE_BINARY_DIR}/${COMMON_DIR} -l${LIB_NAME_COM})

# add source file
ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIB_SO})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${pkgs_LDFLAGS} "-ljpeg -lcapi-appfw-app-manager")

ADD_DEPENDENCIES(${PROJECT_NAME} ${LIB_NAME_COM})

# make noa.edj
ADD_CUSTOM_TARGET(noa.edj
					COMMAND edje_cc -id ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${IMG_DIR}
					${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/noa.edc
					${CMAKE_BINARY_DIR}/noa.edj
					DEPENDS ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/noa.edc )
ADD_DEPENDENCIES(${PROJECT_NAME} noa.edj)

# added by wulin, two edc files
ADD_CUSTOM_TARGET(create_view_naviframe.edj
					COMMAND edje_cc -id ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${IMG_DIR}
					${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/create_view_naviframe.edc
					${CMAKE_BINARY_DIR}/create_view_naviframe.edj
					DEPENDS ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/create_view_naviframe.edc )

ADD_DEPENDENCIES(${PROJECT_NAME} create_view_naviframe.edj)

ADD_CUSTOM_TARGET(create_view_button.edj
					COMMAND edje_cc -id ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${IMG_DIR}
					${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/create_view_button.edc
					${CMAKE_BINARY_DIR}/create_view_button.edj
					DEPENDS ${CMAKE_SOURCE_DIR}/${RSRC_DIR}/${EDC_DIR}/create_view_button.edc )

ADD_DEPENDENCIES(${PROJECT_NAME} noa.edj)
ADD_DEPENDENCIES(${PROJECT_NAME} create_view_naviframe.edj)
ADD_DEPENDENCIES(${PROJECT_NAME} create_view_button.edj)

# install edj file
INSTALL(FILES ${CMAKE_BINARY_DIR}/noa.edj DESTINATION ${EDJDIR})
INSTALL(FILES ${CMAKE_BINARY_DIR}/create_view_button.edj DESTINATION ${EDJDIR})
INSTALL(FILES ${CMAKE_BINARY_DIR}/create_view_naviframe.edj DESTINATION ${EDJDIR})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${BINDIR})
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/res/images DESTINATION ${RESDIR})

# install desktop file & icon
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/${PKGNAME}.desktop.in ${CMAKE_SOURCE_DIR}/${PKGNAME}.desktop)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PKGNAME}.desktop DESTINATION /usr/share/applications)

INSTALL(FILES ${CMAKE_SOURCE_DIR}/com.samsung.noa.xml DESTINATION /usr/share/packages/)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/com.samsung.noa.png DESTINATION /usr/share/icons/default/small)

INSTALL(DIRECTORY DESTINATION ${DATADIR})
#INSTALL(FILES /usr/include/cairo/cairo.h DESTINATION ${CMAKE_SOURCE_DIR}/include)

# ADD_SUBDIRECTORY(res/po)