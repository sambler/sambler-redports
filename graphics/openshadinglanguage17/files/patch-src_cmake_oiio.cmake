--- src/cmake/oiio.cmake.orig	2018-03-19 15:05:35 UTC
+++ src/cmake/oiio.cmake
@@ -15,12 +15,12 @@ if (NOT OpenImageIO_FIND_QUIETLY)
 endif ()
 
 find_library ( OPENIMAGEIO_LIBRARY
-               NAMES OpenImageIO
+               NAMES OpenImageIO17
                HINTS ${OPENIMAGEIOHOME}
                PATH_SUFFIXES lib64 lib
                PATHS "${OPENIMAGEIOHOME}/lib" )
 find_path ( OPENIMAGEIO_INCLUDES
-            NAMES OpenImageIO/imageio.h
+            NAMES OpenImageIO17/imageio.h
             HINTS ${OPENIMAGEIOHOME}
             PATH_SUFFIXES include )
 find_program ( OPENIMAGEIO_BIN
@@ -28,14 +28,14 @@ find_program ( OPENIMAGEIO_BIN
                HINTS ${OPENIMAGEIOHOME}
                PATH_SUFFIXES bin )
 if (NOT OpenImageIO_FIND_QUIETLY)
-    MESSAGE ( STATUS "OpenImageIO includes = ${OPENIMAGEIO_INCLUDES}" )
-    MESSAGE ( STATUS "OpenImageIO library = ${OPENIMAGEIO_LIBRARY}" )
-    MESSAGE ( STATUS "OpenImageIO bin = ${OPENIMAGEIO_BIN}" )
+    MESSAGE ( STATUS "OpenImageIO17 includes = ${OPENIMAGEIO_INCLUDES}" )
+    MESSAGE ( STATUS "OpenImageIO17 library = ${OPENIMAGEIO_LIBRARY}" )
+    MESSAGE ( STATUS "OpenImageIO17 bin = ${OPENIMAGEIO_BIN}" )
 endif ()
 IF ( OPENIMAGEIO_INCLUDES AND OPENIMAGEIO_LIBRARY )
     SET ( OPENIMAGEIO_FOUND TRUE )
 ELSE ()
-    MESSAGE ( FATAL_ERROR "OpenImageIO not found" )
+    MESSAGE ( FATAL_ERROR "OpenImageIO17 not found" )
 ENDIF ()
 
 # end OpenImageIO setup
