# It assumes that opencv-3.1.* is installed on /usr/local/lib.
# Just this script and it should build successfully.

g++ -I ./include -L /usr/local/lib -o displayImage ./displayImage.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui

export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH
