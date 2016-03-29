RcppMLPACK
==========

[![Build Status](https://travis-ci.org/thirdwing/RcppMLPACK.svg?branch=master)](https://travis-ci.org/thirdwing/RcppMLPACK)

[MLPACK](http://www.mlpack.org/) is a C++ machine learning library with emphasis on scalability, speed, and ease-of-use. Its aim is to make machine learning possible for novice users by means of a simple, consistent API, while simultaneously exploiting C++ language features to provide maximum performance and maximum flexibility for expert users. MLPACK outperforms competing machine learning libraries by large margins; see the [BigLearning workshop paper](http://www.mlpack.org/papers/mlpack2011.pdf) for details. 

The algorithms implemented in MLPACK:

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

The RcppMLPACK package includes the source code from the MLPACK library. Thus users do not need to install MLPACK itself in order to use RcppMLPACK. 
 
This MLPACK integration heavily relies on [Rcpp](http://www.rcpp.org) and RcppArmadillo packages. 

The version number of MLPACK is used as the version number of this package. 

Testing and bug reports are deeply welcome.

You can find examples in the [wiki page](https://github.com/thirdwing/RcppMLPACK/wiki). You can always find me by email (qkou@umail.iu.edu) if you have any questions.

[Qiang Kou](https://www.linkedin.com/pub/qiang-kou/2a/986/6b7)
