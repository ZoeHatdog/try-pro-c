'use client';

import { useState } from 'react';
import { useRouter } from 'next/navigation';
import { authApi } from '@/lib/api/auth';
import type { RegisterData, LoginData } from '@/lib/api/auth';

export default function AuthPage() {
  const router = useRouter();
  const [isLogin, setIsLogin] = useState(true);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    password: '',
    confirmPassword: '',
  });

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setError(null);
    setIsLoading(true);

    try {
      if (isLogin) {
        const loginData: LoginData = {
          email: formData.email,
          password: formData.password,
        };
        const response = await authApi.login(loginData);
        
        if (response.success) {
          // Redirect to home or dashboard
          router.push('/');
        } else {
          setError(response.message || 'Login failed');
        }
      } else {
        const registerData: RegisterData = {
          name: formData.name,
          email: formData.email,
          password: formData.password,
          confirmPassword: formData.confirmPassword,
        };
        const response = await authApi.register(registerData);
        
        if (response.success) {
          // Redirect to home or dashboard
          router.push('/');
        } else {
          const errorMessage = response.errors?.join(', ') || response.message || 'Registration failed';
          setError(errorMessage);
        }
      }
    } catch (err) {
      setError(err instanceof Error ? err.message : 'An error occurred');
    } finally {
      setIsLoading(false);
    }
  };

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value,
    });
  };

  return (
    <div className="flex min-h-screen items-center justify-center bg-gradient-to-br from-zinc-50 via-white to-zinc-100 px-4 py-12 dark:from-zinc-950 dark:via-black dark:to-zinc-900">
      <div className="w-full max-w-md">
        {/* Toggle Buttons with Slider */}
        <div className="relative mb-8 flex rounded-2xl bg-white/80 p-1.5 shadow-lg backdrop-blur-sm dark:bg-zinc-900/80">
          {/* Sliding Background */}
          <div
            className={`absolute top-1.5 bottom-1.5 rounded-xl bg-zinc-900 shadow-md transition-all duration-300 ease-in-out dark:bg-zinc-50 ${
              isLogin ? 'left-1.5 right-1/2' : 'left-1/2 right-1.5'
            }`}
          />
          <button
            onClick={() => setIsLogin(true)}
            className={`relative z-10 flex-1 rounded-xl py-3 text-sm font-medium transition-colors duration-300 ${
              isLogin
                ? 'text-white dark:text-zinc-900'
                : 'text-zinc-600 hover:text-zinc-900 dark:text-zinc-400 dark:hover:text-zinc-100'
            }`}
          >
            Sign In
          </button>
          <button
            onClick={() => setIsLogin(false)}
            className={`relative z-10 flex-1 rounded-xl py-3 text-sm font-medium transition-colors duration-300 ${
              !isLogin
                ? 'text-white dark:text-zinc-900'
                : 'text-zinc-600 hover:text-zinc-900 dark:text-zinc-400 dark:hover:text-zinc-100'
            }`}
          >
            Sign Up
          </button>
        </div>

        {/* Form Card */}
        <div className="rounded-2xl bg-white/80 p-8 shadow-xl backdrop-blur-sm dark:bg-zinc-900/80">
          <div className="mb-8 text-center">
            <h1 className="mb-2 text-3xl font-semibold text-zinc-900 dark:text-zinc-50">
              {isLogin ? 'Welcome back' : 'Create account'}
            </h1>
            <p className="text-sm text-zinc-600 dark:text-zinc-400">
              {isLogin
                ? 'Sign in to continue to your account'
                : 'Get started with your free account today'}
            </p>
          </div>

          {error && (
            <div className="mb-4 rounded-xl bg-red-50 p-4 text-sm text-red-800 dark:bg-red-900/20 dark:text-red-400">
              {error}
            </div>
          )}

          <form onSubmit={handleSubmit} className="space-y-5">
            {!isLogin && (
              <div className="animate-in fade-in slide-in-from-top-2 duration-300">
                <label
                  htmlFor="name"
                  className="mb-2 block text-sm font-medium text-zinc-700 dark:text-zinc-300"
                >
                  Full Name
                </label>
                <input
                  type="text"
                  id="name"
                  name="name"
                  value={formData.name}
                  onChange={handleChange}
                  required={!isLogin}
                  className="w-full rounded-xl border border-zinc-200 bg-white px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:border-zinc-900 focus:outline-none focus:ring-2 focus:ring-zinc-900 focus:ring-offset-2 dark:border-zinc-700 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 dark:focus:border-zinc-50 dark:focus:ring-zinc-50"
                  placeholder="John Doe"
                />
              </div>
            )}

            <div>
              <label
                htmlFor="email"
                className="mb-2 block text-sm font-medium text-zinc-700 dark:text-zinc-300"
              >
                Email
              </label>
              <input
                type="email"
                id="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
                required
                className="w-full rounded-xl border border-zinc-200 bg-white px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:border-zinc-900 focus:outline-none focus:ring-2 focus:ring-zinc-900 focus:ring-offset-2 dark:border-zinc-700 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 dark:focus:border-zinc-50 dark:focus:ring-zinc-50"
                placeholder="you@example.com"
              />
            </div>

            <div>
              <label
                htmlFor="password"
                className="mb-2 block text-sm font-medium text-zinc-700 dark:text-zinc-300"
              >
                Password
              </label>
              <input
                type="password"
                id="password"
                name="password"
                value={formData.password}
                onChange={handleChange}
                required
                className="w-full rounded-xl border border-zinc-200 bg-white px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:border-zinc-900 focus:outline-none focus:ring-2 focus:ring-zinc-900 focus:ring-offset-2 dark:border-zinc-700 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 dark:focus:border-zinc-50 dark:focus:ring-zinc-50"
                placeholder="••••••••"
              />
            </div>

            {!isLogin && (
              <div className="animate-in fade-in slide-in-from-top-2 duration-300">
                <label
                  htmlFor="confirmPassword"
                  className="mb-2 block text-sm font-medium text-zinc-700 dark:text-zinc-300"
                >
                  Confirm Password
                </label>
                <input
                  type="password"
                  id="confirmPassword"
                  name="confirmPassword"
                  value={formData.confirmPassword}
                  onChange={handleChange}
                  required={!isLogin}
                  className="w-full rounded-xl border border-zinc-200 bg-white px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:border-zinc-900 focus:outline-none focus:ring-2 focus:ring-zinc-900 focus:ring-offset-2 dark:border-zinc-700 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 dark:focus:border-zinc-50 dark:focus:ring-zinc-50"
                  placeholder="••••••••"
                />
              </div>
            )}

            {isLogin && (
              <div className="flex items-center justify-between text-sm">
                <label className="flex items-center">
                  <input
                    type="checkbox"
                    className="mr-2 h-4 w-4 rounded border-zinc-300 text-zinc-900 focus:ring-2 focus:ring-zinc-900 dark:border-zinc-600 dark:bg-zinc-800 dark:focus:ring-zinc-50"
                  />
                  <span className="text-zinc-600 dark:text-zinc-400">
                    Remember me
                  </span>
                </label>
                <a
                  href="#"
                  className="font-medium text-zinc-900 hover:text-zinc-700 dark:text-zinc-50 dark:hover:text-zinc-300"
                >
                  Forgot password?
                </a>
              </div>
            )}

            <button
              type="submit"
              disabled={isLoading}
              className="w-full rounded-xl bg-zinc-900 px-4 py-3 text-sm font-semibold text-white transition-all hover:bg-zinc-800 focus:outline-none focus:ring-2 focus:ring-zinc-900 focus:ring-offset-2 active:scale-[0.98] disabled:cursor-not-allowed disabled:opacity-50 dark:bg-zinc-50 dark:text-zinc-900 dark:hover:bg-zinc-100 dark:focus:ring-zinc-50"
            >
              {isLoading ? (
                <span className="flex items-center justify-center">
                  <svg
                    className="mr-2 h-4 w-4 animate-spin"
                    xmlns="http://www.w3.org/2000/svg"
                    fill="none"
                    viewBox="0 0 24 24"
                  >
                    <circle
                      className="opacity-25"
                      cx="12"
                      cy="12"
                      r="10"
                      stroke="currentColor"
                      strokeWidth="4"
                    ></circle>
                    <path
                      className="opacity-75"
                      fill="currentColor"
                      d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"
                    ></path>
                  </svg>
                  {isLogin ? 'Signing in...' : 'Creating account...'}
                </span>
              ) : (
                isLogin ? 'Sign In' : 'Create Account'
              )}
            </button>
          </form>

          {isLogin && (
            <div className="mt-6 text-center text-sm text-zinc-600 dark:text-zinc-400">
              Don't have an account?{' '}
              <button
                onClick={() => setIsLogin(false)}
                className="font-semibold text-zinc-900 hover:text-zinc-700 dark:text-zinc-50 dark:hover:text-zinc-300"
              >
                Sign up
              </button>
            </div>
          )}

          {!isLogin && (
            <div className="mt-6 text-center text-sm text-zinc-600 dark:text-zinc-400">
              Already have an account?{' '}
              <button
                onClick={() => setIsLogin(true)}
                className="font-semibold text-zinc-900 hover:text-zinc-700 dark:text-zinc-50 dark:hover:text-zinc-300"
              >
                Sign in
              </button>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}

