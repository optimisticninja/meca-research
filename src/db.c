#include "db.h"

#include <stdio.h>

#include <sqlite3.h>

void meta()
{
	printf("%s\n", sqlite3_libversion());
}

sqlite3* connect_in_memory()
{
	int rc = 0;
	sqlite3* db;
	char* errmsg;

	rc = sqlite3_open(":memory:", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "ERROR: opening SQLite DB in memory: %s\n", sqlite3_errmsg(db));
		goto out;
	}

	printf("opened SQLite handle successfully\n");
	return db;

out:
	sqlite3_close(db);
	printf("database closed.\n");
	return NULL;
}

void close(sqlite3* db)
{
	sqlite3_close(db);
}

int backup(sqlite3* db, const char* fname)
{
	int rc;
	sqlite3* file;
	sqlite3_backup* backup;
	sqlite3* to;
	sqlite3* from;

	rc = sqlite3_open(fname, &file);
	if (rc == SQLITE_OK) {
		from = db;
		to = file;

		backup = sqlite3_backup_init(to, "main", from, "main");

		if (backup) {
			sqlite3_backup_step(backup, -1);
			sqlite3_backup_finish(backup);
		}

		rc = sqlite3_errcode(to);
	}

	sqlite3_close(file);
	return rc;
}
