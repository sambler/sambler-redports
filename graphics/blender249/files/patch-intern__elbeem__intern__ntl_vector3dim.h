--- ./intern/elbeem/intern/ntl_vector3dim.h.orig	2009-09-02 00:50:31 UTC
+++ ./intern/elbeem/intern/ntl_vector3dim.h
@@ -110,6 +110,7 @@
 #endif // !NOGUI
 #endif // ELBEEM_PLUGIN==1
 
+#define ABS(x)	((x) < 0 ? -(x) : (x))
 
 // basic inlined vector class
 template<class Scalar>
