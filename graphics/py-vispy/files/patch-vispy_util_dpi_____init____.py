--- vispy/util/dpi/__init__.py.orig	2015-11-01 07:03:21 UTC
+++ vispy/util/dpi/__init__.py
@@ -13,6 +13,8 @@ __all__ = ['get_dpi']
 
 if sys.platform.startswith('linux'):
     from ._linux import get_dpi
+elif sys.platform.startswith('freebsd'):
+    from ._linux import get_dpi
 elif sys.platform == 'darwin':
     from ._quartz import get_dpi
 elif sys.platform.startswith('win'):
