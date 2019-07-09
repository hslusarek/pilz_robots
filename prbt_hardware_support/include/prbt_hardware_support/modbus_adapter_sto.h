/*
 * Copyright (c) 2019 Pilz GmbH & Co. KG
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

#ifndef MODBUS_ADAPTER_STO_H
#define MODBUS_ADAPTER_STO_H

#include <memory>

#include <ros/ros.h>

#include <prbt_hardware_support/ModbusMsgInStamped.h>
#include <prbt_hardware_support/filter_pipeline.h>
#include <prbt_hardware_support/modbus_api_spec.h>
#include <prbt_hardware_support/adapter_sto.h>

namespace prbt_hardware_support
{

/**
 * @brief Listens to the modbus_read topic and reacts to changes to the STO
 * state.
 */
class ModbusAdapterSto : public AdapterSto
{
public:
  ModbusAdapterSto(ros::NodeHandle& nh, const ModbusApiSpec& api_spec);
  virtual ~ModbusAdapterSto() = default;

private:
  /**
   * @brief Called whenever a new modbus messages arrives.
   *
   * @note Filters like for example the UpdateFilter can restrict
   * the number of incoming messages.
   *
   * @note A STOP1 is triggered in case:
   *    - of a disconnect from the modbus server,
   *    - the modbus message does not contain the expected registers,
   *    - the modbus API version is incorrect,
   *    - the STO state changes to false.
   */
  void modbusMsgCallback(const ModbusMsgInStampedConstPtr& msg_raw);

private:
  const ModbusApiSpec api_spec_;
  std::unique_ptr<FilterPipeline> filter_pipeline_;

private:
  static constexpr unsigned int MODBUS_API_VERSION_REQUIRED {2};
};


} // namespace prbt_hardware_support
#endif // MODBUS_ADAPTER_STO_H
