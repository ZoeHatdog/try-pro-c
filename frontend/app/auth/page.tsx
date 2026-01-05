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
  const [success, setSuccess] = useState<string | null>(null);
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    password: '',
    confirmPassword: '',
  });
  const [fieldErrors, setFieldErrors] = useState<Record<string, string>>({});

  const validateForm = (): boolean => {
    const errors: Record<string, string> = {};
    
    if (!isLogin) {
      if (!formData.name || formData.name.trim().length < 2) {
        errors.name = 'Name must be at least 2 characters long';
      }
      
      if (formData.password !== formData.confirmPassword) {
        errors.confirmPassword = 'Passwords do not match';
      }
    }
    
    if (!formData.email || !/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(formData.email)) {
      errors.email = 'Please provide a valid email address';
    }
    
    if (!formData.password || formData.password.length < 6) {
      errors.password = 'Password must be at least 6 characters long';
    }
    
    setFieldErrors(errors);
    return Object.keys(errors).length === 0;
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setError(null);
    setSuccess(null);
    setFieldErrors({});
    setIsLoading(true);

    // Client-side validation
    if (!validateForm()) {
      setIsLoading(false);
      return;
    }

    try {
      if (isLogin) {
        const loginData: LoginData = {
          email: formData.email,
          password: formData.password,
        };
        const response = await authApi.login(loginData);
        
        if (response.success) {
          // Redirect to success page
          router.push('/success');
        } else {
          const errorMessage = response.errorCode 
            ? `${response.message} (Error: ${response.errorCode})`
            : response.message || 'Login failed';
          setError(errorMessage);
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
          setSuccess('Account created successfully! Please sign in.');
          // Reset form and switch to login mode
          setTimeout(() => {
            setFormData({
              name: '',
              email: formData.email, // Keep email for convenience
              password: '',
              confirmPassword: '',
            });
            setIsLogin(true);
            setSuccess(null);
          }, 2000);
        } else {
          // Handle field-specific errors
          if (response.field && response.errors) {
            const fieldError = Array.isArray(response.errors) 
              ? response.errors.join(', ')
              : response.errors;
            setFieldErrors({ [response.field]: fieldError });
          } else if (response.errors && Array.isArray(response.errors)) {
            // Multiple validation errors
            const errors: Record<string, string> = {};
            response.errors.forEach((err: string) => {
              if (err.toLowerCase().includes('name')) errors.name = err;
              else if (err.toLowerCase().includes('email')) errors.email = err;
              else if (err.toLowerCase().includes('password')) errors.password = err;
            });
            setFieldErrors(errors);
            setError(response.errors.join(', '));
          } else {
            const errorMessage = response.errorCode 
              ? `${response.message} (Error Code: ${response.errorCode})`
              : response.message || 'Registration failed';
            setError(errorMessage);
            
            // Set field-specific error if provided
            if (response.field) {
              setFieldErrors({ [response.field]: response.message });
            }
          }
        }
      }
    } catch (err: any) {
      let errorMessage = 'An unexpected error occurred';
      
      if (err.response?.data) {
        const data = err.response.data;
        errorMessage = data.errorCode 
          ? `${data.message} (Error Code: ${data.errorCode})`
          : data.message || errorMessage;
        
        if (data.field) {
          setFieldErrors({ [data.field]: data.message });
        }
      } else if (err.message) {
        errorMessage = err.message;
      }
      
      setError(errorMessage);
    } finally {
      setIsLoading(false);
    }
  };

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;
    setFormData({
      ...formData,
      [name]: value,
    });
    // Clear field error when user starts typing
    if (fieldErrors[name]) {
      setFieldErrors({
        ...fieldErrors,
        [name]: '',
      });
    }
    // Clear general error when user starts typing
    if (error) {
      setError(null);
    }
    if (success) {
      setSuccess(null);
    }
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
            onClick={() => {
              setIsLogin(true);
              setError(null);
              setSuccess(null);
              setFieldErrors({});
            }}
            className={`relative z-10 flex-1 rounded-xl py-3 text-sm font-medium transition-colors duration-300 ${
              isLogin
                ? 'text-white dark:text-zinc-900'
                : 'text-zinc-600 hover:text-zinc-900 dark:text-zinc-400 dark:hover:text-zinc-100'
            }`}
          >
            Sign In
          </button>
          <button
            onClick={() => {
              setIsLogin(false);
              setError(null);
              setSuccess(null);
              setFieldErrors({});
            }}
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
              <div className="flex items-start">
                <svg className="mr-2 h-5 w-5 flex-shrink-0" fill="currentColor" viewBox="0 0 20 20">
                  <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clipRule="evenodd" />
                </svg>
                <span>{error}</span>
              </div>
            </div>
          )}

          {success && (
            <div className="mb-4 rounded-xl bg-green-50 p-4 text-sm text-green-800 dark:bg-green-900/20 dark:text-green-400">
              <div className="flex items-start">
                <svg className="mr-2 h-5 w-5 flex-shrink-0" fill="currentColor" viewBox="0 0 20 20">
                  <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z" clipRule="evenodd" />
                </svg>
                <span>{success}</span>
              </div>
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
                  className={`w-full rounded-xl border px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:outline-none focus:ring-2 focus:ring-offset-2 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 ${
                    fieldErrors.name
                      ? 'border-red-300 bg-red-50 focus:border-red-500 focus:ring-red-500 dark:border-red-700 dark:bg-red-900/20 dark:focus:border-red-500'
                      : 'border-zinc-200 bg-white focus:border-zinc-900 focus:ring-zinc-900 dark:border-zinc-700 dark:focus:border-zinc-50 dark:focus:ring-zinc-50'
                  }`}
                  placeholder="John Doe"
                />
                {fieldErrors.name && (
                  <p className="mt-1 text-xs text-red-600 dark:text-red-400">{fieldErrors.name}</p>
                )}
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
                className={`w-full rounded-xl border px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:outline-none focus:ring-2 focus:ring-offset-2 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 ${
                  fieldErrors.email
                    ? 'border-red-300 bg-red-50 focus:border-red-500 focus:ring-red-500 dark:border-red-700 dark:bg-red-900/20 dark:focus:border-red-500'
                    : 'border-zinc-200 bg-white focus:border-zinc-900 focus:ring-zinc-900 dark:border-zinc-700 dark:focus:border-zinc-50 dark:focus:ring-zinc-50'
                }`}
                placeholder="you@example.com"
              />
              {fieldErrors.email && (
                <p className="mt-1 text-xs text-red-600 dark:text-red-400">{fieldErrors.email}</p>
              )}
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
                className={`w-full rounded-xl border px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:outline-none focus:ring-2 focus:ring-offset-2 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 ${
                  fieldErrors.password
                    ? 'border-red-300 bg-red-50 focus:border-red-500 focus:ring-red-500 dark:border-red-700 dark:bg-red-900/20 dark:focus:border-red-500'
                    : 'border-zinc-200 bg-white focus:border-zinc-900 focus:ring-zinc-900 dark:border-zinc-700 dark:focus:border-zinc-50 dark:focus:ring-zinc-50'
                }`}
                placeholder="••••••••"
              />
              {fieldErrors.password && (
                <p className="mt-1 text-xs text-red-600 dark:text-red-400">{fieldErrors.password}</p>
              )}
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
                  className={`w-full rounded-xl border px-4 py-3 text-sm text-zinc-900 placeholder-zinc-400 transition-all focus:outline-none focus:ring-2 focus:ring-offset-2 dark:bg-zinc-800 dark:text-zinc-50 dark:placeholder-zinc-500 ${
                    fieldErrors.confirmPassword
                      ? 'border-red-300 bg-red-50 focus:border-red-500 focus:ring-red-500 dark:border-red-700 dark:bg-red-900/20 dark:focus:border-red-500'
                      : 'border-zinc-200 bg-white focus:border-zinc-900 focus:ring-zinc-900 dark:border-zinc-700 dark:focus:border-zinc-50 dark:focus:ring-zinc-50'
                  }`}
                  placeholder="••••••••"
                />
                {fieldErrors.confirmPassword && (
                  <p className="mt-1 text-xs text-red-600 dark:text-red-400">{fieldErrors.confirmPassword}</p>
                )}
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
                onClick={() => {
                  setIsLogin(false);
                  setError(null);
                  setSuccess(null);
                  setFieldErrors({});
                }}
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
                onClick={() => {
                  setIsLogin(true);
                  setError(null);
                  setSuccess(null);
                  setFieldErrors({});
                }}
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
