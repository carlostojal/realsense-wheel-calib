# realsense-wheel-calib

This is a wheel calibration "tool" based on a RealSense camera, developed to FSIPLeiria Formula Student Team.

## Technical overview

The main data needed to do wheel calibration are the wheel poses.

The poses are calculated by computing the transformation between a fixed reference frame on the car and the wheel frame, which is in this case a mobile reference. Both reference frames are identified by a Charuco board. Charuco is a combination of a chessboard and ArUco markers. In our case, the chessboard is used to identify points on the references (its corners), and the ArUco markers are used to distinguish the frames by them known set of numeric IDs.

The poses are calculated by using the OpenCV library, which provides functionality to detect Charuco board corners. These corners are then deprojected to 3D space by using the camera intrinsics and extrinsics. The deprojection happens parallelized on the GPU, by using the CUDA library, making this a lot faster than iteratively on the CPU.

The transformation between the two boards is then calculated by using the ICP algorithm, provided by the PCL library.

**WARNING**: a lot of this functionality is still under development, and the code is not yet ready for production.

## Dependencies
- OpenCV
- PCL
- CUDA
- RealSense SDK 2.0

## Build
On a terminal:
- Go to this directory
- Create a new "build" directory and go there: ```mkdir build && cd build```
- Execute the following command: ```cmake ..```
- This will finally build the program: ```make```

## Run
On a terminal:
- Go to the "build" directory
- Execute the following command: ```./RealSenseWheelCalib```

## Future work
- Send the transformation matrix and a JPEG image to an Android client using an UDP socket.
- Do the Android app.