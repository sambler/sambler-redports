--- cmake/PlatformSpecific.cmake.orig	2012-04-19 22:03:34.000000000 +0930
+++ cmake/PlatformSpecific.cmake	2012-04-20 15:34:52.000000000 +0930
@@ -105,7 +105,7 @@
 IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
   # Update if necessary
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
-  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -mssse3")
+#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -mssse3")
   IF(NOT CYGWIN)
 	  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
   ENDIF(NOT CYGWIN)
 
