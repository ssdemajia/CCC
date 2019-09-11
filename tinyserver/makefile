CPP = g++
CPPFLAGS = -Wall
main.exe: main.cpp tools.cpp
	$(CPP) $(CPPFLAGS) $^ -o $@

echo.exe: tools.cpp echo.cpp 
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf *.o *.s