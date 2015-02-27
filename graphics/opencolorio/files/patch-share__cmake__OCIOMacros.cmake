--- ./share/cmake/OCIOMacros.cmake.orig	2012-04-18 09:38:16.000000000 +0930
+++ ./share/cmake/OCIOMacros.cmake	2012-10-08 00:20:27.666350767 +1030
@@ -64,7 +64,7 @@
     if(OIIO_LIBRARY_PATH)
         message(STATUS "OIIO LIBRARY_PATH explicitly specified: ${OIIO_LIBRARY_PATH}")
     endif()
-    FIND_PATH( OIIO_INCLUDES OpenImageIO/version.h
+    FIND_PATH( OIIO_INCLUDES OpenImageIO14/version.h
         ${OIIO_INCLUDE_PATH}
         ${OIIO_PATH}/include/
         /usr/include
@@ -73,7 +73,7 @@
         /opt/local/include
         DOC "The directory where OpenImageIO/version.h resides")
     FIND_LIBRARY(OIIO_LIBRARIES
-        NAMES OIIO OpenImageIO
+        NAMES OIIO OpenImageIO14
         PATHS
         ${OIIO_LIBRARY_PATH}
         ${OIIO_PATH}/lib/
@@ -294,7 +294,7 @@
 MACRO(ExtractRstCPP INFILE OUTFILE)
    add_custom_command(
       OUTPUT ${OUTFILE}
-      COMMAND ${CMAKE_SOURCE_DIR}/share/sphinx/ExtractRstFromSourceCPP.py ${INFILE} ${OUTFILE}
+      COMMAND python ${CMAKE_SOURCE_DIR}/share/sphinx/ExtractRstFromSourceCPP.py ${INFILE} ${OUTFILE}
       DEPENDS ${INFILE}
       COMMENT "Extracting reStructuredText from ${INFILE} (using old process)"
    )
@@ -303,7 +303,7 @@
 MACRO(ExtractRstSimple INFILE OUTFILE)
    add_custom_command(
       OUTPUT ${OUTFILE}
-      COMMAND ${CMAKE_SOURCE_DIR}/share/sphinx/ExtractRstFromSourceSimple.py ${INFILE} ${OUTFILE}
+      COMMAND python ${CMAKE_SOURCE_DIR}/share/sphinx/ExtractRstFromSourceSimple.py ${INFILE} ${OUTFILE}
       DEPENDS ${INFILE}
       COMMENT "Extracting reStructuredText from ${INFILE}"
    )
