--- ./testshade/testshade_dso.cpp.orig	2012-08-31 06:58:32.000000000 +0930
+++ ./testshade/testshade_dso.cpp	2012-10-27 15:54:13.743668832 +1030
@@ -32,7 +32,7 @@
 #include <dlfcn.h>
 
 #include <OpenImageIO/plugin.h>
-using namespace OIIO;
+using namespace OIIO_NAMESPACE;
 
 
 typedef int (*EntryPoint)(int argc, const char *argv[]);
