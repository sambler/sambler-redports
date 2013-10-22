--- ./intern/elbeem/intern/utilities.h.orig	2009-09-02 00:50:31.000000000 +0930
+++ ./intern/elbeem/intern/utilities.h	2012-12-14 20:19:39.029422133 +1030
@@ -172,6 +172,9 @@
 { return (a < b) ? b : a ; }
 
 /* absolute value */
+#ifdef ABS
+#undef ABS
+#endif
 template < class T >
 inline T
 ABS( T a )
