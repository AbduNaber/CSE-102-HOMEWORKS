all : compile run clean

compile: main.c util.c util.h
		@gcc -o test main.c util.c
run: test
	@./test
clean: test
	@rm -f test 



