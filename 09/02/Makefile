all:
	@./prepare.sh input
	@make clean --no-print-directory
	@make cols-pure.run --no-print-directory
	@make rows-pure.run --no-print-directory
	@make cols-extra.run --no-print-directory
	@make squares.run --no-print-directory

%.run:
	gcc -g -O2 $*.c -o $*.run
	./$*.run

clean:
	rm -f *.run
