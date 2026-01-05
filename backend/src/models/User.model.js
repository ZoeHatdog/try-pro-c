const { executeQuery } = require('../db/connection');

class User {
  constructor({ user_id, username, email, password, created_at }) {
    this.id = user_id;
    this.name = username;
    this.email = email;
    this.password = password;
    this.createdAt = created_at;
  }

  static async create(userData) {
    const { name, email, password } = userData;
    
    try {
      // Insert user
      const insertSql = `
        INSERT INTO users (username, email, password)
        VALUES (:username, :email, :password)
      `;
      
      await executeQuery(insertSql, {
        username: name,
        email: email,
        password: password,
      }, { autoCommit: true });

      // Fetch the created user
      const fetchSql = `
        SELECT user_id, username, email, password, created_at
        FROM users
        WHERE email = :email
      `;
      
      const result = await executeQuery(fetchSql, { email });
      
      if (result.rows && result.rows.length > 0) {
        const row = result.rows[0];
        return new User({
          user_id: row.USER_ID,
          username: row.USERNAME,
          email: row.EMAIL,
          password: row.PASSWORD, // Use stored password
          created_at: row.CREATED_AT,
        });
      }
      
      throw new Error('Failed to create user');
    } catch (err) {
      // Handle unique constraint violations (ORA-00001)
      if (err.originalError && (err.originalError.errorNum === 1 || err.message?.includes('ORA-00001'))) {
        throw {
          code: 'DUPLICATE_EMAIL',
          message: 'User with this email already exists',
          field: 'email',
        };
      }
      throw err;
    }
  }

  static async findByEmail(email) {
    try {
      const sql = `
        SELECT user_id, username, email, password, created_at
        FROM users
        WHERE email = :email
      `;
      
      const result = await executeQuery(sql, { email });
      
      if (result.rows && result.rows.length > 0) {
        const row = result.rows[0];
        return new User({
          user_id: row.USER_ID,
          username: row.USERNAME,
          email: row.EMAIL,
          password: row.PASSWORD,
          created_at: row.CREATED_AT,
        });
      }
      
      return null;
    } catch (err) {
      throw err;
    }
  }

  static async findById(id) {
    try {
      const sql = `
        SELECT user_id, username, email, password, created_at
        FROM users
        WHERE user_id = :id
      `;
      
      const result = await executeQuery(sql, { id: parseInt(id) });
      
      if (result.rows && result.rows.length > 0) {
        const row = result.rows[0];
        return new User({
          user_id: row.USER_ID,
          username: row.USERNAME,
          email: row.EMAIL,
          password: row.PASSWORD,
          created_at: row.CREATED_AT,
        });
      }
      
      return null;
    } catch (err) {
      throw err;
    }
  }

  toJSON() {
    const { password, ...userWithoutPassword } = this;
    return userWithoutPassword;
  }
}

module.exports = User;
