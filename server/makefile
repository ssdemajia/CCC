OBJECTS = Eventloop.o Channel.o Watcher.o Thread.o Socket.o IP.o Acceptor.o

acceptor_example: $(OBJECTS) acceptor_example.cpp
	c++ -Wc++11-extensions -g -std=c++11 -o acceptor_example.out acceptor_example.cpp $(OBJECTS)

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

acceptor: Acceptor.cpp Acceptor.h
	c++ -std=c++11 -c Acceptor.cpp -o Acceptor.o

ip: IP.cpp IP.h
	c++ -std=c++11 -c IP.cpp -o IP.o

socket: Socket.cpp Socket.h
	c++ -std=c++11 -c Socket.cpp -o Socket.o
clean:
	rm *.o