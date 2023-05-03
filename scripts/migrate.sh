#!/bin/sh

cat "sql/V1.0.0__initial.sql" | sqlite3 execution.db
