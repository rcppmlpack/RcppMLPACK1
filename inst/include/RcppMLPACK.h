#ifndef RcppMLPACK__RcppMLPACK__h
#define RcppMLPACK__RcppMLPACK__h

#if defined(Rcpp_hpp) && !defined(COMPILING_RCPPMLPACK)
    #error "The file 'Rcpp.h' should not be included. Please correct to include only 'RcppMLPACK.h'."
#endif

#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>

#endif
