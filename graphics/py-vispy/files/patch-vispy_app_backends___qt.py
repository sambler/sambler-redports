--- vispy/app/backends/_qt.py.orig	2015-11-01 07:03:21 UTC
+++ vispy/app/backends/_qt.py
@@ -44,6 +44,11 @@ if sys.platform.startswith('linux'):
         IS_RPI = True
     else:
         IS_LINUX = True
+elif sys.platform.startswith('freebsd'):
+    if os.uname()[4].startswith('arm'):
+        IS_RPI = True
+    else:
+        IS_LINUX = True
 elif sys.platform.startswith('darwin'):
     IS_OSX = True
 elif sys.platform.startswith('win'):
