example: *.c *.h
	gcc main.c sqlite3.c -o example

run: example
	./example foo.db
clean: 
	rm example foo.db
