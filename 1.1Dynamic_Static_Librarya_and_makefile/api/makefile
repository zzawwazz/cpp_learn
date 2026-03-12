all:libmyapi.a libmyapi.so


libmyapi.a:myapi.h myapi.cpp
	g++ -c -o libmyapi.a myapi.cpp

libmyapi.so:myapi.h myapi.cpp
	g++ -fPIC -shared -o libmyapi.so myapi.cpp

clean:
	rm -f libmyapi.a libmyapi.so

