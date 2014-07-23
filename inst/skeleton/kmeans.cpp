#include "RcppMLPACK.h"

using namespace mlpack::kmeans;
using namespace Rcpp;

// [[Rcpp::export]]
List mlkmeans(const arma::mat& data, const int& clusters) {
    
    arma::Col<size_t> assignments;

	// Initialize with the default arguments.
	KMeans<> k;

	k.Cluster(data, clusters, assignments); 

    return List::create(_["clusters"]	= clusters,
                        _["result"]		= assignments);
}
