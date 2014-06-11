\name{kmeans}
\alias{kmeans}
\title{kmeans from MLPACK}
\description{
  \code{kmeans} from MLPACK.
}
\usage{
kmeans(X, y)
}
\arguments{
  \item{X}{data matrix.}
  \item{y}{number of clusters.}
}
\details{
  \code{kmeans} from MLPACK.
}
\value{
  \code{kmeans} returns a list with cluster assignment:
}
\references{MLPACK project: \url{http://www.mlpack.org/}}
\author{
  MLPACK is written by Ryan Curtin. RcppMLPACK is written by Qiang Kou.
}
\examples{
  data(trees, package="datasets")
  kmeans(t(trees),3)
}
