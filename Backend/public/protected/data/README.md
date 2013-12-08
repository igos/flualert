==== Permitions ====
Set dir mode to 777


==== DB Structure ====

sqlite3 db.sqlite;

CREATE TABLE tbl_axis( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, value INTEGER );

CREATE TABLE tbl_temperature( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, value REAL );

CREATE TABLE tbl_heartrate( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, value REAL );