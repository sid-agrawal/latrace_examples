# Finding out a subset of libc calls needed for SQLite
This extremely trivial SQLite application:
- Opens a SQLite DB handle
- Creates a table 
- Inserts 10 rows to the table.
- Queries the table
- Deletes the table
- Closes the SQLite db handle


Packages Needed:
```bash
 sudo apt-get install latrace sqlite3
```

To the get list of unique libc calls made during this toy example:

```bash
> make show-libc-calls

gcc main.c -lsqlite3 -o app
latrace ./app foo.db > latrace_app.log
cat latrace_app.log | awk '{print $2}' | sort | uniq

|
_dl_audit_preinit
__errno_location
fdatasync
finished
free
getenv
getpid
malloc
memcmp
memcpy
__memcpy_chk
memmove
memset
open64
printf
pthread_mutexattr_destroy
pthread_mutexattr_init
pthread_mutexattr_settype
pthread_mutex_destroy
pthread_mutex_init
pthread_mutex_lock
pthread_mutex_unlock
realloc
sprintf
sqlite3_close
sqlite3_column_text
sqlite3_exec
sqlite3_finalize
sqlite3_open
sqlite3_prepare_v2
sqlite3_step
strchrnul
strcmp
strlen
strncmp
strrchr
__tunable_get_val
```
