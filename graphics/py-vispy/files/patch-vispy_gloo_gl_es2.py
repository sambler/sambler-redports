--- vispy/gloo/gl/es2.py.orig	2015-11-01 07:03:21 UTC
+++ vispy/gloo/gl/es2.py
@@ -49,6 +49,21 @@ elif sys.platform.startswith('linux'):
     # Load it
     _lib = ctypes.CDLL(es2_file)
     
+elif sys.platform.startswith('freebsd'):
+    es2_file = None
+    # Load from env
+    if 'ES2_LIBRARY' in os.environ:  # todo: is this the correct name?
+        if os.path.exists(os.environ['ES2_LIBRARY']):
+            es2_file = os.path.realpath(os.environ['ES2_LIBRARY'])
+    # Else, try to find it
+    if es2_file is None:
+        es2_file = ctypes.util.find_library('GLESv2')
+    # Else, we failed and exit
+    if es2_file is None:
+        raise OSError('GL ES 2.0 library not found')
+    # Load it
+    _lib = ctypes.CDLL(es2_file)
+
 elif sys.platform.startswith('darwin'):
     raise RuntimeError('ES 2.0 is not available on OSX yet')
 
