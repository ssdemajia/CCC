CPP = g++
CPPFLAGS = -Wall -g
main.exe: main.cpp tools.cpp  http_parser.c
	$(CPP) $(CPPFLAGS) $^ -o $@

echo.exe: tools.cpp echo.cpp
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf *.o *.s *.exe