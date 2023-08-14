#app-static: *.c 
#	gcc main.c -Wl,-Bstatic -lsqlite3 -o app-static

app: *.c 
	gcc main.c -lsqlite3 -o app

run: app
	./app foo.db

latrace-log: app
	latrace ./app foo.db > latrace_app.log

show-libc-calls: latrace-log
	cat latrace_app.log | awk '{print $$2}' | sort | uniq

clean: 
	rm app foo.db latrace_app.log
