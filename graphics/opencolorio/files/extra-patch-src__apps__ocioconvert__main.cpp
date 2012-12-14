--- ./src/apps/ocioconvert/main.cpp.orig	2012-11-18 13:45:02.056021661 +1030
+++ ./src/apps/ocioconvert/main.cpp	2012-11-18 13:50:51.982022168 +1030
@@ -35,7 +35,7 @@
 
 #include <OpenImageIO/imageio.h>
 #include <OpenImageIO/typedesc.h>
-namespace OIIO = OIIO_NAMESPACE;
+OIIO_NAMESPACE_USING;

 
 #include "argparse.h"
