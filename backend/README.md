# Backend API

Express.js backend server with authentication.

## Project Structure

```
backend/
├── src/
│   ├── controllers/     # Request handlers
│   ├── services/        # Business logic
│   ├── models/          # Data models
│   ├── routes/          # API routes
│   ├── middleware/      # Express middleware
│   ├── utils/           # Utility functions
│   └── server.js        # Entry point
├── .env                 # Environment variables
└── package.json
```

## Setup

1. Install dependencies:
```bash
npm install
```

2. Create `.env` file (copy from `.env.example`):
```bash
PORT=5000
NODE_ENV=development
FRONTEND_URL=http://localhost:3000
JWT_SECRET=your-super-secret-jwt-key
```

3. Start development server:
```bash
npm run dev
```

## API Endpoints

### Authentication

- `POST /api/auth/register` - Register a new user
- `POST /api/auth/login` - Login user
- `POST /api/auth/logout` - Logout user

### Health Check

- `GET /health` - Server health check

## Notes

- Currently uses in-memory storage for demo purposes
- Replace `User.model.js` with actual database operations for production
- Replace JWT utility with `jsonwebtoken` library for production use

