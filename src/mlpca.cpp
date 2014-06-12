#include "RcppMLPACK.h"

using namespace mlpack;
using namespace mlpack::pca;
using namespace Rcpp;

// [[Rcpp::export]]

List mlpca(arma::mat& dataset, const double& scale, double& varRetained) {
    
    PCA p(scale);

	varRetained = p.Apply(dataset, varRetained);

    return List::create(_["variance retained"]	= varRetained,
                        _["dataset"]			= dataset);
}
