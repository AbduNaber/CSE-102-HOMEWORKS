all : compile run clean

compile: main.c 
		@gcc -o test main.c -lm

run: test
	@./test

clean: test
	@rm -f test 

