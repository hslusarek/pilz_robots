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
#ifndef BENCHMARK_DUMMY_TEST_H
#define BENCHMARK_DUMMY_TEST_H

#include <sstream>

namespace prbt_hardware_support
{

static bool myFuncToBenchmark()
{
  const unsigned int a {3};
  const unsigned int b {4};

  const unsigned int result { a + b };

  std::ostringstream result_stream;
  result_stream << result;

  return true;
}

}

#endif // BENCHMARK_DUMMY_TEST_H
