--- build_files/cmake/Modules/FindPythonLibsUnix.cmake.orig	2020-04-25 16:16:15 UTC
+++ build_files/cmake/Modules/FindPythonLibsUnix.cmake
@@ -38,7 +38,7 @@ IF(NOT PYTHON_ROOT_DIR AND NOT $ENV{PYTHON_ROOT_DIR} S
   SET(PYTHON_ROOT_DIR $ENV{PYTHON_ROOT_DIR})
 ENDIF()
 
-SET(PYTHON_VERSION 3.5 CACHE STRING "Python Version (major and minor only)")
+SET(PYTHON_VERSION 3.6 CACHE STRING "Python Version (major and minor only)")
 MARK_AS_ADVANCED(PYTHON_VERSION)
 
 
