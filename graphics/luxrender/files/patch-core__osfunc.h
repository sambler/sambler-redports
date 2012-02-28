--- ./core/osfunc.h.orig	2012-02-28 04:28:28.000000000 +1030
+++ ./core/osfunc.h	2012-02-28 16:50:09.000000000 +1030
@@ -31,7 +31,7 @@
 
 #include <boost/interprocess/detail/atomic.hpp>
 
-#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 #include <stddef.h>
 #include <sys/time.h>
 #elif defined (WIN32)
@@ -64,7 +64,7 @@
 		std::basic_istream<char> &is);
 
 inline double osWallClockTime() {
-#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__APPLE__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 	struct timeval t;
 	gettimeofday(&t, NULL);
 
