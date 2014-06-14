/**
 * @file lars_main.cpp
 * @author Nishant Mehta
 *
 * Executable for LARS.
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
#include <mlpack/core.hpp>

#include "lars.hpp"



using namespace arma;
using namespace std;
using namespace mlpack;
using namespace mlpack::regression;

int main(int argc, char* argv[])
{
  // Handle parameters,
  CLI::ParseCommandLine(argc, argv);

  double lambda1 = CLI::GetParam<double>("lambda1");
  double lambda2 = CLI::GetParam<double>("lambda2");
  bool useCholesky = CLI::HasParam("use_cholesky");

  // Load covariates.  We can avoid LARS transposing our data by choosing to not
  // transpose this data.
  const string matXFilename = CLI::GetParam<string>("input_file");
  mat matX;
  data::Load(matXFilename, matX, true, false);

  // Load responses.  The responses should be a one-dimensional vector, and it
  // seems more likely that these will be stored with one response per line (one
  // per row).  So we should not transpose upon loading.
  const string yFilename = CLI::GetParam<string>("responses_file");
  mat matY; // Will be a vector.
  data::Load(yFilename, matY, true, false);

  // Make sure y is oriented the right way.
  if (matY.n_rows == 1)
    matY = trans(matY);
  if (matY.n_cols > 1)
    Log::Fatal << "Only one column or row allowed in responses file!" << endl;

  if (matY.n_elem != matX.n_rows)
    Log::Fatal << "Number of responses must be equal to number of rows of X!"
        << endl;

  // Do LARS.
  LARS lars(useCholesky, lambda1, lambda2);
  vec beta;
  lars.Regress(matX, matY.unsafe_col(0), beta, false /* do not transpose */);

  const string betaFilename = CLI::GetParam<string>("output_file");
  beta.save(betaFilename, raw_ascii);
}
