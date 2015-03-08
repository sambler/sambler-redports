--- ./cmake/FindGLFW.cmake.orig	2015-03-08 22:51:34.522337786 +1030
+++ ./cmake/FindGLFW.cmake	2015-03-08 22:51:57.095335165 +1030
@@ -120,11 +120,15 @@
             message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
         endif()
 
+        if(NOT X11_Xi_FOUND)
+            message(FATAL_ERROR "Xi library not found - required for GLFW")
+        endif()
+
         if(NOT X11_Xcursor_FOUND)
             message(FATAL_ERROR "Xcursor library not found - required for GLFW")
         endif()
 
-        list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}" -lrt)
+        list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}" "${X11_Xi_LIB}" -lrt)
 
         find_library( GLFW_glfw_LIBRARY
             NAMES 
