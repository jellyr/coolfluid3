# Confirm that liblapack library is installed
# This module defines
#   CF_HAVE_LAPACK
#   CF_HAVE_BLAS
#   CF_HAVE_BLASLAPACK
#   CF_BLASLAPACK_LIBRARIES
# Require both lapack and blas

IF ( NOT LAPACK_LIBRARIES )

# BLAS ############################

  IF ( NOT CF_HAVE_BLAS )

    IF ( EXISTS ${BLAS_DIR} )
      ADD_TRIAL_LIBRARY_PATH( ${BLAS_DIR} )
      ADD_TRIAL_LIBRARY_PATH( ${BLAS_DIR}/lib )
    ENDIF()

    IF ( EXISTS $ENV{BLAS_HOME} )
      ADD_TRIAL_LIBRARY_PATH( $ENV{BLAS_HOME}/lib )
    ENDIF()

    FIND_LIBRARY(BLAS_LIBRARY blas ${TRIAL_LIBRARY_PATHS} NO_DEFAULT_PATH)
    FIND_LIBRARY(BLAS_LIBRARY blas )

    IF ( BLAS_LIBRARY )
      SET ( CF_HAVE_BLAS 1 CACHE BOOL "Found BLAS library" )
    ELSE()
      SET ( CF_HAVE_BLAS 0 )
    ENDIF()

  ENDIF()

  coolfluid_log( "CF_HAVE_BLAS: [${CF_HAVE_BLAS}]" )
  IF(CF_HAVE_BLAS)
     coolfluid_log( "  BLAS_LIBRARY:     [${BLAS_LIBRARY}]" )
  ENDIF(CF_HAVE_BLAS)

# LAPACK #########################

  IF ( NOT CF_HAVE_LAPACK )

    SET_TRIAL_INCLUDE_PATH ("") # clear include search path
    SET_TRIAL_LIBRARY_PATH ("") # clear library search path


    IF( EXISTS ${LAPACK_DIR} )
      ADD_TRIAL_LIBRARY_PATH ( ${LAPACK_DIR}  )
      ADD_TRIAL_LIBRARY_PATH ( ${LAPACK_DIR}/lib )
    ENDIF()

    IF( EXISTS $ENV{LAPACK_HOME} )
      ADD_TRIAL_LIBRARY_PATH( $ENV{LAPACK_HOME} )
      ADD_TRIAL_LIBRARY_PATH( $ENV{LAPACK_HOME}/lib )
    ENDIF()

    FIND_LIBRARY(LAPACK_LIBRARY lapack ${TRIAL_LIBRARY_PATHS} NO_DEFAULT_PATH)
    FIND_LIBRARY(LAPACK_LIBRARY lapack )

  ENDIF()

  IF ( LAPACK_LIBRARY )
    SET ( CF_HAVE_LAPACK 1 CACHE BOOL "Found LAPACK library")
  ELSE()
    SET ( CF_HAVE_LAPACK 0 )
  ENDIF()


  coolfluid_log( "CF_HAVE_LAPACK: [${CF_HAVE_LAPACK}]" )
  IF(CF_HAVE_LAPACK)
    coolfluid_log( "  LAPACK_LIBRARY:   [${LAPACK_LIBRARY}]" )
  ENDIF(CF_HAVE_LAPACK)

# BOTH ###########################

  IF ( CF_HAVE_BLAS AND CF_HAVE_LAPACK )
    SET ( CF_BLASLAPACK_LIBRARIES   "${LAPACK_LIBRARY} ${BLAS_LIBRARY}" CACHE STRING "BLAS and LAPACK libraries")
    SET ( CF_HAVE_BLASLAPACK ON CACHE BOOL "Found BLAS and LAPACK libraries")
  ENDIF()

  MARK_AS_ADVANCED ( LAPACK_LIBRARY BLAS_LIBRARY )

#################################

ELSE()

  # user provided directly the libraries of LAPACK
  # TODO: test  that they actually work

  SET(CF_HAVE_LAPACK       ON CACHE BOOL "Found LAPACK library")
  SET(CF_HAVE_BLAS         ON CACHE BOOL "Found BLAS   library")
  SET(CF_HAVE_BLASLAPACK   ON CACHE BOOL "Found BLAS and LAPACK libraries")

  SET ( CF_BLASLAPACK_LIBRARIES   "${LAPACK_LIBRARIES}" CACHE STRING "BLAS and LAPACK libraries")

  MARK_AS_ADVANCED ( CF_BLASLAPACK_LIBRARIES LAPACK_LIBRARIES )

  coolfluid_log( "CF_HAVE_BLASLAPACK: [${CF_HAVE_BLASLAPACK}]" )
  coolfluid_log( "  LAPACK_LIBRARIES: [${LAPACK_LIBRARIES}]" )

ENDIF()

MARK_AS_ADVANCED ( CF_HAVE_LAPACK CF_HAVE_BLAS CF_HAVE_BLASLAPACK CF_BLASLAPACK_LIBRARIES )

