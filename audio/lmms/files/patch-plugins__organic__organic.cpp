--- ./plugins/organic/organic.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./plugins/organic/organic.cpp	2014-08-29 23:58:51.576454970 +0930
@@ -41,6 +41,9 @@
 
 #include "embed.cpp"
 
+#if __FreeBSD_version <= 704100 || (__FreeBSD_version >= 800000 && __FreeBSD_version < 802502) || (__FreeBSD_version >= 900000 && __FreeBSD_version < 900027)
+#define log2f(x) (logf(x) / logf(2))
+#endif
 
 
 
