--- libavdevice/bktr.c.orig	2014-09-09 17:31:01 UTC
+++ libavdevice/bktr.c
@@ -24,6 +24,11 @@
  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
  */
 
+typedef unsigned char u_char;
+typedef unsigned short        u_short;
+typedef unsigned int  u_int;
+typedef unsigned long u_long;
+
 #include "libavformat/internal.h"
 #include "libavutil/log.h"
 #include "libavutil/opt.h"
