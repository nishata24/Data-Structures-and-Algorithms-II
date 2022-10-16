findPaths.exe: findPaths.o graph.o heap.o hash.o
	g++ -o findPaths.exe findPaths.o graph.o heap.o hash.o

findPaths.o: findPaths.cpp
	g++ -c findPaths.cpp
    
graph.o: graph.cpp graph.h heap.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o findPathsDebug.exe findPaths.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups