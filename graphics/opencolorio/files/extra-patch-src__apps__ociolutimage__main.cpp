--- ./src/apps/ociolutimage/main.cpp.orig	2012-11-18 13:44:58.667023688 +1030
+++ ./src/apps/ociolutimage/main.cpp	2012-11-18 13:50:46.294026895 +1030
@@ -32,7 +32,7 @@
 
 #include <OpenImageIO/imageio.h>
 #include <OpenImageIO/typedesc.h>
-namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING;
 
 #include "argparse.h"
 
