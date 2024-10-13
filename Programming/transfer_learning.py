import torch
import cv2
import pyrealsense2 as rs
import numpy as np
from ultralytics import YOLO

# Testing without freezing
model = YOLO('yolov8s.pt')
model.to('cuda')

if __name__ == '__main__':
    model.train(data="data.yaml", epochs=50, imgsz=640)