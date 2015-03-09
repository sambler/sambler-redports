--- lib/Alembic/Util/Murmur3.cpp.orig	2012-09-20 21:15:45 UTC
+++ lib/Alembic/Util/Murmur3.cpp
@@ -41,6 +41,8 @@
 
 #ifdef __APPLE__
 #include <machine/endian.h>
+#elif defined(__FreeBSD__)
+#include <sys/endian.h>
 #elif !defined(_MSC_VER)
 #include <endian.h>
 #endif
