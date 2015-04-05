--- ./build_files/cmake/Modules/FindOpenShadingLanguage.cmake.orig	2015-04-05 18:07:12.194518120 +0930
+++ ./build_files/cmake/Modules/FindOpenShadingLanguage.cmake	2015-04-05 18:21:16.062459504 +0930
@@ -28,9 +28,9 @@
 ENDIF()
 
 SET(_osl_FIND_COMPONENTS
-  oslcomp
-  oslexec
-  oslquery
+  oslcomp15
+  oslexec15
+  oslquery15
 )
 
 SET(_osl_SEARCH_DIRS
@@ -44,7 +44,7 @@
 
 FIND_PATH(OSL_INCLUDE_DIR
   NAMES
-    OSL/oslversion.h
+    OSL15/oslversion.h
   HINTS
     ${_osl_SEARCH_DIRS}
   PATH_SUFFIXES
@@ -66,7 +66,7 @@
   LIST(APPEND _osl_LIBRARIES "${OSL_${UPPERCOMPONENT}_LIBRARY}")
 ENDFOREACH()
 
-FIND_PROGRAM(OSL_COMPILER oslc
+FIND_PROGRAM(OSL_COMPILER oslc15
              HINTS ${_osl_SEARCH_DIRS}
              PATH_SUFFIXES bin)
 
