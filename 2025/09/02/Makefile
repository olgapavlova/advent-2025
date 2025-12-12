all:
	@make clean --no-print-directory
	@./prepare.sh i
	@make cols.run --no-print-directory
	@make rows.run --no-print-directory
	@make squares.run --no-print-directory
	@./squares.sh

%.run:
	@gcc -g -O2 $*.c -o $*.run
	@./$*.run

clean:
	@rm -f *.run
	@rm -f cols.txt
	@rm -f rows.txt
	@rm -f main.txt
	@rm -f x-direct.txt
	@rm -f y-direct.txt
	@rm -f squares.txt
