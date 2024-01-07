all:derle bagla calistir
derle:
	g++ -c -I "./include" ./src/Dugum.cpp -o ./lib/Dugum.o
	g++ -c -I "./include" ./src/readTxtFile.cpp -o ./lib/readTxtFile.o
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/AVLAgaci.cpp -o ./lib/AVLAgaci.o
bagla:
	g++ ./lib/Dugum.o ./lib/readTxtFile.o ./lib/main.o ./lib/AVLAgaci.o -o ./bin/program
calistir:
	./bin/program