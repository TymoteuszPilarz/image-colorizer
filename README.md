# ImageColorizer

Web application designed to colorize grayscale images using algorithm described in A. Levin D. Lischinski and Y. Weiss Colorization using Optimization. ACM Transactions on Graphics, Aug 2004 for coloring grayscale images.

Frontend and backend is written in pure C++20 with the help of Wt, OpenCV and Eigen3.

Original algorithm is published [here](https://www.cs.huji.ac.il/w~yweiss/Colorization).
Implementation is based on [this repository]([https://link-url-here.org](https://github.com/lightalchemist/colorize-image).

# Build and run

Appropriate CMake files are provided. To build project Wt, OpenCV and Eigen3 are requred to be installed first. After successfull compilation, the following command can be used to run the program:

--docroot <project_directory> --http-address 0.0.0.0 --http-port 8080

where <project_directory> needs to be replaced with project path.

Image processing can take up to several dozen minutes depending on the image size and other factors, so it may be necessary to modify wt_config.xml. Global configuration is typically located at /etc/wt (check Wt documentation for more information).

<timeout>seconds</timeout> - this property can be increased to prevent session from terminating while the image is still processesd.
<max-request-size>size</max-request-size> - max request size, wchich can be altered in order to upload larger images (e.g. 4k resolution)

# Demonstration
