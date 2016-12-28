#include "RcppMLPACK.h"

using namespace mlpack::kmeans;
using namespace Rcpp;

// [[Rcpp::export]]
List kmeans(SEXP data, const int& clusters) {

  NumericMatrix Xr(data);
  arma::mat X(Xr.begin(), Xr.nrow(), Xr.ncol(), false); 
  arma::Col<size_t> assignments;

  // Initialize with the default arguments.
  KMeans<> k;

  k.Cluster(X, clusters, assignments); 

  return List::create(_["clusters"]	= clusters,
                      _["result"]		= assignments);
}
