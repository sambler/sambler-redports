--- build_files/cmake/Modules/FindOpenImageIO.cmake.orig	2015-01-16 21:30:37 UTC
+++ build_files/cmake/Modules/FindOpenImageIO.cmake
@@ -39,7 +39,7 @@ SET(_openimageio_SEARCH_DIRS
 
 FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
   NAMES
-    OpenImageIO/imageio.h
+    OpenImageIO14/imageio.h
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
@@ -48,7 +48,7 @@ FIND_PATH(OPENIMAGEIO_INCLUDE_DIR
 
 FIND_LIBRARY(OPENIMAGEIO_LIBRARY
   NAMES
-    OpenImageIO
+    OpenImageIO14
   HINTS
     ${_openimageio_SEARCH_DIRS}
   PATH_SUFFIXES
