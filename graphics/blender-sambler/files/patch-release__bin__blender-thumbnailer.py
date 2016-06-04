--- release/bin/blender-thumbnailer.py.orig	2014-03-03 20:46:09 UTC
+++ release/bin/blender-thumbnailer.py
@@ -28,8 +28,8 @@
 with the following contents:
 
 [Thumbnailer Entry]
-TryExec=blender-thumbnailer.py
-Exec=blender-thumbnailer.py %u %o
+TryExec=blender-thumbnailer-%%VERS_TAG%%.py
+Exec=blender-thumbnailer-%%VERS_TAG%%.py %u %o
 MimeType=application/x-blender;
 """
 
