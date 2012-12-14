--- ./intern/elbeem/intern/ntl_vector3dim.h.orig	2009-09-02 00:50:31.000000000 +0930
+++ ./intern/elbeem/intern/ntl_vector3dim.h	2012-12-14 20:19:39.028422257 +1030
@@ -110,6 +110,7 @@
 #endif // !NOGUI
 #endif // ELBEEM_PLUGIN==1
 
+#define ABS(x)	((x) < 0 ? -(x) : (x))
 
 // basic inlined vector class
 template<class Scalar>
