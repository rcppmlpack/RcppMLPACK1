mlKmeans <- function(X, y) {

    X <- matrix(as.numeric(unlist(X)),nrow=nrow(X))
    y <- as.numeric(y)

    .Call( "RcppMLPACK_kmeans", t(X), y, PACKAGE = "RcppMLPACK" )

}
