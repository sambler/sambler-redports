--- ./src/include/OpenImageIO/image_view.h.orig	2014-05-15 18:17:52.345230551 +0930
+++ ./src/include/OpenImageIO/image_view.h	2014-05-15 18:17:59.433230052 +0930
@@ -39,6 +39,7 @@
 #include "oiioversion.h"
 #include "strided_ptr.h"
 
+#define	PTRDIFF_MIN	(-0x7fffffffffffffffL-1)
 
 OIIO_NAMESPACE_ENTER {
 
