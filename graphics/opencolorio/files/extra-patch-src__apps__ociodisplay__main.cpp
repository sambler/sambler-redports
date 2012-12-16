--- src/apps/ociodisplay/main.cpp.orig	2012-12-16 13:56:24.758422542 +1030
+++ src/apps/ociodisplay/main.cpp	2012-12-16 13:56:56.003376824 +1030
@@ -54,6 +54,7 @@
 #include <OpenImageIO/typedesc.h>
 #if (OIIO_VERSION < 10100)
 namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING
 #endif
 
 GLint g_win = 0;
