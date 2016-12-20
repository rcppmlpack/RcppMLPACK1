##  RcppMLPACK configure.ac
##
##  RcppMLPACK compiler check modified from RcppArmadillo to check for gcc > 4.6
##
##  Copyright (C) 2016 Dirk Eddelbuettel, James Balamuta
##
##  Licensed under GPL-2 or later

## require at least autoconf 2.61
AC_PREREQ(2.61)

## Process this file with autoconf to produce a configure script.
AC_INIT(RcppMLPACK, m4_esyscmd_s([awk -e '/^Version:/ {print $2}' DESCRIPTION]))

## Set R_HOME, respecting an environment variable if one is set 
: ${R_HOME=$(R RHOME)}
if test -z "${R_HOME}"; then
    AC_MSG_ERROR([Could not determine R_HOME.])   
fi
## Use R to set CXX and CXXFLAGS
CXX=$(${R_HOME}/bin/R CMD config CXX)
CXXFLAGS=$("${R_HOME}/bin/R" CMD config CXXFLAGS)

## We are using C++
AC_LANG(C++)
AC_REQUIRE_CPP

## Check the C++ compiler using the CXX value set
AC_PROG_CXX

## If it is g++, we have GXX set so let's examine it
if test "${GXX}" = yes; then
    AC_MSG_CHECKING([whether g++ version is sufficient])
    gxx_version=$(${CXX} -v 2>&1 | awk '/^.*g.. version/ {print $3}')
    case ${gxx_version} in
        1.*|2.*|3.*|4.0.*|4.1.*|4.2.*|4.3.*|4.4.*|4.5.*|4.6.*)
             AC_MSG_RESULT([no])
	     AC_MSG_WARN([Only g++ version 4.7 or greater can be used with RcppMLPACK.])
	     AC_MSG_ERROR([Please use a different compiler.])   
        ;;
	  4.7.*|4.8.*|4.9.*|5.*|6.*) ## Removes gcc 4.6.* from this line
	     gxx_newer_than_45="-fpermissive"
             AC_MSG_RESULT([(${gxx_version}) yes])
	;;
    esac
fi