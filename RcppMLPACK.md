RcppMLPACK: R integration with MLPACK using Rcpp
========================================================

MLPACK
----------------
MLPACK is a C++ machine learning library with emphasis on scalability, speed, and ease-of-use. It outperforms competing machine learning libraries by large margins, for detailed results of benchmarking, please visit the [MLPACK website](http://mlpack.org/).

Input/Output using Armadillo
-------------------------------
MLPACK uses Armadillo as input and output, which is widely used in C++ libraries. However, there is one point we need to pay attention to: Armadillo matrices in MLPACK are stored in **a column-major format** for speed. That means **observations are stored as columns and dimensions as rows**.

So when using MLPACK, additional transpose may be needed.

Simple API
---------------------
MLPACK relies on template techniques in C++, and it provides an intuitive and simple API.
For the standard usage of methods, default arguments are provided.

The MLPACK paper provides a good example: standard k-means clustering in Euclidean space can be initialized like below:

```cpp
KMeans<> k();
```

If we want to use Manhattan distance, a different cluster initialization policy, and allow empty clusters,
the object can be initialized with additional arguments:

```cpp
KMeans<ManhattanDistance, KMeansPlusPlusInitialization, AllowEmptyClusters> k();
```
Available methods in MLPACK
---------------------------
Commonly used machine learning methods are all implemented in MLPACK.
Besides, it contains a strong set of tree-building and tree-query routines.

* Fast Hierarchical Clustering (Euclidean Minimum Spanning Trees)
* Gaussian Mixture Models (trained via EM)
* Hidden Markov Models (training, prediction, and classiﬁcation)
* Kernel Principal Components Analysis
* K-Means clustering
* LARS/Lasso Regression
* Least-squares Linear Regression
* Maximum Variance Unfolding (using LRSDP)
* Naive Bayes Classiﬁer
* Neighborhood Components Analysis (using LRSDP)
* RADICAL (Robust, Accurate, Direct ICA aLgorithm)
* Tree-based k-nearest-neighbors search and classiﬁer
* Tree-based range search

For the details of each algorithm and usage, please visit the [tutorial page](http://www.mlpack.org/tutorial.html) of MLPACK.

RcppMLPACK
---------------
As said above, MLPACK is a C++ library using Armadillo.
Since we Rcpp and RcppArmadillo,
which can used to integrate C++ and Armadillo with R seamlessly,
RcppMLPACK becomes something very natural.

k-means example
------------------
Here we continue the k-means example above. By using RcppMLPACK, a k-means method which can be called by R can be implemented like below. The interfere between R and C++ is handled by Rcpp and RcppArmadillo.


```cpp
#include "RcppMLPACK.h"

using namespace mlpack::kmeans;
using namespace Rcpp;

// [[Rcpp::export]]
List kmeans(const arma::mat& data, const int& clusters) {
    
    arma::Col<size_t> assignments;

    // Initialize with the default arguments.
    KMeans<> k;

    k.Cluster(data, clusters, assignments); 

    return List::create(_["clusters"] = clusters,
                        _["result"]   = assignments);
}
```
Using inline
------------------------
inline package provides a complete
wrapper around the compilation, linking, and loading steps.
So all the steps can be done in an R session.
There is no reason that RcppMLPACK doesn't support the inline compilation.

```r
library(inline)
library(RcppMLPACK)
code <- '
  arma::mat data = as<arma::mat>(test);
  int clusters = as<int>(n);
  arma::Col<size_t> assignments;
  mlpack::kmeans::KMeans<> k;
  k.Cluster(data, clusters, assignments); 
  return List::create(_["clusters"] = clusters,
                      _["result"]   = assignments);
'
mlKmeans <- cxxfunction(signature(test="numeric", n ="integer"), code, 
                        plugin="RcppMLPACK")
data(trees, package="datasets")
mlKmeans(t(trees), 3)
```
As said above, MLPACK uses a column-major format of matrix, so when we pass data from R to MLPACK, a transpose may be needed.

RcppMLPACK.package.skeleton
-----------------------
The package also contains a RcppMLPACK.package.skeleton() function for people who want to
use MLPACK code in their own package. It follows the structure of RcppArmadillo.package.skeleton().


```r
library(RcppMLPACK)
library(RcppMLPACK)
RcppMLPACK.package.skeleton("foobar")
Creating directories ...
Creating DESCRIPTION ...
Creating NAMESPACE ...
Creating Read-and-delete-me ...
Saving functions and data ...
Making help files ...
Done.
Further steps are described in './foobar/Read-and-delete-me'.

Adding RcppMLPACK settings
 >> added Imports: Rcpp
 >> added LinkingTo: Rcpp, RcppArmadillo, BH, RcppMLPACK
 >> added useDynLib and importFrom directives to NAMESPACE
 >> added Makevars file with RcppMLPACK settings
 >> added Makevars.win file with RcppMLPACK settings
 >> added example src file using MLPACK classes
 >> invoked Rcpp::compileAttributes to create wrappers
```
By using RcppMLPACK.package.skeleton(), a package skeleton is generated and files are list below.


```r
system("ls -R foobar")
foobar:
DESCRIPTION  man  NAMESPACE  R  Read-and-delete-me  src

foobar/man:
foobar-package.Rd

foobar/R:
RcppExports.R

foobar/src:
kmeans.cpp  Makevars  Makevars.win  RcppExports.cpp
```
Performance
-------------------------

Even without a performance testing, we are still sure the C++ implementations should be faster.
A small [wine data set](https://archive.ics.uci.edu/ml/datasets/Wine) from UCI data sets repository is used for benchmarking.
rbenchmark package is also used.

```r
suppressMessages(library(rbenchmark))
res <- benchmark(mlKmeans(t(wine),3),
                 kmeans(wine,3),
                 columns=c("test", "replications", "elapsed",
                 "relative", "user.self", "sys.self"), order="relative")
```
From benchmarking result, we can see that MLPACK version of k-means is 33-time faster than \texttt{kmeans()} in R.
However, we should note that R returns more information than the clustering result and there are much more checking functions in R.


|test | replications | elapsed | relative | user.self | sys.self|
|----:|-------------:|--------:|---------:|----------:|--------:|
|mlKmeans(t(wine), 3) | 100|  0.028 |   1.000|     0.028  |  0.000|
| kmeans(wine, 3)  |        100|  0.947|   33.821|    0.484 |   0.424|

Modifications on original MLPACK library
-----------------------------------------
To avoid the maintenance tasks, we try to minimize the modification on MLPACK.
However, for the integration and pass R CMD check, there are some changes we have to make.
There is no changes in the methods, all modifications are in utility classes.

* Log class provides four levels of log information. The logging functions are replaced with Rcpp::Rcout to redirect the output stream to R session.

* cli class is used to parse the command line arguments. It relies on boost::program_options which requires additional linking. Since all arguments are passed from R, this class is removed.

* SaveRestoreUtility class is used to store and restore MLPACK models from XML files. This class has been removed to avoid additional linking to libxml2.

* Timer class is used in many methods for timing and print information into log. This class has been commented.

Known problems
--------------------------

There is an important problem in MLPACK: it uses **size_t** type heavily.
There may be problems in wrapping such type, especially on 64-bit Windows.
