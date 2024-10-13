Logbook
---
---

10/12/2024
---
- looked for where i saw yolo architecture which is here [https://www.datacamp.com/blog/yolo-object-detection-explained]()
- trying out roboflow
- created training dataset with roboflow off of 31 images of the robot arm, labelled photos with robot arm and monitor, roboflow allowed augementation of data set to get training data up to 48 images
- exported training file, now to try to train pretrained v8s with it
- found this and going to follow it for tutorial, [https://blog.roboflow.com/how-to-train-yolov8-on-a-custom-dataset/]()
- above tutorial was not for a python script i think
- found a video tutorial from ultralytics, https://www.youtube.com/watch?v=LNwODJXcvt4, going to try to train from terminal based on the code line they use
- used this to train,didn't take too long (.028 hours), used gpu, results saved to runs/detect/train4


    yolo task=detect mode=train model=yolov8s.pt data=data.yaml epochs=20 imgsz=640 device=0

  
- looks like it has good results for detecting robotic arm
- now going to validate (need to copy best.pt into programming because giving path was not working)


    yolo task=detect mode=val model=best.pt data=data.yaml device=0

  
- now going to test model with test images
- something was wrong in code i inputted and it just used two of the generic photos that yolo has
  which were zidane and bus. it didn't recognize any of them so i think this may have created a full new model off of the small data i had
- tried it on one of the test images and it did not work either, didn't show any boxes at all
- going to try a live detection test just in room to see if it is custom with pretrained or custom based off my dataset
- live test showed showed no boxes or object detection, pretty sure i just trained new model from scratch
- after reading some of the discussion on this [https://www.reddit.com/r/computervision/comments/16q1csv/is_it_possible_to_add_new_classes_to_pretrained/]()
  I think that if we want to add new classes, robotic-arm or whatever, we will need to still train on a full dataset containing coco and our new object data
- depending on our use case, we may be able to train new model on just our new data for very specific objects
- need to look into how long it would take to retrain on COCO and new data, probably need more photos of robotic-arm
- at lab, trained model would not recognize robot arm or monitor
- tried yolo v11s, works well
- going to try to get custom trained dataset to detect things before i try to use coco model with extra pretrained images
- took 130 photos of keyboards, robot arm, monitors, now going to label and make into dataset, prob need to train for more than 20 epochs
- labelled 133 photos with keyboard, robot arm, monitor, and mouse, created training set with augmentation for a total of 379 images
- trying to train in lab, can't access path variable without adminstrative position, trying virtual environment that pycharm gave option to, worked
- training on new dataset for 50 epochs, took .094 hours, results look stronger, now to try
- new trained dataset works well, might need to augment to flip photos around to give it a better chance at recognizing things upside down.
  I did notice that it doesn't work at all angles.
- still not exactly sure what this is doing, is it transfer learning but only having outputs for the classes that the custom dataset has or training from scratch
- for now i think this proves that we can train the model to detect specific objects using roboflow for labelling and with enough images

10/11/2024
---
- trying to get labelImg working
- python would not recognize it and couldnt figure out how to add it to path
- eventually found the .exe file in files and ran it from that but it would crash
  after a minute or so
- had weekly meeting - learned about roboflow

10/10/2024
---
- took 31 images of robot arm for transfer learning test
- watched some tutorials on how to train on custom data sets for YOLO
- did some research on how transfer learning freezing would work

Before 10/10/2024 (generally, at least what I can remember)
---
- got realsense camera working on python with pyrealsense2, cv_test.py
- checked depth readings, pretty accurate 
- got yolo v5 working with camera based on ultralytics github and chatgpt information, detection_test.py
- started setup.md for how to get stuff started
