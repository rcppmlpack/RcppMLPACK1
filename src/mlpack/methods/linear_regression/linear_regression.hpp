/**
 * @file linear_regression.hpp
 * @author James Cline
 *
 * Simple least-squares linear regression.
 *
 * This file is part of MLPACK 1.0.8.
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
#ifndef __MLPACK_METHODS_LINEAR_REGRESSION_LINEAR_REGRESSION_HPP
#define __MLPACK_METHODS_LINEAR_REGRESSION_LINEAR_REGRESSION_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace regression /** Regression methods. */{

/**
 * A simple linear regression algorithm using ordinary least squares.
 * Optionally, this class can perform ridge regression, if the lambda parameter
 * is set to a number greater than zero.
 */
class LinearRegression {
public:
	/**
	 * Creates the model.
	 *
	 * @param predictors X, matrix of data points to create B with.
	 * @param responses y, the measured data for each point in X
	 */
	LinearRegression(const arma::mat& predictors, const arma::colvec& responses,
			const double lambda) :
			lambda(lambda) {
		/*
		 * We want to calculate the a_i coefficients of:
		 * \sum_{i=0}^n (a_i * x_i^i)
		 * In order to get the intercept value, we will add a row of ones.
		 */

		// We store the number of rows and columns of the predictors.
		// Reminder: Armadillo stores the data transposed from how we think of it,
		//           that is, columns are actually rows (see: column major order).
		const size_t nCols = predictors.n_cols;

		// Here we add the row of ones to the predictors.
		arma::mat p;
		if (lambda == 0.0) {
			p.set_size(predictors.n_rows + 1, nCols);
			p.submat(1, 0, p.n_rows - 1, nCols - 1) = predictors;
			p.row(0).fill(1);
		} else {
			// Add the identity matrix to the predictors (this is equivalent to ridge
			// regression).  See http://math.stackexchange.com/questions/299481/ for
			// more information.
			p.set_size(predictors.n_rows + 1, nCols + predictors.n_rows + 1);
			p.submat(1, 0, p.n_rows - 1, nCols - 1) = predictors;
			p.row(0).subvec(0, nCols - 1).fill(1);
			p.submat(0, nCols, p.n_rows - 1, nCols + predictors.n_rows) = lambda
					* arma::eye < arma::mat
					> (predictors.n_rows + 1, predictors.n_rows + 1);
		}

		// We compute the QR decomposition of the predictors.
		// We transpose the predictors because they are in column major order.
		arma::mat Q, R;
		arma::qr(Q, R, arma::trans(p));

		// We compute the parameters, B, like so:
		// R * B = Q^T * responses
		// B = Q^T * responses * R^-1
		// If lambda > 0, then we must add a bunch of empty responses.
		if (lambda == 0.0) {
			arma::solve(parameters, R, arma::trans(Q) * responses);
		} else {
			// Copy responses into larger vector.
			arma::vec r(nCols + predictors.n_rows + 1);
			r.subvec(0, nCols - 1) = responses;
			r.subvec(nCols, nCols + predictors.n_rows).fill(0);

			arma::solve(parameters, R, arma::trans(Q) * r);
		}
	}

	/**
	 * Initialize the model from a file.
	 *
	 * @param filename the name of the file to load the model from.
	 */
	LinearRegression(const std::string& filename) :
			lambda(0.0) {
		data::Load(filename, parameters, true);
	}

	/**
	 * Copy constructor.
	 *
	 * @param linearRegression the other instance to copy parameters from.
	 */
	LinearRegression(const LinearRegression& linearRegression) :
			parameters(linearRegression.parameters), lambda(
					linearRegression.lambda) { /* Nothing to do. */
	}

	/**
	 * Empty constructor.
	 */
	LinearRegression() {
	}

	/**
	 * Calculate y_i for each data point in points.
	 *
	 * @param points the data points to calculate with.
	 * @param predictions y, will contain calculated values on completion.
	 */
	void Predict(const arma::mat& points, arma::vec& predictions) const {
		// We want to be sure we have the correct number of dimensions in the dataset.
		Log::Assert(points.n_rows == parameters.n_rows - 1);

		// Get the predictions, but this ignores the intercept value (parameters[0]).
		predictions = arma::trans(
				arma::trans(parameters.subvec(1, parameters.n_elem - 1))
						* points);

		// Now add the intercept.
		predictions += parameters(0);
	}

	/**
	 * Calculate the L2 squared error on the given predictors and responses using
	 * this linear regression model.  This calculation returns
	 *
	 * \f[
	 * (1 / n) * \| y - X B \|^2_2
	 * \f]
	 *
	 * where \f$ y \f$ is the responses vector, \f$ X \f$ is the matrix of
	 * predictors, and \f$ B \f$ is the parameters of the trained linear
	 * regression model.
	 *
	 * As this number decreases to 0, the linear regression fit is better.
	 *
	 * @param predictors Matrix of predictors (X).
	 * @param responses Vector of responses (y).
	 */
	double ComputeError(const arma::mat& predictors,
			const arma::vec& responses) const {
		// Get the number of columns and rows of the dataset.
		const size_t nCols = predictors.n_cols;
		const size_t nRows = predictors.n_rows;

		// Ensure that we have the correct number of dimensions in the dataset.
		if (nRows != parameters.n_rows - 1) {
			Log::Fatal
					<< "The test data must have the same number of columns as the "
							"training file." << std::endl;
		}

		// Calculate the differences between actual responses and predicted responses.
		// We must also add the intercept (parameters(0)) to the predictions.
		arma::vec temp = responses
				- arma::trans(
						(arma::trans(
								parameters.subvec(1, parameters.n_elem - 1))
								* predictors) + parameters(0));

		const double cost = arma::dot(temp, temp) / nCols;

		return cost;
	}

	//! Return the parameters (the b vector).
	const arma::vec& Parameters() const {
		return parameters;
	}
	//! Modify the parameters (the b vector).
	arma::vec& Parameters() {
		return parameters;
	}

	//! Return the Tikhonov regularization parameter for ridge regression.
	double Lambda() const {
		return lambda;
	}
	//! Modify the Tikhonov regularization parameter for ridge regression.
	double& Lambda() {
		return lambda;
	}

private:
	/**
	 * The calculated B.
	 * Initialized and filled by constructor to hold the least squares solution.
	 */
	arma::vec parameters;

	/**
	 * The Tikhonov regularization parameter for ridge regression (0 for linear
	 * regression).
	 */
	double lambda;
};

}
;
// namespace linear_regression
}
;
// namespace mlpack

#endif // __MLPACK_METHODS_LINEAR_REGRESSCLIN_HPP
