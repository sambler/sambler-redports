--- ./extern/glew/src/glew.c.orig	2009-09-02 00:52:11.000000000 +0930
+++ ./extern/glew/src/glew.c	2012-12-14 20:19:39.025422177 +1030
@@ -29,6 +29,7 @@
 ** THE POSSIBILITY OF SUCH DAMAGE.
 */
 
+#define GLEW_MX 1
 #include <GL/glew.h>
 #if defined(_WIN32)
 #  include <GL/wglew.h>
@@ -36,6 +37,8 @@
 #  include <GL/glxew.h>
 #endif
 
+#include <GL/glext.h>
+
 /*
  * Define glewGetContext and related helper macros.
  */
