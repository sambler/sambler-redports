--- textmodel/properties.py.orig	2015-11-05 20:29:16 UTC
+++ textmodel/properties.py
@@ -23,7 +23,7 @@ class Properties(object):
                 try:
                     obj = getattr(self.__class__, name)
                 except :
-                    raise AttributeError, name
+                    raise AttributeError(name)
                 obj.fset(self, value)
 
 
