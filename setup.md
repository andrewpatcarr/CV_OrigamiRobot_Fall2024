SETUP
---
---
This has all the info for setting up various CV models, cameras and any other necessary devices or software


---
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
install pyrealsense2 with:


    pip install pyrealsense2


MATLAB:
---
...

---
GPU
---
---
A GPU is necessary to run advanced Neural Network CV models.
A GPU can complete many matrix calculations in parallel which allows it to process ML models quickly and efficiently.


---
YOLO
---
---
1. Clone repository for desired YOLO model. For example (YOLOv5):


    git clone https://github.com/ultralytics/yolov5.git
2. To install all requirements with:
    
    
    "pip install -r requirements.txt"
3. Ensure correct version of "torch" and "torchvision" are installed to work with Nvidia CUDA using:


    import torch
    import torchvision
    print(torch.__version__)  # Check PyTorch version
    print(torchvision.__version__)  # Check Torchvision version
This should output something of the form " x.x.x+cu118 "

If it outputs "x.x.x+cpu" then uninstall torch and torchvision, and reinstall with:


    pip uninstall torch torchvision torchaudio
    pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118
*torchaudio may or may not be necessary
4. Ensure script is using the GPU with following:


    import torch
    import torchvision

    # Check if CUDA is available
    print(torch.cuda.is_available())

which should output True 
5. At this point, YOLO should be installed and ready for use from python script.