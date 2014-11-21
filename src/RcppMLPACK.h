#ifndef RcppMLPACK__RcppMLPACK__h
#define RcppMLPACK__RcppMLPACK__h

#if _WIN64
#ifndef ARMA_64BIT_WORD
#define ARMA_64BIT_WORD
#endif
#endif

#if defined(__MINGW32__)
#define ARMA_DONT_USE_CXX11
#endif

#include <mlpack/core.hpp>
#include <mlpack/core/kernels/cosine_distance.hpp>
#include <mlpack/core/kernels/epanechnikov_kernel.hpp>
#include <mlpack/core/kernels/gaussian_kernel.hpp>
#include <mlpack/core/kernels/hyperbolic_tangent_kernel.hpp>
#include <mlpack/core/kernels/laplacian_kernel.hpp>
#include <mlpack/core/kernels/linear_kernel.hpp>
#include <mlpack/core/kernels/polynomial_kernel.hpp>
#include <mlpack/core/kernels/spherical_kernel.hpp>
#include <mlpack/core/kernels/pspectrum_string_kernel.hpp>
#include <mlpack/core/metrics/lmetric.hpp>
#include <mlpack/core/metrics/mahalanobis_distance.hpp>
#include <mlpack/core/tree/binary_space_tree.hpp>
#include <mlpack/core/tree/binary_space_tree/binary_space_tree.hpp>
#include <mlpack/core/tree/bounds.hpp>
#include <mlpack/core/tree/cover_tree.hpp>
#include <mlpack/core/tree/cover_tree/cover_tree.hpp>
#include <mlpack/core/tree/cosine_tree/cosine_tree.hpp>
#include <mlpack/core/tree/tree_traits.hpp>
#include <mlpack/core/metrics/lmetric.hpp>
#include <mlpack/core/optimizers/aug_lagrangian/aug_lagrangian.hpp>
#include <mlpack/core/optimizers/aug_lagrangian/aug_lagrangian_test_functions.hpp>
#include <mlpack/core/optimizers/lbfgs/lbfgs.hpp>
#include <mlpack/core/optimizers/lbfgs/test_functions.hpp>
#include <mlpack/core/optimizers/lrsdp/lrsdp.hpp>
#include <mlpack/core/optimizers/sgd/sgd.hpp>
#include <mlpack/core/optimizers/sgd/test_function.hpp>

#include <mlpack/methods/amf/amf.hpp>
#include <mlpack/methods/amf/init_rules/random_init.hpp>
#include <mlpack/methods/amf/update_rules/nmf_mult_dist.hpp>
#include <mlpack/methods/amf/update_rules/nmf_mult_div.hpp>
#include <mlpack/methods/amf/update_rules/nmf_als.hpp>
#include <mlpack/methods/amf/termination_policies/simple_residue_termination.hpp>
#include <mlpack/methods/cf/cf.hpp>
#include <mlpack/methods/det/dt_utils.hpp>
#include <mlpack/methods/decision_stump/decision_stump.hpp>
#include <mlpack/methods/emst/union_find.hpp>
#include <mlpack/methods/emst/dtb.hpp>
#include <mlpack/methods/fastmks/fastmks.hpp>
#include <mlpack/methods/gmm/gmm.hpp>
#include <mlpack/methods/gmm/phi.hpp>
#include <mlpack/methods/gmm/no_constraint.hpp>
#include <mlpack/methods/gmm/positive_definite_constraint.hpp>
#include <mlpack/methods/gmm/diagonal_constraint.hpp>
#include <mlpack/methods/gmm/eigenvalue_ratio_constraint.hpp>
#include <mlpack/methods/hmm/hmm.hpp>
#include <mlpack/methods/lars/lars.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <mlpack/methods/logistic_regression/logistic_regression.hpp>
#include <mlpack/methods/kernel_pca/kernel_rules/nystroem_method.hpp>
#include <mlpack/methods/kernel_pca/kernel_pca.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/methods/kmeans/allow_empty_clusters.hpp>
#include <mlpack/methods/kmeans/refined_start.hpp>
#include <mlpack/methods/lsh/lsh_search.hpp>
#include <mlpack/methods/local_coordinate_coding/lcc.hpp>
#include <mlpack/methods/mvu/mvu.hpp>
#include <mlpack/methods/nca/nca.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <mlpack/methods/neighbor_search/unmap.hpp>
#include <mlpack/methods/neighbor_search/typedef.hpp>
#include <mlpack/methods/nystroem_method/ordered_selection.hpp>
#include <mlpack/methods/nystroem_method/random_selection.hpp>
#include <mlpack/methods/nystroem_method/kmeans_selection.hpp>
#include <mlpack/methods/nystroem_method/nystroem_method.hpp>
#include <mlpack/methods/pca/pca.hpp>
#include <mlpack/methods/perceptron/perceptron.hpp>
#include <mlpack/methods/radical/radical.hpp>
#include <mlpack/methods/range_search/range_search.hpp>
#include <mlpack/methods/rann/ra_search.hpp>
#include <mlpack/methods/sparse_coding/sparse_coding.hpp>

#endif
