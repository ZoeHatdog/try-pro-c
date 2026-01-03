const bcrypt = require('bcryptjs');
const User = require('../models/User.model');

const createUser = async (userData) => {
  const { name, email, password } = userData;

  // Hash password
  const hashedPassword = await bcrypt.hash(password, 10);

  // Create user (in a real app, this would be a database operation)
  const user = await User.create({
    name,
    email,
    password: hashedPassword,
  });

  return user;
};

const findUserByEmail = async (email) => {
  return await User.findByEmail(email);
};

const verifyPassword = async (plainPassword, hashedPassword) => {
  return await bcrypt.compare(plainPassword, hashedPassword);
};

module.exports = {
  createUser,
  findUserByEmail,
  verifyPassword,
};

