/*
 * Copyright (c) 2020 Pilz GmbH & Co. KG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

#include <prbt_hardware_support/benchmark_dummy_test.h>

using namespace prbt_hardware_support;

/**
 * @brief Stores the results from the benchmark tests allowing for a
 * programmatic evaluation of the results.
 */
class StoreResultsReporter : public benchmark::ConsoleReporter
{
 public:
  virtual void ReportRuns(const std::vector<Run>& report);

public:
  const std::vector<Run>& getResults();

private:
  std::vector<Run> benchmark_results_;
};

void StoreResultsReporter::ReportRuns(const std::vector<Run>& report)
{
  benchmark_results_.insert(benchmark_results_.end(), begin(report), end(report));
  // Call base class to still show results on console
  ConsoleReporter::ReportRuns(report);
}

const std::vector<benchmark::BenchmarkReporter::Run>& StoreResultsReporter::getResults()
{
  return benchmark_results_;
}

void BM_BenchmarkMyFuncToBenchmark(benchmark::State& state)
{
  for (auto _ : state)
  {
    myFuncToBenchmark();
  }
}

BENCHMARK(BM_BenchmarkMyFuncToBenchmark);

/**
 * @brief Runs the benchmark tests and programmatically evaluates that the execution time does not exceed a certain
 * value via gtest macros.
 */
TEST(MyTest, runAndCheckBenchmarks)
{
  StoreResultsReporter reporter;

  // Run benchmark tests and use specialized reporter to store the benchmark results for programmatic evaluation
  // via gtest macros.
  benchmark::RunSpecifiedBenchmarks(&reporter);

  for (auto const& run : reporter.getResults())
  {
    if (run.benchmark_name() == "BM_BenchmarkMyFuncToBenchmark")
    {
      EXPECT_LE(run.GetAdjustedCPUTime(), 400.0) << "Execution time exceeded expectation.";
    }
  }
}

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  benchmark::Initialize(&argc, argv);

  return RUN_ALL_TESTS();
}

