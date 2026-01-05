'use client';

import { useEffect } from 'react';
import { useRouter } from 'next/navigation';

export default function SuccessPage() {
  const router = useRouter();

  useEffect(() => {
    // Redirect to home after 3 seconds
    const timer = setTimeout(() => {
      router.push('/');
    }, 3000);

    return () => clearTimeout(timer);
  }, [router]);

  return (
    <div className="flex min-h-screen items-center justify-center bg-gradient-to-br from-zinc-50 via-white to-zinc-100 px-4 py-12 dark:from-zinc-950 dark:via-black dark:to-zinc-900">
      <div className="w-full max-w-md text-center">
        <div className="rounded-2xl bg-white/80 p-12 shadow-xl backdrop-blur-sm dark:bg-zinc-900/80">
          {/* Success Icon */}
          <div className="mx-auto mb-6 flex h-20 w-20 items-center justify-center rounded-full bg-green-100 dark:bg-green-900/20">
            <svg
              className="h-12 w-12 text-green-600 dark:text-green-400"
              fill="none"
              stroke="currentColor"
              viewBox="0 0 24 24"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M5 13l4 4L19 7"
              />
            </svg>
          </div>

          {/* Success Message */}
          <h1 className="mb-4 text-3xl font-semibold text-zinc-900 dark:text-zinc-50">
            Success!
          </h1>
          <p className="mb-8 text-zinc-600 dark:text-zinc-400">
            You have successfully signed in. Redirecting to home page...
          </p>

          {/* Loading Animation */}
          <div className="flex justify-center">
            <div className="h-2 w-48 overflow-hidden rounded-full bg-zinc-200 dark:bg-zinc-700">
              <div className="h-full w-full animate-progress rounded-full bg-green-600 dark:bg-green-400"></div>
            </div>
          </div>

          {/* Manual Link */}
          <div className="mt-8">
            <button
              onClick={() => router.push('/')}
              className="text-sm font-medium text-zinc-900 underline hover:text-zinc-700 dark:text-zinc-50 dark:hover:text-zinc-300"
            >
              Go to home page now
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}



