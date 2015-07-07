--- build_files/cmake/Modules/FindOpenImageIO.cmake.orig	2012-11-12 19:39:09 UTC
+++ build_files/cmake/Modules/FindOpenImageIO.cmake
@@ -38,7 +38,7 @@ SET(_openimageio_SEARCH_DIRS
 
 FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
   NAMES
-    OpenImageIO/imageio.h
+    OpenImageIO14/imageio.h
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
@@ -47,7 +47,7 @@ FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
 
 FIND_LIBRARY(OPENIMAGEIO_LIBRARY
   NAMES
-    OpenImageIO
+    OpenImageIO14
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
