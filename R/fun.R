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
