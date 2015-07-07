--- source/blender/imbuf/intern/cineon/cineonlib.c.orig	2013-03-22 05:34:10 UTC
+++ source/blender/imbuf/intern/cineon/cineonlib.c
@@ -277,10 +277,10 @@ LogImageFile *cineonOpen(const unsigned 
 				return NULL;
 		}
 
-		if (cineon->element[i].refLowData == CINEON_UNDEFINED_U32 || isnan(cineon->element[i].refLowData))
+		if (cineon->element[i].refLowData == CINEON_UNDEFINED_U32)
 			cineon->element[i].refLowData = 0;
 
-		if (cineon->element[i].refHighData == CINEON_UNDEFINED_U32 || isnan(cineon->element[i].refHighData))
+		if (cineon->element[i].refHighData == CINEON_UNDEFINED_U32)
 			cineon->element[i].refHighData = (unsigned int)cineon->element[i].maxValue;
 
 		if (cineon->element[i].refLowQuantity == CINEON_UNDEFINED_R32 || isnan(cineon->element[i].refLowQuantity))
