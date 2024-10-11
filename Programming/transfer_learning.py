import torch
import cv2
import pyrealsense2 as rs
import numpy as np
from ultralytics import YOLO

# Testing without freezing
model = YOLO('yolov8s.pt')
model.to('cuda')

model.train(data="insert_data.yaml", patience=100)