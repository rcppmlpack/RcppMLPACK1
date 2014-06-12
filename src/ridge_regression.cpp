#include "RcppMLPACK.h"

using namespace Rcpp;
using namespace mlpack::regression;

// [[Rcpp::export]]

List ridge(const arma::mat& data, const arma::vec& responses, const int& lambda) {
    
	LinearRegression lr(data, responses, lambda);

	arma::vec parameters = lr.Parameters();
	
    return List::create(_["parameters"]	= parameters,
                        _["lambda"]		= lambda);
}
