--- ./source/blender/imbuf/intern/cineon/cineonlib.c.orig	2013-10-29 22:42:09.000000000 +1030
+++ ./source/blender/imbuf/intern/cineon/cineonlib.c	2013-10-29 22:42:46.000000000 +1030
@@ -277,10 +277,10 @@
 				return NULL;
 		}
 
-		if (cineon->element[i].refLowData == CINEON_UNDEFINED_U32 || isnan(cineon->element[i].refLowData))
+		if (cineon->element[i].refLowData == CINEON_UNDEFINED_U32)
 			cineon->element[i].refLowData = 0;
 
-		if (cineon->element[i].refHighData == CINEON_UNDEFINED_U32 || isnan(cineon->element[i].refHighData))
+		if (cineon->element[i].refHighData == CINEON_UNDEFINED_U32)
 			cineon->element[i].refHighData = (unsigned int)cineon->element[i].maxValue;
 
 		if (cineon->element[i].refLowQuantity == CINEON_UNDEFINED_R32 || isnan(cineon->element[i].refLowQuantity))
