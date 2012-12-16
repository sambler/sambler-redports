--- src/apps/ociolutimage/main.cpp.orig	2012-12-16 13:56:46.992630942 +1030
+++ src/apps/ociolutimage/main.cpp	2012-12-16 13:56:59.136423686 +1030
@@ -34,6 +34,7 @@
 #include <OpenImageIO/typedesc.h>
 #if (OIIO_VERSION < 10100)
 namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING
 #endif
 
 #include "argparse.h"
