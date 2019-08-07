OBJECTS = Eventloop.o Channel.o Watcher.o Thread.o Socket.o IP.o Acceptor.o Conn.o Server.o

example_conn: $(OBJECTS) example_conn.cpp
	c++ -std=c++11 -o example_conn.out example_conn.cpp $(OBJECTS)
example_acceptor: $(OBJECTS) example_acceptor.cpp
	c++ -std=c++11 -o example_acceptor.out example_acceptor.cpp $(OBJECTS)

example_eventlop:  $(OBJECTS) example_eventlop.cpp
	c++ -g -std=c++11 -o example_eventlop.out example_eventlop.cpp $(OBJECTS)

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

conn: Conn.cpp Conn.h
	c++ -std=c++11 -c Conn.cpp -o Conn.o
clean:
	rm *.o