--- src/apps/ocioconvert/main.cpp.orig	2012-12-16 13:56:02.534422201 +1030
+++ src/apps/ocioconvert/main.cpp	2012-12-16 13:56:53.326147240 +1030
@@ -37,6 +37,7 @@
 #include <OpenImageIO/typedesc.h>
 #if (OIIO_VERSION < 10100)
 namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING
 #endif

 
