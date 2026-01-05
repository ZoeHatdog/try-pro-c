
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[98];
};
static const struct sqlcxp sqlfpn =
{
    97,
    "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db_query_service.pc"
};


static unsigned int sqlctx = 1034682733;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned int   sqlpfmem;
            void  *sqhstv[1];
   unsigned int   sqhstl[1];
            int   sqhsts[1];
            void  *sqindv[1];
            int   sqinds[1];
   unsigned int   sqharm[1];
   unsigned int   *sqharc[1];
   unsigned short  sqadto[1];
   unsigned short  sqtdso[1];
} sqlstm = {13,1};

/* SQLLIB Prototypes */
extern void sqlcxt (void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlcx2t(void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlbuft(void **, char *);
extern void sqlgs2t(void **, char *);
extern void sqlorat(void **, unsigned int *, void *);

/* Forms Interface */
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern void sqliem(unsigned char *, signed int *);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{13,4128,1,27,0,
};


#line 1 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db_query_service.pc"
/****************************************/
/* db_query_service.pc - Pro*C Service */
/* Accepts JSON input via stdin        */
/* Returns JSON output via stdout      */
/****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlca.h>
#include "db.h"

void connect_to_db();
void disconnect_from_db();
void execute_select(const char* sql, const char* json_binds);
int execute_dml(const char* sql, const char* json_binds);

// Simple JSON parsing - extract SQL and binds
static void parse_json_request(char* input, char* sql, size_t sql_size, char* binds, size_t binds_size) {
    // Extract SQL
    const char* sql_pos = strstr(input, "\"sql\"");
    if (sql_pos) {
        sql_pos = strchr(sql_pos, ':');
        if (sql_pos) {
            sql_pos = strchr(sql_pos, '"');
            if (sql_pos) {
                sql_pos++; // Skip opening quote
                const char* sql_end = strchr(sql_pos, '"');
                if (sql_end) {
                    size_t len = sql_end - sql_pos;
                    if (len >= sql_size) len = sql_size - 1;
                    strncpy(sql, sql_pos, len);
                    sql[len] = '\0';
                }
            }
        }
    }

    // Extract binds (simplified - get the whole binds object)
    const char* binds_pos = strstr(input, "\"binds\"");
    if (binds_pos) {
        binds_pos = strchr(binds_pos, '{');
        if (binds_pos) {
            const char* binds_end = strrchr(binds_pos, '}');
            if (binds_end) {
                size_t len = binds_end - binds_pos + 1;
                if (len >= binds_size) len = binds_size - 1;
                strncpy(binds, binds_pos, len);
                binds[len] = '\0';
            }
        }
    }
}

int main() {
    char input[4096];
    char sql[2000];
    char binds[1000];
    
    // Read JSON input from stdin
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stdout, "{\"success\":false,\"error\":\"No input provided\",\"rows\":[]}\n");
        return 1;
    }

    // Remove newline
    input[strcspn(input, "\n\r")] = '\0';

    // Initialize output strings
    sql[0] = '\0';
    binds[0] = '\0';

    // Parse JSON request
    parse_json_request(input, sql, sizeof(sql), binds, sizeof(binds));

    if (sql[0] == '\0') {
        fprintf(stdout, "{\"success\":false,\"error\":\"No SQL provided\",\"rows\":[]}\n");
        return 1;
    }

    // Connect to database
    connect_to_db();

    // Determine if SELECT or DML
    int is_select = (strstr(sql, "SELECT") != NULL || strstr(sql, "select") != NULL);

    if (is_select) {
        // Execute SELECT query (already includes success:true)
        execute_select(sql, binds);
        fprintf(stdout, "\n");
    } else {
        // Execute DML (INSERT/UPDATE/DELETE)
        int result = execute_dml(sql, binds);
        if (result == 0) {
            fprintf(stdout, "{\"success\":true,\"error\":null,\"rows\":[]}\n");
        } else {
            fprintf(stdout, "{\"success\":false,\"error\":\"SQL error code: %d\",\"rows\":[]}\n", result);
        }
    }

    // Disconnect from database
    disconnect_from_db();

    return 0;
}

