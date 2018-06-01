--- src/cmake/modules/FindOpenCV.cmake.orig	2018-06-01 03:37:20 UTC
+++ src/cmake/modules/FindOpenCV.cmake
@@ -51,7 +51,7 @@ set (libdirs "${PROJECT_SOURCE_DIR}/lib"
              )
 
 
-set (opencv_components opencv_imgproc opencv_core)
+set (opencv_components opencv_imgproc opencv_core opencv_highgui)
 if (NOT ${OpenCV_VERSION} VERSION_LESS 3.0.0)
     set (opencv_components opencv_videoio ${opencv_components})
 else (NOT ${OpenCV_VERSION} VERSION_LESS 3.0.0)
