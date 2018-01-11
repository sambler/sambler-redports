--- COLLADAStreamWriter/src/COLLADASWLibraryAnimations.cpp.orig	2018-01-11 14:19:20 UTC
+++ COLLADAStreamWriter/src/COLLADASWLibraryAnimations.cpp
@@ -62,7 +62,7 @@ namespace COLLADASW
 
     //---------------------------------------------------------------
     LibraryAnimations::LibraryAnimations ( COLLADASW::StreamWriter * streamWriter )
-            : Library ( streamWriter, CSWC::CSW_ELEMENT_LIBRARY_ANIMATIONS ), mOpenAnimations ( NULL )
+            : Library ( streamWriter, CSWC::CSW_ELEMENT_LIBRARY_ANIMATIONS ), mOpenAnimations ( 0 )
     {}
 
     //---------------------------------------------------------------
