INTEL REALSENSE DEPTH D435 SETUP
----
----
WINDOWS:
---
1. Download the SDK which is official for Windows
   https://github.com/IntelRealSense/librealsense/releases/download/v2.56.1/Intel.RealSense.SDK-WIN10-2.56.1.7154-beta.exe
2. Run the installer
3. After connecting the camera to the computer, the camera should show up on the Intel RealSense Viewer

Python:
---
1. As of 09/30/2024, pyrealsense2 is not supported with python 3.12. 
Need to be working with 3.11 or less. 
To use an older python version, use "pyenv" on mac and linux and "pyenv-win" on windows.
I am currently using Python 3.11.9.
2. Once you have working version of python "installed",
install pyrealsense2 "pip install pyrealsense2"

---
YOLO
---
---
1. Clone repository for desired YOLO model
2. To install all requirements with "pip install -r requirements.txt"
3. Ensure correct version of "torch" and "torchvision" are installed to work with Nvidia CUDA
4. Ensure script is using the GPU