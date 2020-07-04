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

#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

#include <prbt_hardware_support/benchmark_dummy_test.h>

using namespace prbt_hardware_support;

//class MyBenchmarkFixture : public ::benchmark::Fixture
//{
// public:
//  void SetUp(const ::benchmark::State& state)
//  {
//    // Do something
//  }

//  void TearDown(const ::benchmark::State& state)
//  {
//    // Do something
//  }
//}

//BENCHMARK_F(MyBenchmarkFixture, testBenchmarkDummyFunc)(benchmark::State &st)
//{
//  myFuncToBenchmark();
//}

//BENCHMARK_MAIN();

void BM_BenchmarkMyFuncToBenchmark(benchmark::State& state)
{
  for (auto _ : state)
  {
    myFuncToBenchmark();
  }
}

BENCHMARK(BM_BenchmarkMyFuncToBenchmark);

TEST(MyTest, testMyFunc)
{
  EXPECT_TRUE(myFuncToBenchmark());
}

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  benchmark::Initialize(&argc, argv);

  // Run gtests
  int result = RUN_ALL_TESTS();

  if (result == 0)
  {
    std::cout << "\nRunning benchmarks:\n";
    benchmark::RunSpecifiedBenchmarks();
  }

  return result;
}

