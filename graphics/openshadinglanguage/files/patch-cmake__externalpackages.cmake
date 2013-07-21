--- ./cmake/externalpackages.cmake.orig	2013-07-20 16:51:14.744109404 +0930
+++ ./cmake/externalpackages.cmake	2013-07-20 16:51:27.862109296 +0930
@@ -158,12 +158,12 @@
 if(LLVM_DIRECTORY)
   FIND_PROGRAM(LLVM_CONFIG llvm-config-${LLVM_VERSION} HINTS ${LLVM_DIRECTORY}/bin NO_CMAKE_PATH)
   if(NOT LLVM_CONFIG)
-    FIND_PROGRAM(LLVM_CONFIG llvm-config HINTS ${LLVM_DIRECTORY}/bin NO_CMAKE_PATH)
+    FIND_PROGRAM(LLVM_CONFIG llvm-config33 HINTS ${LLVM_DIRECTORY}/bin NO_CMAKE_PATH)
   endif()
 else()
   FIND_PROGRAM(LLVM_CONFIG llvm-config-${LLVM_VERSION})
   if(NOT LLVM_CONFIG)
-    FIND_PROGRAM(LLVM_CONFIG llvm-config)
+    FIND_PROGRAM(LLVM_CONFIG llvm-config33)
   endif()
 endif()
 
