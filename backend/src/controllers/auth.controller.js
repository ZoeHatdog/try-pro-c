const authService = require('../services/auth.service');
const { generateToken } = require('../utils/jwt.util');

const register = async (req, res, next) => {
  try {
    const { name, email, password } = req.body;

    // Check if user already exists
    const existingUser = await authService.findUserByEmail(email);
    if (existingUser) {
      return res.status(409).json({
        success: false,
        errorCode: 'USER_ALREADY_EXISTS',
        message: 'User with this email already exists',
        field: 'email',
      });
    }

    // Create new user
    const user = await authService.createUser({ name, email, password });

    // Generate JWT token
    const token = generateToken({ userId: user.id, email: user.email });

    res.status(201).json({
      success: true,
      message: 'User registered successfully',
      data: {
        user: {
          id: user.id,
          name: user.name,
          email: user.email,
        },
        token,
      },
    });
  } catch (error) {
    // Handle database-specific errors
    if (error.code === 'DUPLICATE_EMAIL') {
      return res.status(409).json({
        success: false,
        errorCode: error.code,
        message: error.message,
        field: error.field,
      });
    }
    
    // Handle database connection errors
    if (error.code === 'DB_ERROR' || error.code === 'ENOTFOUND' || error.code === 'ECONNREFUSED') {
      return res.status(503).json({
        success: false,
        errorCode: 'DATABASE_CONNECTION_ERROR',
        message: 'Unable to connect to database. Please try again later.',
      });
    }

    next(error);
  }
};

const login = async (req, res, next) => {
  try {
    const { email, password } = req.body;

    // Find user by email
    const user = await authService.findUserByEmail(email);
    if (!user) {
      return res.status(401).json({
        success: false,
        errorCode: 'INVALID_CREDENTIALS',
        message: 'Invalid email or password',
      });
    }

    // Verify password
    const isPasswordValid = await authService.verifyPassword(password, user.password);
    if (!isPasswordValid) {
      return res.status(401).json({
        success: false,
        errorCode: 'INVALID_CREDENTIALS',
        message: 'Invalid email or password',
      });
    }

    // Generate JWT token
    const token = generateToken({ userId: user.id, email: user.email });

    res.json({
      success: true,
      message: 'Login successful',
      data: {
        user: {
          id: user.id,
          name: user.name,
          email: user.email,
        },
        token,
      },
    });
  } catch (error) {
    // Handle database connection errors
    if (error.code === 'DB_ERROR' || error.code === 'ENOTFOUND' || error.code === 'ECONNREFUSED') {
      return res.status(503).json({
        success: false,
        errorCode: 'DATABASE_CONNECTION_ERROR',
        message: 'Unable to connect to database. Please try again later.',
      });
    }

    next(error);
  }
};

const logout = async (req, res) => {
  // In a stateless JWT setup, logout is handled client-side
  // You might want to implement token blacklisting here if needed
  res.json({
    success: true,
    message: 'Logout successful',
  });
};

module.exports = {
  register,
  login,
  logout,
};
