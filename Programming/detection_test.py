import torch
import cv2
import pyrealsense2 as rs
import numpy as np

# Load the YOLOv5 model (pre-trained on COCO dataset)
model = torch.hub.load('ultralytics/yolov5', 'yolov5s', pretrained=True)
model.to('cuda')
# Set up the RealSense pipeline
pipeline = rs.pipeline()
config = rs.config()

# Configure RealSense to use both RGB and depth streams
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start the pipeline
pipeline.start(config)

while True:
    # Wait for frames from the RealSense camera
    frames = pipeline.wait_for_frames()

    # Get the color and depth frames
    color_frame = frames.get_color_frame()
    depth_frame = frames.get_depth_frame()

    if not color_frame or not depth_frame:
        continue

    # Convert the RGB frameexit to a numpy array
    color_image = np.asanyarray(color_frame.get_data())

    # Perform object detection using YOLOv5
    results = model(color_image)

    # Extract detected objects
    detected_objects = results.pandas().xyxy[0]

    # Draw bounding boxes on the detected objects
    for index, row in detected_objects.iterrows():
        x1, y1, x2, y2, conf, cls, name = row[['xmin', 'ymin', 'xmax', 'ymax', 'confidence', 'class', 'name']]
        center_x = int((x1 + x2) / 2)
        center_y = int((y1 + y2) / 2)

        # Get depth at the center of the bounding box
        depth_value = depth_frame.get_distance(center_x, center_y)

        # Draw bounding box and label
        cv2.rectangle(color_image, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
        label = f"{name} {conf:.2f}, {depth_value:.2f}m"
        cv2.putText(color_image, label, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36, 255, 12), 2)

    # Display the RGB frame with detections
    cv2.imshow('YOLOv5 RealSense', color_image)

    # Break the loop on 'q' key press
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Stop the RealSense pipeline
pipeline.stop()
cv2.destroyAllWindows()
