  #include <stdio.h>
  #include <sqlite3.h>

  static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
  }

  int main(int argc, char **argv){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    if( argc!=2 ){
      fprintf(stderr, "Usage: %s DATABASE \n", argv[0]);
      return(1);
    }
    rc = sqlite3_open(argv[1], &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return(1);
    }

    /* Create Table */
    char * cmd = "CREATE TABLE KVStore ( key int, val int)";
    rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

    /* Insert value */
    char buf[200];
    for (int i = 1; i <= 10; i++)
    {
      sprintf(buf, "INSERT INTO KVStore (key, val) VALUES (%d,%d)", i, i * i);
      rc = sqlite3_exec(db, buf, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK)
      {
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, "SELECT * FROM KVStore", -1, &res, 0);
    if (rc != SQLITE_OK)
    {
      printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return 1;
    }
    for (int i = 1; i <= 10; i++)
    {
      rc = sqlite3_step(res);
      if (rc == SQLITE_ROW)
      {
        printf("--%s | %s\n", sqlite3_column_text(res, 0), sqlite3_column_text(res, 1));
      }
      else
      {
        break;
      }
    }
    sqlite3_finalize(res);

    /* Drop Table */
    cmd = "DROP TABLE KVStore";
    rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
  }
