all: tl.run tr.run bl.run br.run
	gcc -g -O2 main.c -o main.run
	./main.run

%.run:
	gcc -g -O2 $*.c -o $*.run
	./$*.run

clean:
	rm -f *.run
