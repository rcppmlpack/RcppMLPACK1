/**
 * @file arma_traits.hpp
 * @author Ryan Curtin
 *
 * Some traits used for template metaprogramming (SFINAE) with Armadillo types.
 *
 * This file is part of MLPACK 1.0.10.
 *
 * MLPACK is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * MLPACK is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details (LICENSE.txt).
 *
 * You should have received a copy of the GNU General Public License along with
 * MLPACK.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __MLPACK_CORE_UTIL_ARMA_TRAITS_HPP
#define __MLPACK_CORE_UTIL_ARMA_TRAITS_HPP

// Structs have public members by default (that's why they are chosen over
// classes).

/**
 * If value == true, then VecType is some sort of Armadillo vector or subview.
 * You might use this struct like this:
 *
 * @code
 * // Only accepts VecTypes that are actually Armadillo vector types.
 * template<typename VecType>
 * void Function(const VecType& argumentA,
 *               typename boost::enable_if<IsVector<VecType> >* = 0);
 * @endcode
 *
 * The use of the enable_if object allows the compiler to instantiate Function()
 * only if VecType is one of the Armadillo vector types.  It has a default
 * argument because it isn't meant to be used in either the function call or the
 * function body.
 */
template<typename VecType>
struct IsVector
{
  const static bool value = false;
};

// Commenting out the first template per case, because 
//Visual Studio doesn't like this instantiaion pattern (error C2910).
//template<>
template<typename eT>
struct IsVector<arma::Col<eT> >
{
  const static bool value = true;
};

//template<>
template<typename eT>
struct IsVector<arma::SpCol<eT> >
{
  const static bool value = true;
};

//template<>
template<typename eT>
struct IsVector<arma::Row<eT> >
{
  const static bool value = true;
};

//template<>
template<typename eT>
struct IsVector<arma::SpRow<eT> >
{
  const static bool value = true;
};

//template<>
template<typename eT>
struct IsVector<arma::subview_col<eT> >
{
  const static bool value = true;
};

//template<>
template<typename eT>
struct IsVector<arma::subview_row<eT> >
{
  const static bool value = true;
};

#if ((ARMA_VERSION_MAJOR >= 10) || \
    ((ARMA_VERSION_MAJOR == 9) && (ARMA_VERSION_MINOR >= 869)))

  // Armadillo 9.869+ has SpSubview_col and SpSubview_row

  template<typename eT>
  struct IsVector<arma::SpSubview_col<eT> >
  {
    const static bool value = true;
  };

  template<typename eT>
  struct IsVector<arma::SpSubview_row<eT> >
  {
    const static bool value = true;
  };

#else

  // fallback for older Armadillo versions

  template<typename eT>
  struct IsVector<arma::SpSubview<eT> >
  {
    const static bool value = true;
  };

#endif

#endif
