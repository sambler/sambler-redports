--- release/bin/blender-thumbnailer.py.orig	2015-07-07 08:47:48 UTC
+++ release/bin/blender-thumbnailer.py
@@ -24,7 +24,7 @@
 Thumbnailer runs with python 2.6 and 3.x.
 To run automatically with nautilus:
    gconftool --type boolean --set /desktop/gnome/thumbnailers/application@x-blender/enable true
-   gconftool --type string --set /desktop/gnome/thumbnailers/application@x-blender/command "blender-thumbnailer.py %u %o"
+   gconftool --type string --set /desktop/gnome/thumbnailers/application@x-blender/command "blender-thumbnailer-269.py %u %o"
 """
 
 import struct
