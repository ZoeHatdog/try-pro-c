
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
           char  filnam[95];
};
static const struct sqlcxp sqlfpn =
{
    94,
    "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
};


static unsigned int sqlctx = 666302053;


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
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {13,4};

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
5,0,0,0,0,0,27,29,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
36,0,0,2,0,0,30,41,0,0,0,0,0,1,0,
51,0,0,3,0,0,32,53,0,0,0,0,0,1,0,
};


#line 1 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlca.h>
#include "db.h"

void sql_error();

void connect_to_db() {
    /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 10 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

    char username[50];
    char password[50];
    char database[100];
    /* EXEC SQL END DECLARE SECTION; */ 
#line 14 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"


    // Get credentials from environment variables or use defaults
    const char *env_user = getenv("ORACLE_USER");
    const char *env_pass = getenv("ORACLE_PASSWORD");
    const char *env_db = getenv("ORACLE_DATABASE");

    strcpy(username, env_user ? env_user : "system");
    strcpy(password, env_pass ? env_pass : "password");
    strcpy(database, env_db ? env_db : "localhost:1521/XE");

    /* EXEC SQL WHENEVER SQLERROR DO sql_error(); */ 
#line 25 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"


    // Print connection messages to stderr (not stdout) to avoid interfering with JSON output
    fprintf(stderr, "Connecting to Oracle database: %s as %s\n", database, username);
    /* EXEC SQL CONNECT :username IDENTIFIED BY :password USING :database; */ 
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

{
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    struct sqlexd sqlstm;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlvsn = 13;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.arrsiz = 4;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqladtp = &sqladt;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqltdsp = &sqltds;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.iters = (unsigned int  )10;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.offset = (unsigned int  )5;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.cud = sqlcud0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstv[0] = (         void  *)username;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstl[0] = (unsigned int  )50;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhsts[0] = (         int  )50;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqindv[0] = (         void  *)0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqinds[0] = (         int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqharm[0] = (unsigned int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqadto[0] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqtdso[0] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstv[1] = (         void  *)password;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstl[1] = (unsigned int  )50;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhsts[1] = (         int  )50;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqindv[1] = (         void  *)0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqinds[1] = (         int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqharm[1] = (unsigned int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqadto[1] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqtdso[1] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstv[2] = (         void  *)database;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhstl[2] = (unsigned int  )100;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqhsts[2] = (         int  )100;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqindv[2] = (         void  *)0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqinds[2] = (         int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqharm[2] = (unsigned int  )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqadto[2] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqtdso[2] = (unsigned short )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqphsv = sqlstm.sqhstv;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqphsl = sqlstm.sqhstl;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqphss = sqlstm.sqhsts;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqpind = sqlstm.sqindv;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqpins = sqlstm.sqinds;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqparm = sqlstm.sqharm;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqparc = sqlstm.sqharc;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqpadto = sqlstm.sqadto;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqptdso = sqlstm.sqtdso;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlcmax = (unsigned int )100;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlcmin = (unsigned int )2;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlcincr = (unsigned int )1;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlctimeout = (unsigned int )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlcnowait = (unsigned int )0;
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    if (sqlca.sqlcode < 0) sql_error();
#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
}

#line 29 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"


    if (sqlca.sqlcode != 0) {
        fprintf(stderr, "Error connecting to the database: %.*s\n", 
               sqlca.sqlerrm.sqlerrml, sqlca.sqlerrm.sqlerrmc);
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "Connected to the database successfully.\n");
    }
}

void disconnect_from_db() {
    /* EXEC SQL COMMIT WORK RELEASE; */ 
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

{
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    struct sqlexd sqlstm;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlvsn = 13;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.arrsiz = 4;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqladtp = &sqladt;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqltdsp = &sqltds;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.iters = (unsigned int  )1;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.offset = (unsigned int  )36;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.cud = sqlcud0;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    if (sqlca.sqlcode < 0) sql_error();
#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
}

#line 41 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"


    if (sqlca.sqlcode != 0) {
        fprintf(stderr, "Error disconnecting from the database: %s\n", sqlca.sqlerrm.sqlerrmc);
    } else {
        fprintf(stderr, "Disconnected from the database successfully.\n");
    }
}

void sql_error() {
    fprintf(stderr, "SQL Error: %.*s\n", sqlca.sqlerrm.sqlerrml, sqlca.sqlerrm.sqlerrmc);
    /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 
#line 52 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

    /* EXEC SQL ROLLBACK WORK RELEASE; */ 
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

{
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    struct sqlexd sqlstm;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlvsn = 13;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.arrsiz = 4;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqladtp = &sqladt;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqltdsp = &sqltds;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.iters = (unsigned int  )1;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.offset = (unsigned int  )51;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.cud = sqlcud0;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"
}

#line 53 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\connection.pc"

    exit(EXIT_FAILURE);
}