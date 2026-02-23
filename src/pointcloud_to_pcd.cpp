#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

#include <filesystem>
#include <string>

// Create a new class that inherits from the rclcpp::Node class.
class PointCloudToPCDNode : public rclcpp::Node 
{
    public:
        // Define the constructor. 
        PointCloudToPCDNode() : Node("pointcloud_to_pcd"), file_index_(0) 
        {
            // DeclarepParameters
            this->declare_parameter<std::string>("input_topic", "/map");
            this->declare_parameter<std::string>("output_directory", "src/pointcloud_to_pcd/pcd");

            input_topic_ = this->get_parameter("input_topic").as_string();
            output_directory_ = this->get_parameter("output_directory").as_string();

            std::filesystem::create_directories(output_directory_);

            auto qos = rclcpp::QoS(rclcpp::KeepLast(1));
            qos.reliable();

            subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2> (
                input_topic_,
                qos,
                std::bind(&PointCloudToPCDNode::cloudCallback, this, std::placeholders::_1)
            );

            RCLCPP_INFO(get_logger(), "Subscribed to %s", input_topic_.c_str());
            RCLCPP_INFO(get_logger(), "Saving PCDs to %s", output_directory_.c_str());
        }

    private:
        // Define the pointcloud callback function. 
        void cloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
        {
            pcl::PointCloud<pcl::PointXYZ> cloud;
            pcl::fromROSMsg(*msg, cloud);

            RCLCPP_INFO(get_logger(), "Received a message.");

            if (cloud.empty()) {
                RCLCPP_WARN(get_logger(), "Received empty point cloud");
                return;
            }

            std::string filename = output_directory_ + "/cloud_" + std::to_string(file_index_) + ".pcd";

            int result;
            result = pcl::io::savePCDFileBinary(filename, cloud);

            if (result == 0) {
                RCLCPP_INFO(get_logger(), "Saved %zu points to %s", cloud.size(), filename.c_str());
                file_index_++;
            } 
            else {
                RCLCPP_ERROR(get_logger(), "Failed to save PCD file: %s", filename.c_str());
            }
        }

        std::string input_topic_;
        std::string output_directory_;

        size_t file_index_;

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointCloudToPCDNode>());
    rclcpp::shutdown();
    return 0;
}
