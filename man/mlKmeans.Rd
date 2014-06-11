\name{mlKmeans}
\alias{mlKmeans}
\title{kmeans from MLPACK}
\description{
  kmeans from MLPACK.
}
\usage{
mlKmeans(X, y)
}
\arguments{
  \item{X}{data matrix.}
  \item{y}{number of clusters.}
}
\details{
  kmeans from MLPACK.
}
\value{
  \code{mlKmeans} returns a list with cluster assignment:
}
\references{MLPACK project: \url{http://www.mlpack.org/}}
\author{
  MLPACK is written by Ryan Curtin. RcppMLPACK is written by Qiang Kou.
}
\examples{
  data(trees, package="datasets")
  mlKmeans(t(trees),3)
}
