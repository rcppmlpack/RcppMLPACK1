\name{mlRidge}
\alias{mlRidge}
\title{ridge regression from MLPACK}
\description{
  ridge regression from MLPACK.
}
\usage{
mlRidge(X, y, lambda)
}
\arguments{
  \item{X}{data matrix.}
  \item{y}{number of clusters.}
  \item{lambda}{lambda in ridge regression.}
}
\details{
  ridge regression from MLPACK.
}
\value{
  \code{mlRidge} returns a list with coefficients.
}
\references{MLPACK project: \url{http://www.mlpack.org/}}
\author{
  MLPACK is written by Ryan Curtin. RcppMLPACK is written by Qiang Kou.
}
