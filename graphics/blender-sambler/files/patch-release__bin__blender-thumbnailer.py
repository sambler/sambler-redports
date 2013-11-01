--- ./release/bin/blender-thumbnailer.py.orig	2013-01-01 20:58:39.949174277 +1030
+++ ./release/bin/blender-thumbnailer.py	2013-01-01 20:59:02.127178116 +1030
@@ -24,7 +24,7 @@
 Thumbnailer runs with python 2.6 and 3.x.
 To run automatically with nautilus:
    gconftool --type boolean --set /desktop/gnome/thumbnailers/application@x-blender/enable true
-   gconftool --type string --set /desktop/gnome/thumbnailers/application@x-blender/command "blender-thumbnailer.py %u %o"
+   gconftool --type string --set /desktop/gnome/thumbnailers/application@x-blender/command "blender-thumbnailer-%%VERS_TAG%%.py %u %o"
 """
 
 import struct
