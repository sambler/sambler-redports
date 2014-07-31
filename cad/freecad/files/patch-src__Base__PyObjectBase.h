--- ./src/Base/PyObjectBase.h.orig	2014-07-14 01:03:02.000000000 +0930
+++ ./src/Base/PyObjectBase.h	2014-07-29 14:42:03.169399417 +0930
@@ -36,7 +36,7 @@
 // needed header
 #undef slots
 #include <Python.h>
-#ifdef FC_OS_MACOSX
+#if defined(FC_OS_MACOSX) || defined(__FreeBSD__)
 #undef toupper
 #undef tolower
 #undef isupper
