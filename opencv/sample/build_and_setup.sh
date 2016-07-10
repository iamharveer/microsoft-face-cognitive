# It assumes that opencv-3.1.* is installed on /usr/local/lib.
# Just run this script and it should build successfully.
# usage: ./build_and_setup.sh <path_to_cpp> <output_file_name>

g++ -I ./include -L /usr/local/lib -o $2 $1 -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio

export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
