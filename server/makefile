OBJECTS = Eventloop.o Channel.o Watcher.o Thread.o

eventloop_example:  $(OBJECTS) eventloop_example.cpp
	c++ -g -std=c++11 -o eventloop_example.out eventloop_example.cpp $(OBJECTS)

eventloop: Eventloop.cpp Eventloop.h
	c++ -std=c++11 -c Eventloop.cpp -o Eventloop.o

channel: Channel.cpp Channel.h
	c++ -std=c++11 -c Channel.cpp -o Channel.o

watcher: Watcher.cpp Watcher.h
	c++ -std=c++11 -c Watcher.cpp -o Watcher.o

thread: Thread.cpp Thread.h
	c++ -std=c++11 -c Thread.cpp -o Thread.o

clean:
	rm *.o