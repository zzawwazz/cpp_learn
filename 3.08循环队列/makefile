all: demo1 demo2


demo1: _public.h demo1.cpp
	g++ -o demo1 demo1.cpp _public.h

demo2: _public.h demo2.cpp
	g++ -o demo2 demo2.cpp _public.h

clean:
	rm -f demo1 demo2 