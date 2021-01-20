all: Antimirov_Aut

Antimirov_Aut:   main.pdf
	evince main.pdf &

main.pdf: main.dot
	 dot -Tpdf main.dot -o  main.pdf

main.dot: main.o
	./main > main.dot

main.o: main.cc
	g++ main.cc -o main.o

clean:
	rm -rf  Antimirov_Aut *.o *.dot *.pdf


mrproper: clean
	rm -rf main.pdf
