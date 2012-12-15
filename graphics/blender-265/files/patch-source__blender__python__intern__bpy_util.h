--- ./source/blender/python/intern/bpy_util.h.orig	2012-12-15 21:40:27.037422330 +1030
+++ ./source/blender/python/intern/bpy_util.h	2012-12-15 21:40:39.811423744 +1030
@@ -27,9 +27,9 @@
 #ifndef __BPY_UTIL_H__
 #define __BPY_UTIL_H__
 
-#if PY_VERSION_HEX <  0x03030000
-#  error "Python 3.3 or greater is required, you'll need to update your python."
-#endif
+//#if PY_VERSION_HEX <  0x03030000
+//#  error "Python 3.3 or greater is required, you'll need to update your python."
+//#endif
 
 struct EnumPropertyItem;
 struct ReportList;
