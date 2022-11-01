#Patrick Ging MakeFile

#executables
sample: sample.o imageio.o
	g++ -o sample -std=c++11 sample.o imageio.o

main: main.o image_functions.o imageio.o
	g++ -o main -std=c++11 main.o image_functions.o imageio.o

#objs
main.o: main.cpp image_functions.cpp image_functions.h
	g++ -c -std=c++11 main.cpp image_functions.cpp

sample.o: sample.cpp imageio.h
	g++ -c -std=c++11 sample.cpp

imageio.o: imageio.cpp imageio.h
	g++ -c -std=c++11 imageio.cpp

#misc
clean:
	rm -f sample.o imageio.o main.o image_functions.o 
	rm -f main a.out sample
	rm -f taskA.pgm taskB.pgm taskC.pgm taskD.pgm taskE.pgm taskF.pgm
