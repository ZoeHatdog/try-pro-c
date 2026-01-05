const errorHandler = (err, req, res, next) => {
  console.error('Error:', err);

  // Default error
  let statusCode = err.statusCode || 500;
  let message = err.message || 'Internal server error';
  let errorCode = err.errorCode || 'INTERNAL_SERVER_ERROR';

  // Handle specific error types
  if (err.name === 'ValidationError') {
    statusCode = 400;
    message = 'Validation error';
    errorCode = 'VALIDATION_ERROR';
  }

  // Handle Oracle database errors
  if (err.code === 'DB_ERROR' || err.originalError) {
    const oracleError = err.originalError || err;
    
    // Unique constraint violation
    if (oracleError.errorNum === 1) {
      statusCode = 409;
      message = 'A record with this information already exists';
      errorCode = 'DUPLICATE_ENTRY';
    }
    // Foreign key constraint violation
    else if (oracleError.errorNum === 2291) {
      statusCode = 400;
      message = 'Referenced record does not exist';
      errorCode = 'FOREIGN_KEY_VIOLATION';
    }
    // Not null constraint violation
    else if (oracleError.errorNum === 1400) {
      statusCode = 400;
      message = 'Required field is missing';
      errorCode = 'NULL_CONSTRAINT_VIOLATION';
    }
    // Connection errors
    else if (oracleError.errorNum === 1017 || oracleError.message?.includes('ORA-01017')) {
      statusCode = 503;
      message = 'Database authentication failed';
      errorCode = 'DATABASE_AUTH_ERROR';
    }
    // Generic database error
    else {
      statusCode = 503;
      message = 'Database error occurred';
      errorCode = 'DATABASE_ERROR';
    }
  }

  res.status(statusCode).json({
    success: false,
    errorCode,
    message,
    ...(process.env.NODE_ENV === 'development' && { 
      stack: err.stack,
      details: err.originalError?.message,
    }),
  });
};

module.exports = {
  errorHandler,
};
