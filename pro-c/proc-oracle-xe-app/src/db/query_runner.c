
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
           char  filnam[97];
};
static const struct sqlcxp sqlfpn =
{
    96,
    "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
};


static unsigned int sqlctx = 1630045243;


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
            void  *sqhstv[5];
   unsigned int   sqhstl[5];
            int   sqhsts[5];
            void  *sqindv[5];
            int   sqinds[5];
   unsigned int   sqharm[5];
   unsigned int   *sqharc[5];
   unsigned short  sqadto[5];
   unsigned short  sqtdso[5];
} sqlstm = {13,5};

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

 static const char *sq0001 = 
"select user_id ,username ,email ,password ,TO_CHAR(created_at,'YYYY-MM-DD HH\
24:MI:SS')  from users where email=:b0           ";

 static const char *sq0002 = 
"select user_id ,username ,email ,password ,TO_CHAR(created_at,'YYYY-MM-DD HH\
24:MI:SS')  from users where user_id=:b0           ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{13,4128,1,27,0,
5,0,0,1,125,0,9,97,0,0,1,1,0,1,0,1,97,0,0,
24,0,0,1,0,0,13,100,0,0,5,0,0,1,0,2,3,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,0,
59,0,0,1,0,0,15,112,0,0,0,0,0,1,0,
74,0,0,2,127,0,9,119,0,0,1,1,0,1,0,1,3,0,0,
93,0,0,2,0,0,13,122,0,0,5,0,0,1,0,2,3,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,0,
128,0,0,2,0,0,15,133,0,0,0,0,0,1,0,
143,0,0,3,64,0,3,167,0,0,3,3,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,
170,0,0,4,0,0,24,171,0,0,1,1,0,1,0,1,97,0,0,
189,0,0,5,0,0,29,178,0,0,0,0,0,1,0,
};


#line 1 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlca.h>
#include "db.h"

extern void sql_error();

// Simple JSON parsing helpers (for basic JSON structure)
static int extract_json_string(const char* json, const char* key, char* output, size_t output_size) {
    char search_key[256];
    snprintf(search_key, sizeof(search_key), "\"%s\"", key);
    const char* pos = strstr(json, search_key);
    if (!pos) return 0;
    
    pos = strchr(pos, ':');
    if (!pos) return 0;
    pos++; // Skip colon
    
    // Skip whitespace
    while (*pos == ' ' || *pos == '\t') pos++;
    
    if (*pos == '"') {
        pos++; // Skip opening quote
        const char* end = strchr(pos, '"');
        if (!end) return 0;
        size_t len = end - pos;
        if (len >= output_size) len = output_size - 1;
        strncpy(output, pos, len);
        output[len] = '\0';
        return 1;
    }
    return 0;
}

static int extract_json_int(const char* json, const char* key, int* output) {
    char search_key[256];
    snprintf(search_key, sizeof(search_key), "\"%s\"", key);
    const char* pos = strstr(json, search_key);
    if (!pos) return 0;
    
    pos = strchr(pos, ':');
    if (!pos) return 0;
    pos++; // Skip colon
    
    // Skip whitespace
    while (*pos == ' ' || *pos == '\t') pos++;
    
    *output = atoi(pos);
    return 1;
}

