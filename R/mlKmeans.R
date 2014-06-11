mlKmeans <- function(X, y) {

    X <- as.matrix(X)
    y <- as.numeric(y)

    .Call( "RcppMLPACK_kmeans", X, y, PACKAGE = "RcppMLPACK" )

}
