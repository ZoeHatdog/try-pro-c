# Pro*C Integration - Child Process Approach

This integration replaces the Node.js `oracledb` package with Pro*C using a child process approach.

## Architecture

1. **Pro*C Executable** (`db_query_service.exe`)
   - Accepts JSON input via stdin
   - Executes SQL queries using Pro*C embedded SQL
   - Returns JSON output via stdout

2. **Node.js Backend** (`backend/src/db/connection.js`)
   - Spawns Pro*C process for each query
   - Communicates via stdin/stdout
   - Parses JSON responses

## Build Steps

### 1. Build Pro*C Service Executable

```powershell
cd pro-c/proc-oracle-xe-app
.\build-service.ps1
```

This will create `db_query_service.exe` in the `pro-c/proc-oracle-xe-app/` directory.

**Requirements:**
- Oracle Instant Client with Pro*C precompiler
- GCC compiler (MinGW on Windows)
- ORACLE_HOME environment variable set

### 2. Install Backend Dependencies

```bash
cd backend
npm install
```

**Note:** The `oracledb` package has been removed from dependencies.

### 3. Configure Environment Variables

Create/update `.env` file in `backend/`:

```
ORACLE_USER=system
ORACLE_PASSWORD=password
ORACLE_DATABASE=localhost:1521/XE
PORT=5000
NODE_ENV=development
FRONTEND_URL=http://localhost:3000
JWT_SECRET=your-secret-key
```

### 4. Run Backend

```bash
cd backend
npm run dev
```

## How It Works

### Query Flow

1. **Backend receives request** → `backend/src/db/connection.js`
2. **Spawns Pro*C process** → `db_query_service.exe`
3. **Sends JSON request** via stdin:
   ```json
   {
     "sql": "SELECT user_id, username, email, password, created_at FROM users WHERE email = :email",
     "binds": {"email": "user@example.com"},
     "options": {"autoCommit": true}
   }
   ```
4. **Pro*C executes query** using embedded SQL
5. **Returns JSON response** via stdout:
   ```json
   {
     "rows": [
       {
         "USER_ID": 1,
         "USERNAME": "John Doe",
         "EMAIL": "user@example.com",
         "PASSWORD": "hashed_password",
         "CREATED_AT": "2024-01-01 12:00:00"
       }
     ]
   }
   ```
6. **Backend parses response** and returns to calling code

## Supported Queries

Currently, the Pro*C service supports:

### SELECT Queries
- `SELECT ... FROM users WHERE email = :email`
- `SELECT ... FROM users WHERE user_id = :id` (or `:user_id`)

### INSERT Queries
- `INSERT INTO users (username, email, password) VALUES (:username, :email, :password)`

### Future Enhancements
- Generic SELECT queries
- UPDATE/DELETE statements
- DDL statements (CREATE TABLE, etc.)

## Files

### Pro*C Code
- `pro-c/proc-oracle-xe-app/src/db/connection.pc` - Database connection
- `pro-c/proc-oracle-xe-app/src/db/query_runner.pc` - Query execution logic
- `pro-c/proc-oracle-xe-app/src/db_query_service.pc` - Main service entry point
- `pro-c/proc-oracle-xe-app/build-service.ps1` - Build script

### Node.js Code
- `backend/src/db/connection.js` - Pro*C process wrapper (replaces oracledb)
- `backend/src/models/User.model.js` - Uses connection.js (no changes needed)

## Troubleshooting

### Pro*C executable not found
- Ensure `db_query_service.exe` exists in `pro-c/proc-oracle-xe-app/`
- Run `build-service.ps1` to build it

### Connection errors
- Check Oracle database is running
- Verify ORACLE_USER, ORACLE_PASSWORD, ORACLE_DATABASE environment variables
- Ensure Oracle Instant Client is installed

### JSON parsing errors
- Check Pro*C executable output format
- Verify JSON response is valid
- Check stdout/stderr from Pro*C process

## Performance Notes

- Each query spawns a new process (some overhead)
- Consider connection pooling in future (more complex Pro*C implementation)
- Suitable for moderate traffic applications
- For high performance, consider native addon approach (Option 1)

## Next Steps

1. Enhance Pro*C code to support more query types
2. Add proper error handling and logging
3. Consider connection pooling (keep Pro*C process alive)
4. Add query result caching if needed
5. Optimize JSON parsing performance


