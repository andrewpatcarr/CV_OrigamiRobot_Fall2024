Regarding the camera:
---

- Realsense2 provides RGBD data
  - Distance is achieved using 2 cameras and triangularization (stereo vision). 
  It is equipped with infrared emitters which enables higher quality using IR dot patterns.
  - IR is not necessary for use but gives much more quality. 
  Outdoors or where there might be a high amount of IR, the dot patterns might not be seen or used.

Regarding Computer Vision:
---
- YOLO (You Only Look Once)
  - algorithm used for object detection
  - When using RGBD data, we need to add another input to the neural network
  - Works very generally by gridding image, bounding boxes, getting rid of boxes with not enough object, and non-max suppression(?).
