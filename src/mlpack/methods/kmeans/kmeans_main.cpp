/**
 * @file kmeans_main.cpp
 * @author Ryan Curtin
 *
 * Executable for running K-Means.
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

#include "kmeans.hpp"
#include "allow_empty_clusters.hpp"
#include "refined_start.hpp"

using namespace mlpack;
using namespace mlpack::kmeans;
using namespace std;

int main(int argc, char** argv)
{
  CLI::ParseCommandLine(argc, argv);

  // Initialize random seed.
  if (CLI::GetParam<int>("seed") != 0)
    math::RandomSeed((size_t) CLI::GetParam<int>("seed"));
  else
    math::RandomSeed((size_t) std::time(NULL));

  // Now do validation of options.
  const string inputFile = CLI::GetParam<string>("inputFile");
  const int clusters = CLI::GetParam<int>("clusters");
  if (clusters < 1)
  {
    Log::Fatal << "Invalid number of clusters requested (" << clusters << ")! "
        << "Must be greater than or equal to 1." << endl;
  }

  const int maxIterations = CLI::GetParam<int>("max_iterations");
  if (maxIterations < 0)
  {
    Log::Fatal << "Invalid value for maximum iterations (" << maxIterations <<
        ")! Must be greater than or equal to 0." << endl;
  }

  const double overclustering = CLI::GetParam<double>("overclustering");
  if (overclustering < 1)
  {
    Log::Fatal << "Invalid value for overclustering (" << overclustering <<
        ")! Must be greater than or equal to 1." << endl;
  }

  // Make sure we have an output file if we're not doing the work in-place.
  if (!CLI::HasParam("in_place") && !CLI::HasParam("output_file"))
  {
    Log::Fatal << "--outputFile not specified (and --in_place not set)."
        << endl;
  }

  // Load our dataset.
  arma::mat dataset;
  data::Load(inputFile, dataset, true); // Fatal upon failure.

  // Now create the KMeans object.  Because we could be using different types,
  // it gets a little weird...
  arma::Col<size_t> assignments;
  arma::mat centroids;

  const bool initialCentroidGuess = CLI::HasParam("initial_centroids");
  // Load initial centroids if the user asked for it.
  if (initialCentroidGuess)
  {
    string initialCentroidsFile = CLI::GetParam<string>("initial_centroids");
    data::Load(initialCentroidsFile, centroids, true);

    if (CLI::HasParam("refined_start"))
      Log::Warn << "Initial centroids are specified, but will be ignored "
          << "because --refined_start is also specified!" << endl;
    else
      Log::Info << "Using initial centroid guesses from '" <<
          initialCentroidsFile << "'." << endl;
  }

  if (CLI::HasParam("allow_empty_clusters"))
  {
    if (CLI::HasParam("refined_start"))
    {
      const int samplings = CLI::GetParam<int>("samplings");
      const double percentage = CLI::GetParam<int>("percentage");

      if (samplings < 0)
        Log::Fatal << "Number of samplings (" << samplings << ") must be "
            << "greater than 0!" << endl;
      if (percentage <= 0.0 || percentage > 1.0)
        Log::Fatal << "Percentage for sampling (" << percentage << ") must be "
            << "greater than 0.0 and less than or equal to 1.0!" << endl;

      KMeans<metric::SquaredEuclideanDistance, RefinedStart, AllowEmptyClusters>
          k(maxIterations, overclustering, metric::SquaredEuclideanDistance(),
          RefinedStart(samplings, percentage));

      Timer::Start("clustering");
//      if (CLI::HasParam("fast_kmeans"))
//        k.FastCluster(dataset, clusters, assignments);
//      else
      k.Cluster(dataset, clusters, assignments, centroids);
      Timer::Stop("clustering");
    }
    else
    {
      KMeans<metric::SquaredEuclideanDistance, RandomPartition,
          AllowEmptyClusters> k(maxIterations, overclustering);

      Timer::Start("clustering");
//      if (CLI::HasParam("fast_kmeans"))
//        k.FastCluster(dataset, clusters, assignments);
//      else
      k.Cluster(dataset, clusters, assignments, centroids, false,
          initialCentroidGuess);
      Timer::Stop("clustering");
    }
  }
  else
  {
    if (CLI::HasParam("refined_start"))
    {
      const int samplings = CLI::GetParam<int>("samplings");
      const double percentage = CLI::GetParam<int>("percentage");

      if (samplings < 0)
        Log::Fatal << "Number of samplings (" << samplings << ") must be "
            << "greater than 0!" << endl;
      if (percentage <= 0.0 || percentage > 1.0)
        Log::Fatal << "Percentage for sampling (" << percentage << ") must be "
            << "greater than 0.0 and less than or equal to 1.0!" << endl;

      KMeans<metric::SquaredEuclideanDistance, RefinedStart, AllowEmptyClusters>
          k(maxIterations, overclustering, metric::SquaredEuclideanDistance(),
          RefinedStart(samplings, percentage));

      Timer::Start("clustering");
//      if (CLI::HasParam("fast_kmeans"))
//        k.FastCluster(dataset, clusters, assignments);
//      else
        k.Cluster(dataset, clusters, assignments, centroids);
      Timer::Stop("clustering");
    }
    else
    {
      KMeans<> k(maxIterations, overclustering);

      Timer::Start("clustering");
//      if (CLI::HasParam("fast_kmeans"))
//        k.FastCluster(dataset, clusters, assignments);
//      else
        k.Cluster(dataset, clusters, assignments, centroids, false,
            initialCentroidGuess);
      Timer::Stop("clustering");
    }
  }

  // Now figure out what to do with our results.
  if (CLI::HasParam("in_place"))
  {
    // Add the column of assignments to the dataset; but we have to convert them
    // to type double first.
    arma::vec converted(assignments.n_elem);
    for (size_t i = 0; i < assignments.n_elem; i++)
      converted(i) = (double) assignments(i);

    dataset.insert_rows(dataset.n_rows, trans(converted));

    // Save the dataset.
    data::Save(inputFile, dataset);
  }
  else
  {
    if (CLI::HasParam("labels_only"))
    {
      // Save only the labels.
      string outputFile = CLI::GetParam<string>("output_file");
      arma::Mat<size_t> output = trans(assignments);
      data::Save(outputFile, output);
    }
    else
    {
      // Convert the assignments to doubles.
      arma::vec converted(assignments.n_elem);
      for (size_t i = 0; i < assignments.n_elem; i++)
        converted(i) = (double) assignments(i);

      dataset.insert_rows(dataset.n_rows, trans(converted));

      // Now save, in the different file.
      string outputFile = CLI::GetParam<string>("output_file");
      data::Save(outputFile, dataset);
    }
  }

  // Should we write the centroids to a file?
  if (CLI::HasParam("centroid_file"))
    data::Save(CLI::GetParam<std::string>("centroid_file"), centroids);
}

