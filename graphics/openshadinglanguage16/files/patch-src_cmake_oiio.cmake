--- src/cmake/oiio.cmake.orig	2016-07-07 21:36:16 UTC
+++ src/cmake/oiio.cmake
@@ -13,12 +13,12 @@ endif ()
 MESSAGE ( STATUS "OPENIMAGEIOHOME = ${OPENIMAGEIOHOME}" )
 
 find_library ( OPENIMAGEIO_LIBRARY
-               NAMES OpenImageIO
+               NAMES OpenImageIO16
                HINTS ${OPENIMAGEIOHOME}
                PATH_SUFFIXES lib64 lib
                PATHS "${OPENIMAGEIOHOME}/lib" )
 find_path ( OPENIMAGEIO_INCLUDES
-            NAMES OpenImageIO/imageio.h
+            NAMES OpenImageIO16/imageio.h
             HINTS ${OPENIMAGEIOHOME}
             PATH_SUFFIXES include )
 IF (OPENIMAGEIO_INCLUDES AND OPENIMAGEIO_LIBRARY )
