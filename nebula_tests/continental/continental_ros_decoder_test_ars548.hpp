// Copyright 2024 TIER IV, Inc.
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

#ifndef NEBULA_ContinentalRosDecoderTestArs548_H
#define NEBULA_ContinentalRosDecoderTestArs548_H

#include <diagnostic_updater/diagnostic_updater.hpp>
#include <nebula_common/nebula_common.hpp>
#include <nebula_common/nebula_status.hpp>
#include <nebula_decoders/nebula_decoders_continental/decoders/continental_ars548_decoder.hpp>
#include <rclcpp/rclcpp.hpp>

#include <continental_msgs/msg/continental_ars548_detection_list.hpp>
#include <continental_msgs/msg/continental_ars548_object_list.hpp>
#include <nebula_msgs/msg/nebula_packets.hpp>

#include <gtest/gtest.h>
#include <yaml-cpp/node/node.h>

#include <memory>
#include <string>

namespace nebula
{
namespace ros
{
class ContinentalRosDecoderTest final : public rclcpp::Node  //, testing::Test
{
  std::shared_ptr<drivers::continental_ars548::ContinentalARS548Decoder> driver_ptr_;
  Status wrapper_status_;

  std::shared_ptr<drivers::continental_ars548::ContinentalARS548SensorConfiguration>
    sensor_cfg_ptr_;

  Status InitializeDriver(
    std::shared_ptr<drivers::continental_ars548::ContinentalARS548SensorConfiguration>
      sensor_configuration);

  Status GetParameters(
    drivers::continental_ars548::ContinentalARS548SensorConfiguration & sensor_configuration);

  void CheckResult(const std::string msg_as_string, const std::string & gt_path);

  void DetectionListCallback(
    std::unique_ptr<continental_msgs::msg::ContinentalArs548DetectionList> msg);

  void ObjectListCallback(std::unique_ptr<continental_msgs::msg::ContinentalArs548ObjectList> msg);

  void CompareNodes(const YAML::Node & node1, const YAML::Node & node2);

  static inline std::chrono::nanoseconds SecondsToChronoNanoSeconds(const double seconds)
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::duration<double>(seconds));
  }

public:
  explicit ContinentalRosDecoderTest(
    const rclcpp::NodeOptions & options, const std::string & node_name);

  void ReceiveScanMsgCallback(const nebula_msgs::msg::NebulaPackets::SharedPtr scan_msg);
  Status GetStatus();
  void ReadBag();

private:
  std::string bag_path_{};
  std::string storage_id_{};
  std::string format_{};
  std::string target_topic_{};
};

}  // namespace ros
}  // namespace nebula

#endif  // NEBULA_ContinentalRosDecoderTestArs548_H
