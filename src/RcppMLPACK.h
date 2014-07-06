#ifndef RcppMLPACK__RcppMLPACK__h
#define RcppMLPACK__RcppMLPACK__h

#if defined(Rcpp_hpp) && !defined(COMPILING_RCPPMLPACK)
    #error "The file 'Rcpp.h' should not be included. Please correct to include only 'RcppMLPACK.h'."
#endif

#include <RcppArmadillo.h>
#include <Rcpp.h>

#include <mlpack/core.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/methods/kmeans/allow_empty_clusters.hpp>
#include <mlpack/methods/kmeans/refined_start.hpp>
#include <mlpack/methods/pca/pca.hpp>
#include <mlpack/methods/range_search/range_search.hpp>
#include <mlpack/methods/lsh/lsh_search.hpp>
#endif
