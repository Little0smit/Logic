all:	ttable

clean:
	rm ttable
ttable : main.c operations.c operations.h functions.c functions.h parser.c parser.h
	gcc main.c operations.c functions.c parser.c -o ttable
