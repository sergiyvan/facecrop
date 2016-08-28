all:
	g++ -std=c++11 main.cpp ImgProcessor.cpp -o facecrop `pkg-config opencv --cflags gtk+-2.0 --libs gtk+-2.0`

clean:
	rm -f *.o facecrop