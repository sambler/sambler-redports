--- ./intern/elbeem/intern/utilities.h.orig	2009-09-02 00:50:31 UTC
+++ ./intern/elbeem/intern/utilities.h
@@ -172,6 +172,9 @@
 { return (a < b) ? b : a ; }
 
 /* absolute value */
+#ifdef ABS
+#undef ABS
+#endif
 template < class T >
 inline T
 ABS( T a )
