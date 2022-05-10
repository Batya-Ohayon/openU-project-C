all: preprocessor

preprocessor: preprocessor.c comments.c preprocessor.h comments.h
	gcc preprocessor.c comments.c preprocessor.h comments.h -Wall -ansi -pedantic -o preprocessor

clean:
	rm*~

