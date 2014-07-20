#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// kmeans
List kmeans(const arma::mat& data, const int& clusters);
RcppExport SEXP RcppMLPACK_kmeans(SEXP dataSEXP, SEXP clustersSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const arma::mat& >::type data(dataSEXP );
        Rcpp::traits::input_parameter< const int& >::type clusters(clustersSEXP );
        List __result = kmeans(data, clusters);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
