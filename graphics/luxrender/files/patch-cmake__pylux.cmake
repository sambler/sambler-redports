--- ./cmake/pylux.cmake.orig	2012-02-28 16:48:53.000000000 +1030
+++ ./cmake/pylux.cmake	2012-02-28 16:49:49.000000000 +1030
@@ -110,3 +110,10 @@
 ELSE(PYTHONLIBS_FOUND OR PYTHON_CUSTOM)
 	MESSAGE( STATUS "Warning: could not find Python libraries - not building python module")
 ENDIF(PYTHONLIBS_FOUND OR PYTHON_CUSTOM)
+
+install(FILES ${CMAKE_BINARY_DIR}/pylux.so DESTINATION ${TARGETROOT}/lib)
+install(FILES ${CMAKE_BINARY_DIR}/pyluxconsole.py DESTINATION ${TARGETROOT}/lib)
+IF(EXISTS ${CMAKE_BINARY_DIR}/doc/html/)
+	install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html/ DESTINATION ${TARGETROOT}/share/luxrender/)
+ENDIF(EXISTS ${CMAKE_BINARY_DIR}/doc/html/)
+
