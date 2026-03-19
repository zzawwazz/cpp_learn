all: incache outcache


incache: _public.h incache.cpp _public.cpp
	g++ -o incache incache.cpp _public.h _public.cpp

outcache: _public.h outcache.cpp _public.cpp
	g++ -o outcache outcache.cpp _public.h _public.cpp



clean:
	rm -f outcache incache