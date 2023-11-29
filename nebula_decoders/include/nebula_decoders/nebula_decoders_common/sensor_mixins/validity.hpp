#pragma once

#include "nebula_decoders/nebula_decoders_common/util.hpp"

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace nebula
{
namespace drivers
{
namespace point_accessors
{

template <typename SensorT>
struct ValidityMixin
{
  virtual bool isValid(
    const SensorT::packet_t & packet, const size_t block_id, const size_t unit_id) = 0;
};

template <typename SensorT>
struct NonZeroDistanceIsValidMixin : public ValidityMixin<SensorT>
{
  /// @brief Performs a rudimentary check to see if the point is valid.
  /// This mixin considers a point valid if its distance is non-zero.
  bool isValid(
    const SensorT::packet_t & packet, const size_t block_id, const size_t unit_id) override
  {
    const auto * unit = getUnit(packet, block_id, unit_id);
    return getFieldValue(unit->distance) != 0;
  }
};

}  // namespace point_accessors
}  // namespace drivers
}  // namespace nebula