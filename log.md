Logbook
---
---


10/23/2024
---
- adjusted thickness of friction pad slider to 1.2 mm; tested and it was too thin; put it to 1.3 mm and tested; tight fit but still easy to get in, could be a hair too thin but for the strenfth of the servos and expected friction, it should be fine
- going to test on the arduino
- in the future, changing to dc motor with encoder, motor driver could increase performance drastically; especially for speed and accurate rotation
- in testing, one of the pulleys started to slip where the teeth connect. Going to try printing it out of nylon
- did some of a csu training i need to do
- nylon gear did not print accurately enough to have teeth; going to print another pla one for now
- 10k dataset uploaded to roboflow but none of the photos have annotations. Might need to reupload to roboflow again, cause it took a while and I went to sleep before
- going to get a test photo going, might get a better one from lab with many photos tomorrow

code used:


    yolo detect  predict model=yolo11n.pt source='"C:\Users\Andrew Carr\Downloads\CV_OrigamiRobot_Fall2024\Object Photos\comparison_image2.jpeg"'


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Image Comparison Table</title>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
        }
        th, td {
            border: 3px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #f2f2f2;
        }
        img {
            width: 300px; /* Adjust size as needed */
            height: auto;
        }
        .row-header {
            background-color: #f9f9f9;
            font-weight: bold;
        }
    </style>
</head>
<body>

<h2>Model Image Comparison</h2>

<table>
    <thead>
        <tr>
            <th>Image #</th> <!-- Empty cell for top-left corner -->
            <th>11s</th>
            <th>11n</th>
            <th>custom</th>
            <th>to be freeze</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th>1</th>
            <td><img src="Programming/runs_compare1/detect/predict/comparison_image1.jpeg" alt="Model 1 - Image 1"></td>
            <td><img src="Programming/runs_compare1/detect/predict2/comparison_image1.jpeg" alt="Model 2 - Image 1"></td>
            <td><img src="Programming/runs_compare1/detect/predict3/comparison_image1.jpeg" alt="Model 3 - Image 1"></td>
            <td><img src="image1_model4.jpg" alt="Model 4 - Image 1"></td>
        </tr>
        <tr>
            <th>2</th>
            <td><img src="Programming/runs_compare1/detect/predict6/comparison_image2.jpeg" alt="Model 1 - Image 2"></td>
            <td><img src="Programming/runs_compare1/detect/predict7/comparison_image2.jpeg" alt="Model 2 - Image 2"></td>
            <td><img src="Programming/runs_compare1/detect/predict4/comparison_image2.jpeg" alt="Model 3 - Image 2"></td>
            <td><img src="image2_model4.jpg" alt="Model 4 - Image 2"></td>
        </tr>
        <tr>
            <th>3</th>
            <td><img src="Programming/runs_compare1/detect/predict9/comparison_image3.jpeg" alt="Model 1 - Image 2"></td>
            <td><img src="Programming/runs_compare1/detect/predict8/comparison_image3.jpeg" alt="Model 2 - Image 2"></td>
            <td><img src="Programming/runs_compare1/detect/predict10/comparison_image3.jpeg" alt="Model 3 - Image 2"></td>
            <td><img src="image2_model4.jpg" alt="Model 4 - Image 2"></td>
        </tr>
    </tbody>
</table>

</body>
</html>

10/21/2024
---
- all robot structure parts printed; assembled it from scratch in about 35 minutes; everything seems to be in right order
![](log_photos/IMG_1474.jpeg) ![](log_photos/IMG_1475.jpeg) ![](log_photos/IMG_1476.jpeg)![](log_photos/IMG_1479.jpeg)
- the plastic threads of the servo horn screw seem to be stripped on one of the servo which is partly how I tighten the thread into place. If this reoccurs as a problem, I may need to redesign
- going to print the new tpu pads to see how they work/fit into mount

