## flags pass to c-compiler.
PYTHONLIBS = -ldl  -lutil -lm  -lpython3.4m -Xlinker -export-dynamic
OPENCVLIBS=-lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio
AM_CXXFLAGS = -g -O0 -pthread -std=c++11 -I../include/ -L/usr/local/lib -lpthread $(PYTHONLIBS) $(OPENCVLIBS)
bin_PROGRAMS = face
face_SOURCES = face.cpp python_cpp_interface.cpp frame.cpp

clean_local :
	rm face.o python_cpp_interface.o frame.o