// Execute a SELECT query with bind variables
void execute_select(const char* sql, const char* json_binds) {
    /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 55 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    char sql_stmt[2000];
    char bind_email[200];
    int bind_id;
    
    // Output variables
    int user_id;
    char username[200];
    char email[200];
    char password[500];
    char created_at[50];
    /* EXEC SQL END DECLARE SECTION; */ 
#line 66 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"


    strncpy(sql_stmt, sql, sizeof(sql_stmt) - 1);
    sql_stmt[sizeof(sql_stmt) - 1] = '\0';

    // Initialize bind variables
    bind_email[0] = '\0';
    bind_id = 0;

    // Parse bind variables from JSON
    if (json_binds) {
        extract_json_string(json_binds, "email", bind_email, sizeof(bind_email));
        extract_json_int(json_binds, "id", &bind_id);
        if (bind_id == 0) {
            extract_json_int(json_binds, "user_id", &bind_id);
        }
    }

    // Output JSON result to stdout
    fprintf(stdout, "{\"success\":true,\"rows\":[");

    /* EXEC SQL WHENEVER SQLERROR DO sql_error(); */ 
#line 87 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"


    int first_row = 1;
    
    // Handle different query types
    if (strstr(sql, "WHERE email = :email") && bind_email[0] != '\0') {
        /* EXEC SQL DECLARE c_email CURSOR FOR
            SELECT user_id, username, email, password, TO_CHAR(created_at, 'YYYY-MM-DD HH24:MI:SS')
            FROM users WHERE email = :bind_email; */ 
#line 95 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

        
        /* EXEC SQL OPEN c_email; */ 
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 1;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.stmt = sq0001;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )5;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.selerr = (unsigned short)1;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlpfmem = (unsigned int  )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqcmod = (unsigned int )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[0] = (         void  *)bind_email;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[0] = (unsigned int  )200;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[0] = (         int  )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[0] = (         void  *)0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[0] = (         int  )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[0] = (unsigned int  )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[0] = (unsigned short )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[0] = (unsigned short )0;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsv = sqlstm.sqhstv;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsl = sqlstm.sqhstl;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphss = sqlstm.sqhsts;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpind = sqlstm.sqindv;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpins = sqlstm.sqinds;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparm = sqlstm.sqharm;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparc = sqlstm.sqharc;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpadto = sqlstm.sqadto;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqptdso = sqlstm.sqtdso;
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 97 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

        
        while (1) {
            /* EXEC SQL FETCH c_email INTO :user_id, :username, :email, :password, :created_at; */ 
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            struct sqlexd sqlstm;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlvsn = 13;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.arrsiz = 5;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqladtp = &sqladt;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqltdsp = &sqltds;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.iters = (unsigned int  )1;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.offset = (unsigned int  )24;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.selerr = (unsigned short)1;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlpfmem = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.cud = sqlcud0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlety = (unsigned short)4352;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.occurs = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqfoff = (           int )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqfmod = (unsigned int )2;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[0] = (         void  *)&user_id;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[0] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[0] = (         void  *)0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[0] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[0] = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[0] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[0] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[1] = (         void  *)username;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[1] = (unsigned int  )200;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[1] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[1] = (         void  *)0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[1] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[1] = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[1] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[1] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[2] = (         void  *)email;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[2] = (unsigned int  )200;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[2] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[2] = (         void  *)0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[2] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[2] = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[2] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[2] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[3] = (         void  *)password;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[3] = (unsigned int  )500;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[3] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[3] = (         void  *)0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[3] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[3] = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[3] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[3] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[4] = (         void  *)created_at;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[4] = (unsigned int  )50;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[4] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[4] = (         void  *)0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[4] = (         int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[4] = (unsigned int  )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[4] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[4] = (unsigned short )0;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphsv = sqlstm.sqhstv;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphsl = sqlstm.sqhstl;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphss = sqlstm.sqhsts;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpind = sqlstm.sqindv;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpins = sqlstm.sqinds;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqparm = sqlstm.sqharm;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqparc = sqlstm.sqharc;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpadto = sqlstm.sqadto;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqptdso = sqlstm.sqtdso;
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            if (sqlca.sqlcode < 0) sql_error();
#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 100 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

            if (sqlca.sqlcode == 100) break; // No more rows
            if (sqlca.sqlcode != 0) break;
            
            if (!first_row) fprintf(stdout, ",");
            first_row = 0;
            
            // Escape JSON strings
            fprintf(stdout, "{\"USER_ID\":%d,\"USERNAME\":\"%s\",\"EMAIL\":\"%s\",\"PASSWORD\":\"%s\",\"CREATED_AT\":\"%s\"}",
                   user_id, username, email, password, created_at);
        }
        
        /* EXEC SQL CLOSE c_email; */ 
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 5;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )59;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 112 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    } 
    else if ((strstr(sql, "WHERE user_id = :id") || strstr(sql, "WHERE user_id = :user_id")) && bind_id != 0) {
        /* EXEC SQL DECLARE c_id CURSOR FOR
            SELECT user_id, username, email, password, TO_CHAR(created_at, 'YYYY-MM-DD HH24:MI:SS')
            FROM users WHERE user_id = :bind_id; */ 
#line 117 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

        
        /* EXEC SQL OPEN c_id; */ 
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 5;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.stmt = sq0002;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )74;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.selerr = (unsigned short)1;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlpfmem = (unsigned int  )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqcmod = (unsigned int )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[0] = (         void  *)&bind_id;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[0] = (         int  )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[0] = (         void  *)0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[0] = (         int  )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[0] = (unsigned int  )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[0] = (unsigned short )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[0] = (unsigned short )0;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsv = sqlstm.sqhstv;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsl = sqlstm.sqhstl;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphss = sqlstm.sqhsts;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpind = sqlstm.sqindv;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpins = sqlstm.sqinds;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparm = sqlstm.sqharm;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparc = sqlstm.sqharc;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpadto = sqlstm.sqadto;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqptdso = sqlstm.sqtdso;
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 119 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

        
        while (1) {
            /* EXEC SQL FETCH c_id INTO :user_id, :username, :email, :password, :created_at; */ 
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            struct sqlexd sqlstm;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlvsn = 13;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.arrsiz = 5;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqladtp = &sqladt;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqltdsp = &sqltds;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.iters = (unsigned int  )1;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.offset = (unsigned int  )93;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.selerr = (unsigned short)1;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlpfmem = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.cud = sqlcud0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqlety = (unsigned short)4352;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.occurs = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqfoff = (           int )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqfmod = (unsigned int )2;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[0] = (         void  *)&user_id;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[0] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[0] = (         void  *)0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[0] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[0] = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[0] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[0] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[1] = (         void  *)username;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[1] = (unsigned int  )200;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[1] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[1] = (         void  *)0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[1] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[1] = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[1] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[1] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[2] = (         void  *)email;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[2] = (unsigned int  )200;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[2] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[2] = (         void  *)0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[2] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[2] = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[2] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[2] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[3] = (         void  *)password;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[3] = (unsigned int  )500;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[3] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[3] = (         void  *)0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[3] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[3] = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[3] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[3] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstv[4] = (         void  *)created_at;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhstl[4] = (unsigned int  )50;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqhsts[4] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqindv[4] = (         void  *)0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqinds[4] = (         int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqharm[4] = (unsigned int  )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqadto[4] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqtdso[4] = (unsigned short )0;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphsv = sqlstm.sqhstv;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphsl = sqlstm.sqhstl;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqphss = sqlstm.sqhsts;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpind = sqlstm.sqindv;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpins = sqlstm.sqinds;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqparm = sqlstm.sqharm;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqparc = sqlstm.sqharc;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqpadto = sqlstm.sqadto;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlstm.sqptdso = sqlstm.sqtdso;
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
            if (sqlca.sqlcode < 0) sql_error();
#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 122 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

            if (sqlca.sqlcode == 100) break; // No more rows
            if (sqlca.sqlcode != 0) break;
            
            if (!first_row) fprintf(stdout, ",");
            first_row = 0;
            
            fprintf(stdout, "{\"USER_ID\":%d,\"USERNAME\":\"%s\",\"EMAIL\":\"%s\",\"PASSWORD\":\"%s\",\"CREATED_AT\":\"%s\"}",
                   user_id, username, email, password, created_at);
        }
        
        /* EXEC SQL CLOSE c_id; */ 
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 5;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )128;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 133 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    }

    fprintf(stdout, "]}");
}

