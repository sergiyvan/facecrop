# Facecorp

## 1. Description
This programm extact the biggest face from the rest of image and write it to video file.  
It do following steps:
 1. Find biggest face region
 2. Aply face mask to this region
They are better(more accurate) aprochaes but they would need more time to implement.

## 2. Requirements
 * Web-cam
 * [OpenCV >=3.1](https://github.com/opencv/opencv)
 * *libgtk2.0-dev* and *pkg-config* packages
     * ```sudo apt-get install libgtk2.0-dev pkg-config```

## 3. Usage
 1. Clone the files
 2. Go to the programm directory
 3. Call `make`
 4. Call `./facecrop`
 5. keep some distance from the camera
 6. Look to the web-cam and press *Esc* after a while
 7. watch the result in the *facecrop.mp4* file

## 4. Notes
 * Tested on Ubuntu 14.04
