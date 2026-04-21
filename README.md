# pointcloud_to_pcd

Provides a ROS 2 node that saves incoming `sensor_msgs/PointCloud2` messages as PCD files for offline processing and dataset collection.

## Output Structure

All PCD files are saved inside the package under:

```
<base_path>/pcd/<experiment_name>/
```

Where `base_path` is defined inside the package (global configuration) and
`experiment_name` is provided by the user at launch time.

## Usage
```
ros2 launch pointcloud_to_pcd pointcloud_to_pcd.launch.py experiment_name:=NAME
```
Optionally, override the `input_topic` (defaults to `/map`).

## Viewing Raw PCD Files

Install PCL tools:
```
sudo apt install pcl-tools libpcl-dev
```
View a file:
```
pcl_viewer FILE_NAME.pcd
```

## Notes
Directories are created automatically if they do not exist.
Each experiment should use a unique `experiment_name` to avoid overwriting data.