# Full Stack Application

A modern full-stack application with Next.js frontend and Express.js backend.

## Project Structure

```
project-root/
├── frontend/          # Next.js frontend application
│   ├── app/          # Next.js app directory
│   ├── lib/          # Utilities and API clients
│   └── public/       # Static assets
├── backend/          # Express.js backend API
│   └── src/          # Backend source code
└── README.md
```

## Getting Started

### Prerequisites

- Node.js 18+ 
- npm or yarn

### Backend Setup

1. Navigate to backend directory:
```bash
cd backend
```

2. Install dependencies:
```bash
npm install
```

3. Create `.env` file:
```bash
PORT=5000
NODE_ENV=development
FRONTEND_URL=http://localhost:3000
JWT_SECRET=your-super-secret-jwt-key
```

4. Start the backend server:
```bash
npm run dev
```

The backend will run on `http://localhost:5000`

### Frontend Setup

1. Navigate to frontend directory:
```bash
cd frontend
```

2. Install dependencies:
```bash
npm install
```

3. Create `.env.local` file:
```bash
NEXT_PUBLIC_API_URL=http://localhost:5000/api
```

4. Start the development server:
```bash
npm run dev
```

The frontend will run on `http://localhost:3000`

## Features

- ✅ User authentication (Login/Register)
- ✅ JWT token-based authentication
- ✅ Form validation
- ✅ Error handling
- ✅ Responsive design
- ✅ Dark mode support

## Tech Stack

### Frontend
- Next.js 16
- React 19
- TypeScript
- Tailwind CSS

### Backend
- Express.js 5
- Node.js
- bcryptjs (password hashing)
- CORS enabled

## Development

- Backend runs on port `5000`
- Frontend runs on port `3000`
- Make sure both servers are running for full functionality

