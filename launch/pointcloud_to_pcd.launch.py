from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node


def generate_launch_description():

    input_topic = LaunchConfiguration('input_topic')
    experiment_name = LaunchConfiguration('experiment_name')

    output_directory = PathJoinSubstitution([
        '/home/robot/ragnarhorn/src/pointcloud_to_pcd',
        'pcd',
        experiment_name
    ])

    return LaunchDescription([

        DeclareLaunchArgument(
            'input_topic',
            default_value='/map'
        ),

        DeclareLaunchArgument(
            'experiment_name',
            description='Unique experiment name to create output directory under pcd/',
        ),

        Node(
            package='pointcloud_to_pcd',
            executable='pointcloud_to_pcd',
            name='pointcloud_to_pcd',
            output='screen',
            parameters=[{
                'input_topic': input_topic,
                'output_directory': output_directory
            }]
        )
    ])