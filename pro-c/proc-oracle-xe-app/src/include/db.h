#ifndef DB_H
#define DB_H

// Function declarations for database operations
void connect_to_db();
void disconnect_from_db();
void sql_error();
void execute_select(const char* sql, const char* json_binds);
int execute_dml(const char* sql, const char* json_binds);

#endif // DB_H
