--- libavfilter/vf_libopencv.c.orig	2014-09-09 17:30:59 UTC
+++ libavfilter/vf_libopencv.c
@@ -25,8 +25,7 @@
 
 /* #define DEBUG */
 
-#include <opencv/cv.h>
-#include <opencv/cxcore.h>
+#include <opencv2/imgproc/imgproc_c.h>
 #include "libavutil/avstring.h"
 #include "libavutil/common.h"
 #include "libavutil/file.h"
