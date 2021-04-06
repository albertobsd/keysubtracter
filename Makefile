default:
	gcc -O3 -c gmpecc.c -o gmpecc.o
	gcc -O3 -c util.c -o util.o
	gcc -o keysubtracter keysubtracter.c gmpecc.o util.o -lgmp
clean:
	rm -r *.o
