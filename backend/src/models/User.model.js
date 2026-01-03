// In-memory storage for demo purposes
// In production, replace this with actual database operations (MongoDB, PostgreSQL, etc.)
const users = [];

class User {
  constructor({ id, name, email, password }) {
    this.id = id;
    this.name = name;
    this.email = email;
    this.password = password;
    this.createdAt = new Date();
  }

  static async create(userData) {
    const id = users.length + 1;
    const user = new User({ ...userData, id });
    users.push(user);
    return user;
  }

  static async findByEmail(email) {
    return users.find(user => user.email === email) || null;
  }

  static async findById(id) {
    return users.find(user => user.id === id) || null;
  }

  toJSON() {
    const { password, ...userWithoutPassword } = this;
    return userWithoutPassword;
  }
}

module.exports = User;

