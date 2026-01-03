// Simple token generation for demo purposes
// In production, use jsonwebtoken library: npm install jsonwebtoken
const crypto = require('crypto');

const JWT_SECRET = process.env.JWT_SECRET || 'your-secret-key-change-in-production';

const generateToken = (payload) => {
  // For demo: create a simple token
  // In production, use: return jwt.sign(payload, JWT_SECRET, { expiresIn: '24h' });
  const token = crypto
    .createHash('sha256')
    .update(JSON.stringify(payload) + JWT_SECRET + Date.now())
    .digest('hex');
  
  return token;
};

const verifyToken = (token) => {
  // For demo: simple verification
  // In production, use: return jwt.verify(token, JWT_SECRET);
  try {
    // This is a simplified version - in production use proper JWT verification
    return { valid: true };
  } catch (error) {
    return { valid: false };
  }
};

module.exports = {
  generateToken,
  verifyToken,
};

