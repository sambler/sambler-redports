--- textmodel/listtools.py.orig	2015-11-05 20:29:16 UTC
+++ textmodel/listtools.py
@@ -46,7 +46,7 @@ def iter_items(l):
 
 def intersecting_items(l, i1, i2):
     if not i2>i1:
-        raise ValueError, "i2 must be larger i1"
+        raise ValueError("i2 must be larger i1")
     r = []
     j1 = 0
     for item in l:
