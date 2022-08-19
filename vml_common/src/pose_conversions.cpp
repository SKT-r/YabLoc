#include "vml_common/pose_conversions.hpp"

#include <eigen3/Eigen/Geometry>

namespace vml_common
{
geometry_msgs::msg::Pose affine2Pose(const Eigen::Affine3f & affine)
{
  geometry_msgs::msg::Pose pose;
  Eigen::Vector3f pos = affine.translation();
  Eigen::Quaternionf ori(affine.rotation());
  pose.position.x = pos.x();
  pose.position.y = pos.y();
  pose.position.z = pos.z();
  pose.orientation.w = ori.w();
  pose.orientation.x = ori.x();
  pose.orientation.y = ori.y();
  pose.orientation.z = ori.z();
  return pose;
}

Eigen::Affine3f pose2Affine(const geometry_msgs::msg::Pose & pose)
{
  const auto pos = pose.position;
  const auto ori = pose.orientation;
  Eigen::Translation3f t(pos.x, pos.y, pos.z);
  Eigen::Quaternionf q(ori.w, ori.x, ori.y, ori.z);
  return t * q;
}

Sophus::SE3f pose2Se3(const geometry_msgs::msg::Pose & pose)
{
  auto ori = pose.orientation;
  auto pos = pose.position;
  Eigen::Quaternionf q(ori.w, ori.x, ori.y, ori.z);
  Eigen::Vector3f t(pos.x, pos.y, pos.z);
  return {q, t};
}

geometry_msgs::msg::Pose se32Pose(const Sophus::SE3f & se3f)
{
  geometry_msgs::msg::Pose pose;
  Eigen::Vector3f pos = se3f.translation();
  Eigen::Quaternion ori = se3f.so3().unit_quaternion();
  pose.position.x = pos.x();
  pose.position.y = pos.y();
  pose.position.z = pos.z();
  pose.orientation.w = ori.w();
  pose.orientation.x = ori.x();
  pose.orientation.y = ori.y();
  pose.orientation.z = ori.z();
  return pose;
}
}  // namespace vml_common