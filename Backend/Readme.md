==== DB Structure ====

sqlite3 db.sqlite;

CREATE TABLE tbl_axis( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, x REAL, y REAL, z REAL );

CREATE TABLE tbl_temperature( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, value REAL );

CREATE TABLE tbl_heartrate( idx INTEGER PRIMARY KEY, id INTEGER, time NUMERIC, value REAL );