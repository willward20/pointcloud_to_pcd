# pointcloud_to_pcd

## Usage
Run the `pointcloud_to_pcd` tool. This saves PCD files of incoming 
pointcloud messages (default ROS 2 topic is `/map`).

```
ros2 run pointcloud_to_pcd pointcloud_to_pcd
```

## Viewing Raw PCD Files
```
sudo apt install pcl-tools libpcl-dev
pcl_viewer FILE-NAME.pcd
```
