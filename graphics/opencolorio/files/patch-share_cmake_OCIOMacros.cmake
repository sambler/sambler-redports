--- share/cmake/OCIOMacros.cmake.orig	2012-09-23 08:22:50.284500079 +0930
+++ share/cmake/OCIOMacros.cmake	2012-09-23 08:23:01.717501340 +0930
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
