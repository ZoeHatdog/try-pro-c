const express = require('express');
const cors = require('cors');
const dotenv = require('dotenv');
const authRoutes = require('./routes/auth.routes');
const { errorHandler } = require('./middleware/error.middleware');
const { initializePool, closePool } = require('./db/connection');
const { initializeDatabase } = require('./db/init-db');

// Load environment variables
dotenv.config();

const app = express();
const PORT = process.env.PORT || 5000;

// Middleware
app.use(
  cors({
    origin: process.env.FRONTEND_URL || 'http://localhost:3000',
    credentials: true,
  })
);
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Health check
app.get('/health', (req, res) => {
  res.json({ status: 'ok', message: 'Server is running' });
});

// Routes
app.use('/api/auth', authRoutes);

// Error handling middleware (must be last)
app.use(errorHandler);

// Initialize database connection pool and tables
// Initialize database connection pool and tables
initializePool()
  .then(() => {
    // Skip database initialization for Pro*C (tables should be created manually)
    console.log('✅ Pro*C connection service ready');
    console.log('⚠️  Note: Database tables must be created manually');
  })
  .catch((err) => {
    console.error('Failed to initialize database:', err);
    // Don't exit - allow server to start anyway
    console.log('⚠️  Server starting without database initialization');
  });

// Graceful shutdown
process.on('SIGTERM', async () => {
  console.log('SIGTERM received, closing database pool...');
  await closePool();
  process.exit(0);
});

process.on('SIGINT', async () => {
  console.log('SIGINT received, closing database pool...');
  await closePool();
  process.exit(0);
});

// Start server
app.listen(PORT, () => {
  console.log(`🚀 Server running on port ${PORT}`);
  console.log(`📍 Environment: ${process.env.NODE_ENV || 'development'}`);
});

module.exports = app;
