// Copyright 2023 Map IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NEBULA_HesaiRosOfflineExtractBag_H
#define NEBULA_HesaiRosOfflineExtractBag_H

#include <diagnostic_updater/diagnostic_updater.hpp>
#include <nebula_common/hesai/hesai_common.hpp>
#include <nebula_common/nebula_common.hpp>
#include <nebula_common/nebula_status.hpp>
#include <nebula_decoders/nebula_decoders_hesai/hesai_driver.hpp>
#include <nebula_ros/common/parameter_descriptors.hpp>
#include <rclcpp/rclcpp.hpp>

#include <nebula_msgs/msg/nebula_packet.hpp>
#include <nebula_msgs/msg/nebula_packets.hpp>
#include <pandar_msgs/msg/pandar_packet.hpp>
#include <pandar_msgs/msg/pandar_scan.hpp>

#include <memory>
#include <string>

namespace nebula
{
namespace ros
{
class HesaiRosOfflineExtractBag final : public rclcpp::Node
{
  std::shared_ptr<drivers::HesaiDriver> driver_ptr_;
  Status wrapper_status_;

  std::shared_ptr<drivers::HesaiCalibrationConfiguration> calibration_cfg_ptr_;
  std::shared_ptr<drivers::SensorConfigurationBase> sensor_cfg_ptr_;
  std::shared_ptr<drivers::HesaiCorrection> correction_cfg_ptr_;

  Status InitializeDriver(
    std::shared_ptr<drivers::SensorConfigurationBase> sensor_configuration,
    std::shared_ptr<drivers::HesaiCalibrationConfigurationBase> calibration_configuration);

  Status GetParameters(
    drivers::HesaiSensorConfiguration & sensor_configuration,
    drivers::HesaiCalibrationConfiguration & calibration_configuration,
    drivers::HesaiCorrection & correction_configuration);

  static inline std::chrono::nanoseconds SecondsToChronoNanoSeconds(const double seconds)
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::duration<double>(seconds));
  }

public:
  explicit HesaiRosOfflineExtractBag(
    const rclcpp::NodeOptions & options, const std::string & node_name);

  Status GetStatus();
  Status ReadBag();

private:
  std::string bag_path;
  std::string storage_id;
  std::string out_path;
  std::string format;
  std::string target_topic;
  std::string correction_file_path;
  int out_num;
  int skip_num;
  bool only_xyz;
};

}  // namespace ros
}  // namespace nebula

#endif  // NEBULA_HesaiRosOfflineExtractBag_H
