--- build_files/cmake/Modules/FindOpenImageIO.cmake.orig	2018-03-18 20:50:59 UTC
+++ build_files/cmake/Modules/FindOpenImageIO.cmake
@@ -40,7 +40,7 @@ SET(_openimageio_SEARCH_DIRS
 
 FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
   NAMES
-    OpenImageIO/imageio.h
+    OpenImageIO17/imageio.h
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
@@ -49,7 +49,7 @@ FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
 
 FIND_LIBRARY(OPENIMAGEIO_LIBRARY
   NAMES
-    OpenImageIO
+    OpenImageIO17
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
