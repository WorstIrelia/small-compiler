all :
	g++ -o front  main.cpp scanner.h scanner.cpp parser.h parser.cpp error.h error.cpp semantic.h semantic.cpp generate.h generate.cpp -std=c++11 	
	g++ -o back  background.cpp -std=c++11
clean :
	rm *.gch *.o front back 

