#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// kmeans
List kmeans(SEXP data, const int& clusters);
RcppExport SEXP RcppMLPACK_kmeans(SEXP dataSEXP, SEXP clustersSEXP) {
BEGIN_RCPP
  Rcpp::RObject rcpp_result_gen;
  Rcpp::RNGScope rcpp_rngScope_gen;
  Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
  Rcpp::traits::input_parameter< const int& >::type clusters(clustersSEXP);
  rcpp_result_gen = Rcpp::wrap(kmeans(data, clusters));
  return rcpp_result_gen;
END_RCPP
}
