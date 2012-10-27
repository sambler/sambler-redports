--- ./cmake/platform.cmake.orig	2012-08-31 06:58:32.000000000 +0930
+++ ./cmake/platform.cmake	2012-10-27 15:54:13.672945357 +1030
@@ -14,6 +14,9 @@
             set (platform "linux64")
             set (CXXFLAGS "${CXXFLAGS} -DLINUX64")
         endif ()
+    elseif (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
+        set (platform "FreeBSD")
+        set (CXXFLAGS "${CXXFLAGS} -DFREEBSD")
     endif ()
     if (APPLE)
         message (STATUS "Apple!")
