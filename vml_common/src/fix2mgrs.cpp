#include "vml_common/fix2mgrs.hpp"

#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/UTMUPS.hpp>

namespace vml_common
{
Eigen::Vector3d fix2Mgrs(const sensor_msgs::msg::NavSatFix & msg)
{
  using namespace GeographicLib;
  double x, y;
  int zone;
  bool northp;
  std::string mgrs;
  UTMUPS::Forward(msg.latitude, msg.longitude, zone, northp, x, y);

  const int DIGIT = 7;
  MGRS::Forward(zone, northp, x, y, msg.latitude, DIGIT, mgrs);

  double local_x = std::stoi(mgrs.substr(5, DIGIT)) * std::pow(10, 5 - DIGIT);
  double local_y = std::stoi(mgrs.substr(5 + DIGIT, DIGIT)) * std::pow(10, 5 - DIGIT);
  return {local_x, local_y, 0};
}
}  // namespace vml_common