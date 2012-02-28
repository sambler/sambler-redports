--- ./shapes/mikktspace/weldmesh.c.orig	2012-02-28 04:28:28.000000000 +1030
+++ ./shapes/mikktspace/weldmesh.c	2012-02-28 16:50:09.000000000 +1030
@@ -23,7 +23,7 @@
 #include <string.h>
 #include <assert.h>
 
-#ifdef __APPLE__
+#if defined(__APPLE__) || defined(__FreeBSD__)
 #include <stdlib.h>  /* OSX gets its malloc stuff through here */
 #else
 #include <malloc.h> 
@@ -191,4 +191,4 @@
 			MergeVertsFast(piCurNrUniqueVertices, piRemapTable, pfVertexDataOut, piVertexIDs,
 						   pfVertexDataIn, iNrVerticesIn, iFloatsPerVert, iL, iR_in, iChannelNum);	// weld all right of (or equal to) fSep
 	}
-}
\ No newline at end of file
+}
