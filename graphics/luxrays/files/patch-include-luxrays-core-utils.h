--- include/luxrays/core/utils.h.orig
+++ include/luxrays/core/utils.h
@@ -41,7 +41,7 @@
 using std::isnan;
 #endif
 
-#if defined(__APPLE__) // OSX adaptions Jens Verwiebe
+#if defined(__APPLE__) || defined(__FreeBSD__) // OSX adaptions Jens Verwiebe
 #  define memalign(a,b) valloc(b)
 #include <string>
 typedef unsigned int u_int;
@@ -51,7 +51,7 @@
 using std::isinf;
 #endif
 
-#if defined(__APPLE__)
+#if defined(__APPLE__) || defined(__FreeBSD__)
 #include <stdlib.h>
 #else
 #include <malloc.h>
@@ -59,7 +59,7 @@
 
 #include <sstream>
 
-#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 #include <stddef.h>
 #include <sys/time.h>
 #elif defined (WIN32)
@@ -87,7 +87,7 @@
 namespace luxrays {
 
 inline double WallClockTime() {
-#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 	struct timeval t;
 	gettimeofday(&t, NULL);
 
@@ -226,7 +226,7 @@
 }
 
 inline bool SetThreadRRPriority(boost::thread *thread, int pri = 0) {
-#if defined (__linux__) || defined (__APPLE__) || defined(__CYGWIN__)
+#if defined (__linux__) || defined (__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 	{
 		const pthread_t tid = (pthread_t)thread->native_handle();
 
