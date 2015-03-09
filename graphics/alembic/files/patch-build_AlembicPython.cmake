--- build/AlembicPython.cmake.orig	2014-03-28 01:06:30 UTC
+++ build/AlembicPython.cmake
@@ -39,7 +39,7 @@ ELSE ()
     IF (APPLE)
         SET(PYTHON_EXECUTABLE_NAMES python2.7 python27 python2 python)
     ELSE ()
-        SET(PYTHON_EXECUTABLE_NAMES python2.6 python26 python2 python)
+        SET(PYTHON_EXECUTABLE_NAMES python2.7 python27 python2 python)
     ENDIF ()
 ENDIF ()
 
