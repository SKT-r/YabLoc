#pragma once
#include <opencv4/opencv2/ximgproc/segmentation.hpp>
#include <rclcpp/rclcpp.hpp>

#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

namespace imgproc
{
class GraphSegment : public rclcpp::Node
{
public:
  using PointCloud2 = sensor_msgs::msg::PointCloud2;
  using Image = sensor_msgs::msg::Image;
  GraphSegment();

private:
  rclcpp::Subscription<Image>::SharedPtr sub_image_;
  rclcpp::Publisher<PointCloud2>::SharedPtr pub_cloud_;
  rclcpp::Publisher<Image>::SharedPtr pub_image_;
  cv::Ptr<cv::ximgproc::segmentation::GraphSegmentation> segmentation_;

  void callbackImage(const Image & msg);
  void execute(const PointCloud2 & msg1, const PointCloud2 & msg2);
  void publishImage(
    const cv::Mat & raw_image, const cv::Mat & segmentation, const rclcpp::Time & stamp);
};
}  // namespace imgproc