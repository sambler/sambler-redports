--- ./src/cmake/platform.cmake.orig	2014-05-16 20:24:57.075230591 +0930
+++ ./src/cmake/platform.cmake	2014-05-16 20:25:04.258229867 +0930
@@ -23,6 +23,7 @@
     elseif (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
         set (platform "FreeBSD")
         set (CXXFLAGS "${CXXFLAGS} -DFREEBSD")
+        add_definitions ("-D__STDC_LIMIT_MACROS=1")
         if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386")
             # to use gcc atomics we need cpu instructions only available
             # with arch of i586 or higher