// Execute INSERT/UPDATE/DELETE with bind variables
int execute_dml(const char* sql, const char* json_binds) {
    /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 141 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    char sql_stmt[2000];
    char bind_username[200];
    char bind_email[200];
    char bind_password[500];
    /* EXEC SQL END DECLARE SECTION; */ 
#line 146 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"


    strncpy(sql_stmt, sql, sizeof(sql_stmt) - 1);
    sql_stmt[sizeof(sql_stmt) - 1] = '\0';

    // Initialize bind variables
    bind_username[0] = '\0';
    bind_email[0] = '\0';
    bind_password[0] = '\0';

    // Parse bind variables from JSON
    if (json_binds) {
        extract_json_string(json_binds, "username", bind_username, sizeof(bind_username));
        extract_json_string(json_binds, "email", bind_email, sizeof(bind_email));
        extract_json_string(json_binds, "password", bind_password, sizeof(bind_password));
    }

    /* EXEC SQL WHENEVER SQLERROR DO sql_error(); */ 
#line 163 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"


    // Handle INSERT INTO users
    if (strstr(sql, "INSERT INTO users")) {
        /* EXEC SQL INSERT INTO users (username, email, password)
            VALUES (:bind_username, :bind_email, :bind_password); */ 
#line 168 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 5;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.stmt = "insert into users (username,email,password) values (:\
b0,:b1,:b2)";
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )143;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[0] = (         void  *)bind_username;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[0] = (unsigned int  )200;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[0] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[0] = (         void  *)0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[0] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[0] = (unsigned int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[0] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[0] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[1] = (         void  *)bind_email;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[1] = (unsigned int  )200;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[1] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[1] = (         void  *)0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[1] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[1] = (unsigned int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[1] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[1] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[2] = (         void  *)bind_password;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[2] = (unsigned int  )500;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[2] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[2] = (         void  *)0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[2] = (         int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[2] = (unsigned int  )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[2] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[2] = (unsigned short )0;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsv = sqlstm.sqhstv;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsl = sqlstm.sqhstl;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphss = sqlstm.sqhsts;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpind = sqlstm.sqindv;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpins = sqlstm.sqinds;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparm = sqlstm.sqharm;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparc = sqlstm.sqharc;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpadto = sqlstm.sqadto;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqptdso = sqlstm.sqtdso;
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 167 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 168 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    } else {
        // Generic DML (for future expansion)
        /* EXEC SQL EXECUTE IMMEDIATE :sql_stmt; */ 
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        struct sqlexd sqlstm;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlvsn = 13;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.arrsiz = 5;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqladtp = &sqladt;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqltdsp = &sqltds;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.stmt = "";
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.iters = (unsigned int  )1;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.offset = (unsigned int  )170;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.cud = sqlcud0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstv[0] = (         void  *)sql_stmt;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhstl[0] = (unsigned int  )2000;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqhsts[0] = (         int  )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqindv[0] = (         void  *)0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqinds[0] = (         int  )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqharm[0] = (unsigned int  )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqadto[0] = (unsigned short )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqtdso[0] = (unsigned short )0;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsv = sqlstm.sqhstv;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphsl = sqlstm.sqhstl;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqphss = sqlstm.sqhsts;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpind = sqlstm.sqindv;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpins = sqlstm.sqinds;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparm = sqlstm.sqharm;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqparc = sqlstm.sqharc;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqpadto = sqlstm.sqadto;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlstm.sqptdso = sqlstm.sqtdso;
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
        if (sqlca.sqlcode < 0) sql_error();
#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 171 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    }

    if (sqlca.sqlcode != 0 && sqlca.sqlcode != 1403) {
        return sqlca.sqlcode;
    }

    /* EXEC SQL COMMIT; */ 
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

{
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    struct sqlexd sqlstm;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.sqlvsn = 13;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.arrsiz = 5;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.sqladtp = &sqladt;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.sqltdsp = &sqltds;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.iters = (unsigned int  )1;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.offset = (unsigned int  )189;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.cud = sqlcud0;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
    if (sqlca.sqlcode < 0) sql_error();
#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"
}

#line 178 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\query_runner.pc"

    return 0;
}

