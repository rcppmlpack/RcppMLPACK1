inlineCxxPlugin <- function(...) {
    plugin <- Rcpp::Rcpp.plugin.maker(
        include.before = "#include <RcppMLPACK.h>", 
        libs = sprintf("%s $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)", RcppMLPACKLdFlags()),
        LinkingTo      = c("RcppArmadillo", "Rcpp", "BH", "RcppMLPACK"),
        package        = "RcppMLPACK"
    )
    settings <- plugin()
    settings
}
