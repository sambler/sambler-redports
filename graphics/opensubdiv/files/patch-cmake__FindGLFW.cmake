--- ./cmake/FindGLFW.cmake.orig	2014-04-22 04:58:17.000000000 +0930
+++ ./cmake/FindGLFW.cmake	2014-05-20 02:57:05.500230396 +0930
@@ -119,8 +119,12 @@
         if(NOT X11_xf86vmode_FOUND)
             message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
         endif()
+        
+        if(NOT X11_Xi_FOUND)
+            message(FATAL_ERROR "Xi library not found - required for GLFW")
+        endif()
 
-        list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}")
+        list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xi_LIB}")
 
         find_library( GLFW_glfw_LIBRARY
             NAMES 
