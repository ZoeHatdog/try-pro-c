const { spawn } = require('child_process');
const path = require('path');
require('dotenv').config();

// Path to the Pro*C executable
const PROC_SERVICE_PATH = path.join(
  __dirname,
  '../../../pro-c/proc-oracle-xe-app/db_query_service.exe'
);

// Oracle connection configuration (used for environment variables)
const dbConfig = {
  user: process.env.ORACLE_USER || 'system',
  password: process.env.ORACLE_PASSWORD || 'password',
  connectString: process.env.ORACLE_DATABASE || 'localhost:1521/XE',
};

/**
 * Execute a query using Pro*C service
 * @param {string} sql - SQL query with bind variables
 * @param {object} binds - Bind variables object
 * @param {object} options - Query options (autoCommit, etc.)
 * @returns {Promise<object>} Query result
 */
async function executeQuery(sql, binds = {}, options = {}) {
  return new Promise((resolve, reject) => {
    // Prepare JSON request
    const request = {
      sql: sql,
      binds: binds,
      options: options,
    };

    const requestJson = JSON.stringify(request);

    // Set environment variables for Pro*C executable
    const env = {
      ...process.env,
      ORACLE_USER: dbConfig.user,
      ORACLE_PASSWORD: dbConfig.password,
      ORACLE_DATABASE: dbConfig.connectString,
    };

    // Spawn Pro*C process
    const proc = spawn(PROC_SERVICE_PATH, [], {
      env: env,
      stdio: ['pipe', 'pipe', 'pipe'],
    });

    let stdout = '';
    let stderr = '';

    // Collect stdout
    proc.stdout.on('data', (data) => {
      stdout += data.toString();
    });

    // Collect stderr
    proc.stderr.on('data', (data) => {
      stderr += data.toString();
    });

    // Handle process completion
    proc.on('close', (code) => {
      if (code !== 0) {
        return reject({
          code: 'PROC_ERROR',
          message: stderr || `Pro*C process exited with code ${code}`,
          originalError: { code, stderr, stdout },
        });
      }

      try {
        // Parse JSON response
        const response = JSON.parse(stdout.trim());

        // Check for errors (success field may be undefined for SELECT queries)
        if (response.error || response.success === false) {
          // Handle SQL errors
          if (response.error && (response.error.includes('ORA-00001') || response.error.includes('code: 1'))) {
            return reject({
              code: 'DUPLICATE_EMAIL',
              message: 'User with this email already exists',
              field: 'email',
              originalError: { errorNum: 1, message: response.error },
            });
          }

          return reject({
            code: 'DB_ERROR',
            message: response.error || 'Database error occurred',
            originalError: { message: response.error },
          });
        }

        // Convert rows to match oracledb format
        const result = {
          rows: response.rows || [],
          rowsAffected: response.rowsAffected || 0,
        };

        resolve(result);
      } catch (parseError) {
        reject({
          code: 'PARSE_ERROR',
          message: 'Failed to parse Pro*C response',
          originalError: { parseError, stdout, stderr },
        });
      }
    });

    // Handle spawn errors
    proc.on('error', (error) => {
      reject({
        code: 'SPAWN_ERROR',
        message: `Failed to spawn Pro*C process: ${error.message}`,
        originalError: error,
      });
    });

    // Send JSON request to stdin
    proc.stdin.write(requestJson);
    proc.stdin.end();
  });
}

/**
 * Initialize connection pool (not needed for Pro*C, but kept for compatibility)
 */
async function initializePool() {
  // Pro*C doesn't use connection pooling in the same way
  // Each query spawns a new process and connection
  console.log('Pro*C connection service ready');
}

/**
 * Get connection (not applicable for Pro*C, but kept for compatibility)
 */
async function getConnection() {
  throw new Error('getConnection() not supported with Pro*C. Use executeQuery() directly.');
}

/**
 * Close pool (not applicable for Pro*C, but kept for compatibility)
 */
async function closePool() {
  // Nothing to close - each query is independent
  console.log('Pro*C connection pool closed');
}

module.exports = {
  initializePool,
  getConnection,
  closePool,
  executeQuery,
};

