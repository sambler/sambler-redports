--- cmake/PlatformSpecific.cmake.orig
+++ cmake/PlatformSpecific.cmake
@@ -79,8 +79,8 @@
   # Update if necessary
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
 
-  SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -msse -msse2 -msse3 -mssse3 -fPIC -O0 -g")
-  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -fPIC -O3 -ftree-vectorize -msse -msse2 -msse3 -mssse3 -fvariable-expansion-in-unroller")
+#  SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -msse -msse2 -msse3 -mssse3 -fPIC -O0 -g")
+#  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -fPIC -O3 -ftree-vectorize -msse -msse2 -msse3 -mssse3 -fvariable-expansion-in-unroller")
   
 ENDIF()
 

