example:
	gcc main.c sqlite3.c -o example

drop_table: example
	./example foo.db "drop table some_table"
clean: 
	rm example foo.db
