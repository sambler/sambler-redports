--- setup.py.orig	2016-05-15 14:19:49 UTC
+++ setup.py
@@ -25,10 +25,6 @@ and releases is available at http://nucu
 """
 
 from distutils.core import setup
-import sys
-
-if sys.version<"2.3":
-    raise ValueError, "requires python 2.3 or better"
 
 setup(name="nucular",
       version="0.5",
