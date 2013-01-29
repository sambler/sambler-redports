--- cmake/platform.cmake.orig	2013-01-10 11:43:37.000000000 +1030
+++ cmake/platform.cmake	2013-01-24 09:22:45.327857472 +1030
@@ -7,6 +7,15 @@
     message (STATUS "CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}")
 endif ()
 
+
+if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386")
+    if (NOT USE_TBB)
+        # to use gcc atomics we need cpu instructions only available
+        # with arch of i586 or higher
+        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=i586")
+    endif()
+endif()
+
 if (UNIX)
     if (VERBOSE)
         message (STATUS "Unix! ${CMAKE_SYSTEM_NAME}")
