--- ./src/apps/ociodisplay/main.cpp.orig	2012-11-18 13:44:55.706022772 +1030
+++ ./src/apps/ociodisplay/main.cpp	2012-11-18 13:50:56.826023344 +1030
@@ -53,7 +53,7 @@
 
 #include <OpenImageIO/imageio.h>
 #include <OpenImageIO/typedesc.h>
-namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING;
 
 GLint g_win = 0;
 int g_winWidth = 0;
