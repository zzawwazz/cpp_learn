#若要编译的项目很多，写makefile文件会非常的麻烦，我们可以用变量来解决这个问题
INCLUDEDIR=-I/home/zzaw/cpp_project/lesson/1.1Dynamic_Static_Librarya_and_makefile/tools -I/home/zzaw/cpp_project/lesson/1.1Dynamic_Static_Librarya_and_makefile/api
LIBDIR=-L/home/zzaw/cpp_project/lesson/1.1Dynamic_Static_Librarya_and_makefile/tools -L/home/zzaw/cpp_project/lesson/1.1Dynamic_Static_Librarya_and_makefile/api

all:demo demo01 demo02 demo03 

demo:demo.cpp
#使用变量之前
#	g++ -o demo demo.cpp -L/home/zzaw/cpp_project/lesson/tools -lpublic -L/home/zzaw/cpp_project/lesson/api -lmyapi -I/home/zzaw/cpp_project/lesson/tools -I/home/zzaw/cpp_project/lesson/api
#使用变量之后
	g++ -o demo demo.cpp  $(INCLUDEDIR) $(LIBDIR) -lpublic  -lmyapi 
#还可以进行其他指令，例如：
	cp demo /tmp/.

demo01:demo01.cpp
	g++ -o demo01 demo01.cpp  $(INCLUDEDIR) $(LIBDIR) -lpublic  -lmyapi

demo02:demo02.cpp
	g++ -o demo02 demo02.cpp  $(INCLUDEDIR) $(LIBDIR) -lpublic  -lmyapi

demo03:demo03.cpp
	g++ -o demo03 demo03.cpp  $(INCLUDEDIR) $(LIBDIR) -lpublic  -lmyapi

clean:
	rm -f demo demo01 demo02 demo03 
