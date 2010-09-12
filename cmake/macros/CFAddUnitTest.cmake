##############################################################################
# macro for adding a testing application in the project
##############################################################################

MACRO( CF_ADD_UNITTEST UTESTNAME )

  # option to build it or not
  OPTION( CF_BUILD_${UTESTNAME} "Build the ${UTESTNAME} testing application" ON )
  # this option is advanced (does not appear in the cmake gui)
  MARK_AS_ADVANCED(CF_BUILD_${UTESTNAME})

  # add to list of local apps
  LIST( APPEND CF_LOCAL_UTESTNAMES ${UTESTNAME} )

#   CF_DEBUG_VAR(CF_MODULES_LIST)

  # check if all required modules are present
  SET( ${UTESTNAME}_all_mods_pres ON )
  FOREACH( reqmod ${${UTESTNAME}_requires_mods} )
    LIST( FIND CF_MODULES_LIST ${reqmod} pos )
    IF( ${pos} EQUAL -1 )
      SET( ${UTESTNAME}_all_mods_pres OFF )
      IF( CF_BUILD_${UTESTNAME} )
          coolfluid_log_verbose ( "     \# utest [${UTESTNAME}] requires module [${reqmod}] which is not present")
      ENDIF()
    ENDIF()
  ENDFOREACH()

  # check that all CF dependencies will be compiling
  # else skip this uTest
  SET( ${UTESTNAME}_all_cfdeps_ok ON )
  FOREACH( reqlib ${${UTESTNAME}_cflibs} )
    IF( NOT ${${reqlib}_will_compile} )
       SET( ${UTESTNAME}_all_cfdeps_ok OFF )
       IF( CF_BUILD_${UTESTNAME} )
           coolfluid_log_verbose ( "     \# utest [${UTESTNAME}] requires cflib [${reqlib}] which will not compile")
       ENDIF()
    ENDIF()
  ENDFOREACH()
  MARK_AS_ADVANCED( ${UTESTNAME}_all_cfdeps_ok )

  SET( ${UTESTNAME}_dir ${CMAKE_CURRENT_SOURCE_DIR} )

  IF( CF_BUILD_${UTESTNAME} AND ${UTESTNAME}_all_cfdeps_ok AND ${UTESTNAME}_all_mods_pres)
    SET( ${UTESTNAME}_will_compile ON )
  ELSE()
    SET( ${UTESTNAME}_will_compile OFF )
  ENDIF()

  coolfluid_log_verbose("test_${UTESTNAME} = ${${UTESTNAME}_will_compile}")

  # separate the source files
  # and remove them from the orphan list

  CF_SEPARATE_SOURCES("${${UTESTNAME}_files}" ${UTESTNAME})

  SOURCE_GROUP( Headers FILES ${${UTESTNAME}_headers} )
  SOURCE_GROUP( Sources FILES ${${UTESTNAME}_sources} )

  # compile if selected and all required modules are present
  IF(${UTESTNAME}_will_compile)

    IF( DEFINED ${UTESTNAME}_includedirs )
      INCLUDE_DIRECTORIES(${${UTESTNAME}_includedirs})
    ENDIF()

    coolfluid_log( " +++ TEST [${UTESTNAME}]" )

    IF( DEFINED ${UTESTNAME}_moc_files )
      ADD_EXECUTABLE( ${UTESTNAME} ${${UTESTNAME}_sources} ${${UTESTNAME}_headers}  ${${UTESTNAME}_moc_files})
    ELSE()
      ADD_EXECUTABLE( ${UTESTNAME} ${${UTESTNAME}_sources} ${${UTESTNAME}_headers})
    ENDIF()

    IF(CF_INSTALL_TESTS)
      # add installation paths
      INSTALL( TARGETS ${UTESTNAME}
        RUNTIME DESTINATION ${CF_INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${CF_INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${CF_INSTALL_LIB_DIR}
        )
    ENDIF(CF_INSTALL_TESTS)

    # if mpi was found add it to the libraries
    IF(CF_HAVE_MPI AND NOT CF_HAVE_MPI_COMPILER)
#           MESSAGE ( STATUS "${UTESTNAME} links to ${MPI_LIBRARIES}" )
          TARGET_LINK_LIBRARIES ( ${UTESTNAME} ${MPI_LIBRARIES} )
    ENDIF()

    # add external dependency libraries if defined
    IF( DEFINED ${UTESTNAME}_libs )
      TARGET_LINK_LIBRARIES( ${UTESTNAME} ${${UTESTNAME}_libs} )
    ENDIF(DEFINED ${UTESTNAME}_libs)

    # profiling gloabally selected
    if( CF_ENABLE_PROFILING AND CF_PROFILER_IS_GOOGLE AND CF_BUILD_GooglePerfTools )
      LIST( APPEND ${UTESTNAME}_cflibs GooglePerfTools )
    endif()

    # profiling selected for specific target
    if( ${UTESTNAME}_profile AND CF_BUILD_GooglePerfTools )
      LIST( APPEND ${UTESTNAME}_cflibs GooglePerfTools )
    endif()

    # internal dependencies
    if( DEFINED ${UTESTNAME}_cflibs )
        TARGET_LINK_LIBRARIES ( ${UTESTNAME} ${${UTESTNAME}_cflibs} )
    endif()

  # add to the test database
  ADD_TEST( ${UTESTNAME} ${UTESTNAME} ${${UTESTNAME}_args})

  ENDIF()

  GET_TARGET_PROPERTY( ${UTESTNAME}_P_SOURCES   ${UTESTNAME} SOURCES )
  GET_TARGET_PROPERTY( ${UTESTNAME}_LINK_FLAGS       ${UTESTNAME} LINK_FLAGS )
  GET_TARGET_PROPERTY( ${UTESTNAME}_TYPE             ${UTESTNAME} TYPE )

  # log some info about the app
  coolfluid_log_file("${UTESTNAME} : [${CF_BUILD_${UTESTNAME}}]")
  coolfluid_log_file("${UTESTNAME} : [${${UTESTNAME}_will_compile}]")
  coolfluid_log_file("${UTESTNAME}_dir             : [${${UTESTNAME}_dir}]")
  coolfluid_log_file("${UTESTNAME}_includedirs     : [${${UTESTNAME}_includedirs}]")
  coolfluid_log_file("${UTESTNAME}_libs            : [${${UTESTNAME}_libs}]")
  coolfluid_log_file("${UTESTNAME}_cflibs          : [${${UTESTNAME}_cflibs}]")
  coolfluid_log_file("${UTESTNAME}_all_mods_pres   : [${${UTESTNAME}_all_mods_pres}]")
  coolfluid_log_file("${UTESTNAME}_requires_mods   : [${${UTESTNAME}_requires_mods}]")
  coolfluid_log_file("${UTESTNAME}_P_SOURCES       : [${${UTESTNAME}_P_SOURCES}]")
  coolfluid_log_file("${UTESTNAME}_LINK_FLAGS      : [${${UTESTNAME}_LINK_FLAGS}]")
  coolfluid_log_file("${UTESTNAME}_TYPE            : [${${UTESTNAME}_TYPE}]")


ENDMACRO( CF_ADD_UNITTEST )

##############################################################################
# macro for adding a testing application in the project, profiled with perftools
##############################################################################

MACRO( CF_ADD_PROFILED_UNITTEST UTESTNAME )

ENDMACRO( CF_ADD_PROFILED_UNITTEST )

##############################################################################
