import cv2
import pyrealsense2 as rs
import numpy as np


point = (0,0)
def show_distance(event, x, y, args, params):
    global point
    point = (x,y)

# Initialize

pipeline = rs.pipeline()
config = rs.config()

#pipeline_wrapper = rs.pipeline_wrapper(pipeline)

config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

pipeline_profile = pipeline.start(config)

cv2.namedWindow("RealSense Color and Depth")
cv2.setMouseCallback("RealSense Color and Depth", show_distance)

while True:

    frames = pipeline.wait_for_frames(5000)
    depth_frame = frames.get_depth_frame()
    color_frame = frames.get_color_frame()

    if not depth_frame or not color_frame:
        continue

    depth_image = np.asanyarray(depth_frame.get_data())
    color_image = np.asanyarray(color_frame.get_data())

    depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)

    full_images = np.hstack((color_image, depth_colormap))
    cv2.circle(full_images, point, 4, (0, 0, 255))
    distance = depth_frame[point[1], point[0]]

    cv2.putText(full_images, "{}mm".format(distance), (point[0], point[1]-20), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 0), 2)
    # Show images
    cv2.imshow('RealSense Color and Depth', full_images)
    #cv2.imshow("Color Image", color_image)
    #cv2.imshow("Depth Image", depth_colormap)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

pipeline.stop()

cv2.destroyAllWindows()