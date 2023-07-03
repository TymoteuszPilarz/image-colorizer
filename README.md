# ImageColorizer

Web application designed to colorize grayscale images using algorithm described in A. Levin D. Lischinski and Y. Weiss Colorization using Optimization. ACM Transactions on Graphics, Aug 2004 for coloring grayscale images.

Frontend and backend is written in pure C++20 with the help of Wt, OpenCV and Eigen3.

Original algorithm is published [here](https://www.cs.huji.ac.il/w~yweiss/Colorization).\
Implementation used by this project is based on [this repository](https://github.com/lightalchemist/colorize-image).

# Building and running

Appropriate CMake files are already provided. To build the project, Wt, OpenCV and Eigen3 are requred to be installed first. After successfull compilation, the following command can be used to run the program:

--docroot <project_directory> --http-address 0.0.0.0 --http-port 8080

where <project_directory> needs to be replaced with the project path.

Image processing can take up to several dozen minutes depending on the image size and used setting, so it may be necessary to modify wt_config.xml. Global configuration is typically located at /etc/wt/ (check Wt documentation for more details).

```<timeout>seconds</timeout>``` - this property can be increased to prevent session from terminating while the image is still processesd.

```<max-request-size>size</max-request-size>``` - max request size, wchich can be altered in order to upload larger images (e.g. 4k resolution)

# Demonstration
<img width="1440" alt="image1" src="https://github.com/TymoteuszPilarz/ImageColorizer/assets/122737837/aff08814-c2ac-48e6-9f3e-294f26a2e3bf">
<img width="1440" alt="image2" src="https://github.com/TymoteuszPilarz/ImageColorizer/assets/122737837/c36f0157-9116-4895-ba32-9b07ca7c2122">
<img width="1440" alt="image3" src="https://github.com/TymoteuszPilarz/ImageColorizer/assets/122737837/f0b97d88-c557-4d0f-a219-f2de07e4daf9">
