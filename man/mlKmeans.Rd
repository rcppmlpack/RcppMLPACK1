\name{mlKmeans}
\alias{mlKmeans}
\title{kmeans from MLPACK}
\description{
  kmeans example for using MLPACK with R.
}
\usage{
mlKmeans(X, y)
}
\arguments{
  \item{X}{data matrix.}
  \item{y}{number of clusters.}
}
\details{
  This is a kmeans example using RcppMLPACK. It uses the Kmeans method in MLPACK and integrates with R.
}
\value{
  \code{mlKmeans} returns a list with cluster assignment:
}
\references{MLPACK project: \url{http://www.mlpack.org/}}
\author{
  For RcppMLPACK: Qiang Kou
  
  For MLPACK: Ryan Curtin
}
\examples{
\dontrun{
  data(trees, package="datasets")
  mlKmeans(t(trees),3)
}
}