10/20/2024
---
- all parts printed, going to assemble robot
- when trying to put clamp on, discovered that I didn't change the outer diameter dimension of servo mount so did not work; fixed it and printing new one, which will be an hour
- tried to get smaller cocodataset but some of the options that were posted would not download for me; going to keep looking
- Tried to download from this [repo](https://github.com/nightrome/cocostuff10k?tab=readme-ov-file) which I think it legitamate but outdated
- trying to download from this [dataset ninja](https://datasetninja.com/cocostuff10k#download) but wasn't working in a similar way to the above repo but can install from a python package so trying that.
  Above did not work, python script showed I was missing package but I followed instructions on website and didn't mention anything about it
- Dataset ninja download for supervisely format dataset worked and Roboflow can take supervisely formatted files
- Uploading to roboflow but learned only allowed to have 10,000 total so have to get rid of about 300. Hopefully doesn't make some of the annotations not work. Looks like it might take a bit, roughly 4 hours
- another error on the position of the tabs of the servo mount. Confident I fixed this time by making assembly in solidworks of actual pieces instead of test pieces. Going to reprint
- fitment test looks like this: ![fitment_show](log_photos/fitment_show.png)
- this is what it looks like assembled in solid works (except servo is actually rotated 90deg so need to fix mates): ![assembled_1](log_photos/assembled_1.png)

10/19/2024
---
- Print failed last night, pretty sure it was a surface grip problem but so going to reglue and try again
- found an error on my pulley part that may have made the print fail; I changed a diameter that another was based on but didn't update other side
- new way for attaching thread to pulley works very well; struggling to print out the teeth good enough to properly attach to servo
- trying some smaller outer diameter of teeth section
- trying to download a smaller version of coco to try transfer learning based on this [tutorial](https://github.com/ultralytics/yolov5/issues/1314)
- need to combine custom dataset with new object; curious what will happen if i have more than one of the same class
- new outer tooth diameter worked, 4.7 mm. Pulley system seems like it will work well
- updated servo mount to be stronger and fit the servo better: ![new_servo_mount](log_photos/new_servo_mount.png)
- adding a screw into place method for tightening other side of thread to servo mount


10/18/2024
---
- original idea for friction pads did not work as intended, pulley printed was too tight of tolerances for hole and connection teeth
- some new ideas for both of those: put hole through center of pulley section so I can pull thread through and put screw in to lock it into place
- for the friction pad: Create a way to just slide it in but have the friction pad be extra thick so only friction pad part will interact with ground
- going to cad it up
- new pulley: ![new_pulley](log_photos/new_pulley.png)
- new friction pad mount on clamp: ![new_outclamp](log_photos/new_outclamp.png)
- new friction pad, trying to make ridges stronger, and new clamp system: ![new_frictpad](log_photos/new_frictpad.png)
- increased inner wall dimension on clamp to make it a little easier for it to clamp
- going to print and test


10/15/2024
---
- working on 3D printable servo horn pulley; found cad file of servo on internet; designed horn off of other shaft
- here's what the first edition looks like in solidworks, also cut out a slot so servo will sit properly
![servo_pulley_one](log_photos/servo_pulley_horn_one.png)
- printer can do resolution ![pulley_print](log_photos/pulley_print.png)
10/14/2024
---
- went to lab to test and saw that the springs edges are not just squares,
  there is a flat fold sticking up on top right/left of the robot,
  will need to adjust design
- going to bring robot home so i can design things for it better
- though of better way to connect friction pads using the flexibility of tpu
- tpu friction pad print went well, much more flexible but maybe too much
- looking at windup system on the servo for cable, needs to be better and I have an idea in mind;
  I think its important that the mechanisms for the robot are well designed so that proper testing can happen,
  hard to trust results when many other factors could be affecting results.
- measuring mylar with verniers shows a thickness of 0.4mm; currently printing new version with slot but spacing might be too aggressive
- added new way of sliding friction pad into place, then realized that I could now have the friction pad be more centered under the mount;
  might increase friction and performance
- fit test worked with walls; pretty tight but gives it a much more stable feel and look; allows the origami spring to only act as spring and not interact with ground
![fit_test_walls](log_photos/fit_test_walls.jpg)
- printing updated clamp and servo mount to reassemble robot; once this print is done, will print friction pad that will fit in new system


10/13/2024
---
- starting redesign of origami robot structure and friction pads, need other parts to function better to properly test and get better results
- going to try printing pads in tpu, also new idea for a one way leverage mechanism that will press into ground in one direction
- trying new way to connect spring to mount, basically a press fit piece that will go around normal one and press fit the spring in
- this might allow for better connection and integration of the friction pads
- getting weird error in solidworks that the piece can't face or plane but won't show me where so hard to fix. Part looks fine so going to ignore for now
- going to create test piece for testing fitment
- printing at home out of pla, about 30 min, some parts of design look a little thin, but we'll see
- going to get my tpu ready to go to try printing out of that, needs to be dried for 24 hours at 50 degC before I can print
- from looking at print, thicknesses and size of walls and teeth need to be increased
- looking at paper to try to find thickness of mylar, will probably need to go to lab to test properly, did not find thickness
- going to work on one way friction press mechanism
  ![new_friction_idea](log_photos/new_friction_idea.jpg)
- fit test worked pretty well, might need to try some different spacings, new version will be stiffer too
  ![paper_fit_test](log_photos/paper_fit_test.jpeg)
- printing new version (larger teeth, thicker walls, filet on corner) and going to test with mylar spring, 32 min print, pla
- here's what the new clamp design looks like in solidworks ![new_clamp_solidworks](log_photos/solidworks_clamp_idea.png)
- new test piece did not fit together well, some parts were too tight, giving it more clearance and going to try again
- pretty sure problem was that the extra clearance given was only going to one side since location of tooth dimension was on one side, 
  so adjusted location such that it has .2 mm clearance on each side
- giving .2 mm clearance on each side of tooth, .4 mm at top of tooth; 
  outer diam of inner clamp is 52.78 mm, inner diam of outer clamp is 53.5 mm ~~ .75/2 == .38 mm clearance between clamp
- in the worm assembly, lined up the clamps to make sure everything looked right, found that the teeth were not alligned correctly,
  eventually found that it was one location dimension that was on attached to wrong wall
- made outer clamp thicker so it will deflect less, printing new test
- here's what spacing looks like ![clamp_spacing_1](log_photos/fit_spacing_1.png)
- started working on geometry so that clamp will lock into place and not slip off, 
  trying one wall that it won't go past and one chamfered less deep wall that it can deflect through and then be locked into place
- printing test of this, tpu has been drying for about 10 hours, might try to print one of each for testing
- trying the original 'flexure design' and a flexure design with less legs and more spacing to hopefully allow more deflection and surface area touching; like this:
![flexure_with_less](log_photos/flexure_with_less.png)


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
- after reading some of the discussion on this [https://www.reddit.com/r/computervision/comments/16q1csv/is_it_possible_to_add_new_classes_to_pretrained/](https://www.reddit.com/r/computervision/comments/16q1csv/is_it_possible_to_add_new_classes_to_pretrained/)
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
  I did notice that it doesn't work at all angles. Only tested on keyboard, monitor and mouse, robotic arm is far from camera when attached to pc
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



Random old stuff:

old way before table:


Comparison image 1
-using yolo11x.pt (biggest one, only going to do for image 1 cause not significantly different from 11s):
<img src="runs/detect/predict11/comparison_image1.jpeg" width="400">
- using yolo11s.pt:
<img src="runs/detect/predict/comparison_image1.jpeg" width="400">
- using yolo11n.pt:
<img src="runs/detect/predict2/comparison_image1.jpeg" width="400">
- using custom trained dataset on stuff in lab
<img src="runs/detect/predict3/comparison_image1.jpeg" width="400">

Comparison image 2
- using yolo11s.pt:
<img src="runs/detect/predict6/comparison_image2.jpeg" width="400">
- using yolo11n.pt:
<img src="runs/detect/predict7/comparison_image2.jpeg" width="400">
- using custom trained dataset on stuff in lab
<img src="runs/detect/predict4/comparison_image2.jpeg" width="400">

Comparison image 3
- using yolo11s.pt:
<img src="runs/detect/predict9/comparison_image3.jpeg" width="400">
- using yolo11n.pt:
<img src="runs/detect/predict8/comparison_image3.jpeg" width="400">
- using custom trained dataset on stuff in lab
<img src="runs/detect/predict10/comparison_image3.jpeg" width="400">

