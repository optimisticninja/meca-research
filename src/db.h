#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <sqlite3.h>

void meta();

sqlite3* connect_in_memory();

int backup(sqlite3* db, const char* fname);
void close(sqlite3* db);
void insert(uint32_t rule, size_t timestep, uint32_t prev, uint32_t next, const char* type, double shannon,
            bool avalanche);
