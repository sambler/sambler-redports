--- ./build_files/cmake/Modules/FindOpenImageIO.cmake.orig	2015-01-17 18:28:24.262351007 +1030
+++ ./build_files/cmake/Modules/FindOpenImageIO.cmake	2015-01-17 18:28:46.060346994 +1030
@@ -38,7 +38,7 @@
 
 FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
   NAMES
-    OpenImageIO/imageio.h
+    OpenImageIO16/imageio.h
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
@@ -47,7 +47,7 @@
 
 FIND_LIBRARY(OPENIMAGEIO_LIBRARY
   NAMES
-    OpenImageIO
+    OpenImageIO16
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
