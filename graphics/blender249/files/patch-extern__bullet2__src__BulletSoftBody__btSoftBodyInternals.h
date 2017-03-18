--- ./extern/bullet2/src/BulletSoftBody/btSoftBodyInternals.h.orig	2009-09-02 00:53:19 UTC
+++ ./extern/bullet2/src/BulletSoftBody/btSoftBodyInternals.h
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
