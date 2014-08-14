--- ./extern/bullet2/src/BulletSoftBody/btSoftBodyInternals.h.orig	2009-09-02 00:53:19.000000000 +0930
+++ ./extern/bullet2/src/BulletSoftBody/btSoftBodyInternals.h	2012-12-14 20:27:09.849423421 +1030
@@ -171,8 +171,7 @@
 template <typename T>
 static inline void			ZeroInitialize(T& value)
 {
-	static const T	zerodummy;
-	value=zerodummy;
+	memset(&value,0,sizeof(T));
 }
 //
 template <typename T>
