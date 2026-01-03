import { apiClient, type ApiResponse, type AuthResponse } from './client';

export interface RegisterData {
  name: string;
  email: string;
  password: string;
  confirmPassword: string;
}

export interface LoginData {
  email: string;
  password: string;
}

export const authApi = {
  register: async (data: RegisterData): Promise<ApiResponse<AuthResponse>> => {
    const response = await apiClient.post<AuthResponse>('/auth/register', {
      name: data.name,
      email: data.email,
      password: data.password,
      confirmPassword: data.confirmPassword,
    });

    // Store token in localStorage
    if (response.success && response.data?.token) {
      if (typeof window !== 'undefined') {
        localStorage.setItem('auth_token', response.data.token);
        localStorage.setItem('user', JSON.stringify(response.data.user));
      }
    }

    return response;
  },

  login: async (data: LoginData): Promise<ApiResponse<AuthResponse>> => {
    const response = await apiClient.post<AuthResponse>('/auth/login', {
      email: data.email,
      password: data.password,
    });

    // Store token in localStorage
    if (response.success && response.data?.token) {
      if (typeof window !== 'undefined') {
        localStorage.setItem('auth_token', response.data.token);
        localStorage.setItem('user', JSON.stringify(response.data.user));
      }
    }

    return response;
  },

  logout: async (): Promise<void> => {
    try {
      await apiClient.post('/auth/logout', {});
    } catch (error) {
      console.error('Logout error:', error);
    } finally {
      // Clear local storage regardless of API call success
      if (typeof window !== 'undefined') {
        localStorage.removeItem('auth_token');
        localStorage.removeItem('user');
      }
    }
  },

  getStoredUser: () => {
    if (typeof window === 'undefined') return null;
    const userStr = localStorage.getItem('user');
    return userStr ? JSON.parse(userStr) : null;
  },

  getStoredToken: () => {
    if (typeof window === 'undefined') return null;
    return localStorage.getItem('auth_token');
  },
};

