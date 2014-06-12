#include "RcppMLPACK.h"
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
// ridge
List ridge(const arma::mat& data, const arma::vec& responses, const int& lambda);
RcppExport SEXP RcppMLPACK_ridge(SEXP dataSEXP, SEXP responsesSEXP, SEXP lambdaSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const arma::mat& >::type data(dataSEXP );
        Rcpp::traits::input_parameter< const arma::vec& >::type responses(responsesSEXP );
        Rcpp::traits::input_parameter< const int& >::type lambda(lambdaSEXP );
        List __result = ridge(data, responses, lambda);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// mlpca
List mlpca(arma::mat& dataset, const double& scale, double& varRetained);
RcppExport SEXP RcppMLPACK_mlpca(SEXP datasetSEXP, SEXP scaleSEXP, SEXP varRetainedSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< arma::mat& >::type dataset(datasetSEXP );
        Rcpp::traits::input_parameter< const double& >::type scale(scaleSEXP );
        Rcpp::traits::input_parameter< double& >::type varRetained(varRetainedSEXP );
        List __result = mlpca(dataset, scale, varRetained);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
