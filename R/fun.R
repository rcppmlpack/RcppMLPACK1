mlKmeans <- function(X, y) {

    X <- as.matrix(X)
    y <- as.numeric(y)

    .Call( "RcppMLPACK_kmeans", X, y, PACKAGE = "RcppMLPACK" )

}

mlRidge <- function(X, y, lambda) {

    X <- as.matrix(X)
    y <- as.vector(y)
    lambda <- as.numeric(lambda)

    .Call( "RcppMLPACK_ridge", X, y, lambda, PACKAGE = "RcppMLPACK" )

}

mlPCA <- function(X, scale, varRetained) {

    X <- as.matrix(X)
    scale <- as.vector(scale)
    varRetained <- as.numeric(varRetained)

    .Call( "RcppMLPACK_mlpca", X, scale, varRetained, PACKAGE = "RcppMLPACK" )

}
