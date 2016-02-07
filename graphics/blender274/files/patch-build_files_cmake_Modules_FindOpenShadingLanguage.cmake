--- build_files/cmake/Modules/FindOpenShadingLanguage.cmake.orig	2016-02-08 03:09:16 UTC
+++ build_files/cmake/Modules/FindOpenShadingLanguage.cmake
@@ -28,9 +28,9 @@ IF(NOT OSL_ROOT_DIR AND NOT $ENV{OSL_ROO
 ENDIF()
 
 SET(_osl_FIND_COMPONENTS
-  oslcomp
-  oslexec
-  oslquery
+  oslcomp16
+  oslexec16
+  oslquery16
 )
 
 SET(_osl_SEARCH_DIRS
@@ -66,7 +66,7 @@ FOREACH(COMPONENT ${_osl_FIND_COMPONENTS
   LIST(APPEND _osl_LIBRARIES "${OSL_${UPPERCOMPONENT}_LIBRARY}")
 ENDFOREACH()
 
-FIND_PROGRAM(OSL_COMPILER oslc
+FIND_PROGRAM(OSL_COMPILER oslc16
              HINTS ${_osl_SEARCH_DIRS}
              PATH_SUFFIXES bin)
 
@@ -79,9 +79,9 @@ IF(OSL_FOUND)
   SET(OSL_LIBRARIES ${_osl_LIBRARIES})
   SET(OSL_INCLUDE_DIRS ${OSL_INCLUDE_DIR})
 
-  FILE(STRINGS "${OSL_INCLUDE_DIR}/OSL/oslversion.h" OSL_LIBRARY_VERSION_MAJOR
+  FILE(STRINGS "${OSL_INCLUDE_DIR}/OSL16/oslversion.h" OSL_LIBRARY_VERSION_MAJOR
        REGEX "^[ \t]*#define[ \t]+OSL_LIBRARY_VERSION_MAJOR[ \t]+[0-9]+.*$")
-  FILE(STRINGS "${OSL_INCLUDE_DIR}/OSL/oslversion.h" OSL_LIBRARY_VERSION_MINOR
+  FILE(STRINGS "${OSL_INCLUDE_DIR}/OSL16/oslversion.h" OSL_LIBRARY_VERSION_MINOR
        REGEX "^[ \t]*#define[ \t]+OSL_LIBRARY_VERSION_MINOR[ \t]+[0-9]+.*$")
   STRING(REGEX REPLACE ".*#define[ \t]+OSL_LIBRARY_VERSION_MAJOR[ \t]+([.0-9]+).*"
          "\\1" OSL_LIBRARY_VERSION_MAJOR ${OSL_LIBRARY_VERSION_MAJOR})
