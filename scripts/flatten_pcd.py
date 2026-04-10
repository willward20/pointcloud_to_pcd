import numpy as np

def load_pcd_ascii(filename):
    header = []
    points = []

    with open(filename, 'r') as f:
        lines = f.readlines()

    data_start = 0
    for i, line in enumerate(lines):
        header.append(line)
        if line.strip().startswith("DATA"):
            data_start = i + 1
            break

    for line in lines[data_start:]:
        if line.strip():
            points.append([float(x) for x in line.strip().split()])

    return header, np.array(points)


def save_pcd_ascii(filename, header, points):
    with open(filename, 'w') as f:
        for line in header:
            f.write(line)
        for p in points:
            f.write(" ".join(map(str, p)) + "\n")


def flatten_z(input_file, output_file):
    header, points = load_pcd_ascii(input_file)

    # Set Z = 0
    points[:, 2] = 0.0

    save_pcd_ascii(output_file, header, points)


if __name__ == "__main__":
    path = "/home/robot/ragnarhorn/src/pointcloud_to_pcd/pcd"
    bag_name = "rosbag2_2026_04_08-16_25_26"
    flatten_z(f"{path}/{bag_name}/cloud_12_flattened.pcd", f"{path}/{bag_name}/cloud_12_flattened.pcd")