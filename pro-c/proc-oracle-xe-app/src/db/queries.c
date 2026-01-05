
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
           char  filnam[92];
};
static const struct sqlcxp sqlfpn =
{
    91,
    "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
};


static unsigned int sqlctx = 620150877;


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
5,0,0,1,0,0,17,21,0,0,1,1,0,1,0,1,97,0,0,
24,0,0,1,0,0,45,23,0,0,0,0,0,1,0,
39,0,0,1,0,0,13,26,0,0,1,0,0,1,0,2,97,0,0,
58,0,0,1,0,0,15,36,0,0,0,0,0,1,0,
};


#line 1 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlca.h>
#include "db.h"

void sql_error();

void execute_query(const char* query) {
    /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 10 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

    char query_str[1000];
    char result[100];
    /* EXEC SQL END DECLARE SECTION; */ 
#line 13 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"


    // Copy the query string into a host variable
    strncpy(query_str, query, sizeof(query_str) - 1);
    query_str[sizeof(query_str) - 1] = '\0';

    /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 
#line 19 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"


    /* EXEC SQL PREPARE stmt FROM :query_str; */ 
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

{
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    struct sqlexd sqlstm;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlvsn = 13;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.arrsiz = 1;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqladtp = &sqladt;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqltdsp = &sqltds;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.stmt = "";
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.iters = (unsigned int  )1;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.offset = (unsigned int  )5;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.cud = sqlcud0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqhstv[0] = (         void  *)query_str;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqhstl[0] = (unsigned int  )1000;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqhsts[0] = (         int  )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqindv[0] = (         void  *)0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqinds[0] = (         int  )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqharm[0] = (unsigned int  )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqadto[0] = (unsigned short )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqtdso[0] = (unsigned short )0;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqphsv = sqlstm.sqhstv;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqphsl = sqlstm.sqhstl;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqphss = sqlstm.sqhsts;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqpind = sqlstm.sqindv;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqpins = sqlstm.sqinds;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqparm = sqlstm.sqharm;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqparc = sqlstm.sqharc;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqpadto = sqlstm.sqadto;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqptdso = sqlstm.sqtdso;
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
}

#line 21 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

    /* EXEC SQL DECLARE c_cursor CURSOR FOR stmt; */ 
#line 22 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

    /* EXEC SQL OPEN c_cursor; */ 
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

{
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    struct sqlexd sqlstm;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlvsn = 13;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.arrsiz = 1;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqladtp = &sqladt;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqltdsp = &sqltds;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.stmt = "";
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.iters = (unsigned int  )1;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.offset = (unsigned int  )24;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.selerr = (unsigned short)1;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlpfmem = (unsigned int  )0;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.cud = sqlcud0;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqcmod = (unsigned int )0;
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
}

#line 23 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"


    while (1) {
        /* EXEC SQL FETCH c_cursor INTO :result; */ 
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

{
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        struct sqlexd sqlstm;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqlvsn = 13;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.arrsiz = 1;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqladtp = &sqladt;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqltdsp = &sqltds;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.iters = (unsigned int  )1;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.offset = (unsigned int  )39;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.selerr = (unsigned short)1;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqlpfmem = (unsigned int  )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.cud = sqlcud0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqlety = (unsigned short)4352;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.occurs = (unsigned int  )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqfoff = (           int )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqfmod = (unsigned int )2;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqhstv[0] = (         void  *)result;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqhstl[0] = (unsigned int  )100;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqhsts[0] = (         int  )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqindv[0] = (         void  *)0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqinds[0] = (         int  )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqharm[0] = (unsigned int  )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqadto[0] = (unsigned short )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqtdso[0] = (unsigned short )0;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqphsv = sqlstm.sqhstv;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqphsl = sqlstm.sqhstl;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqphss = sqlstm.sqhsts;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqpind = sqlstm.sqindv;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqpins = sqlstm.sqinds;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqparm = sqlstm.sqharm;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqparc = sqlstm.sqharc;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqpadto = sqlstm.sqadto;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlstm.sqptdso = sqlstm.sqtdso;
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
}

#line 26 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

        if (sqlca.sqlcode == 100) {
            break; // No more rows
        } else if (sqlca.sqlcode != 0) {
            printf("Error fetching data: %.*s\n", sqlca.sqlerrm.sqlerrml, sqlca.sqlerrm.sqlerrmc);
            break;
        }
        printf("Result: %s\n", result);
    }

    /* EXEC SQL CLOSE c_cursor; */ 
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

{
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    struct sqlexd sqlstm;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlvsn = 13;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.arrsiz = 1;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqladtp = &sqladt;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqltdsp = &sqltds;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.iters = (unsigned int  )1;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.offset = (unsigned int  )58;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.cud = sqlcud0;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.sqlety = (unsigned short)4352;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlstm.occurs = (unsigned int  )0;
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"
}

#line 36 "C:\\Users\\arnel\\Downloads\\Side-Projects\\try-pro-c\\pro-c\\proc-oracle-xe-app\\src\\db\\queries.pc"

}

void get_all_records() {
    const char* query = "SELECT * FROM users";
    execute_query(query);
}