--- ./source/blender/imbuf/intern/cineon/dpxlib.c.orig	2013-10-29 22:43:48.000000000 +1030
+++ ./source/blender/imbuf/intern/cineon/dpxlib.c	2013-10-29 22:44:45.000000000 +1030
@@ -300,10 +300,10 @@
 			case descriptor_RGB:
 			case descriptor_RGBA:
 			case descriptor_ABGR:
-				if (dpx->element[i].refLowData == DPX_UNDEFINED_U32 || isnan(dpx->element[i].refLowData))
+				if (dpx->element[i].refLowData == DPX_UNDEFINED_U32)
 					dpx->element[i].refLowData = 0;
 
-				if (dpx->element[i].refHighData == DPX_UNDEFINED_U32 || isnan(dpx->element[i].refHighData))
+				if (dpx->element[i].refHighData == DPX_UNDEFINED_U32)
 					dpx->element[i].refHighData = (unsigned int)dpx->element[i].maxValue;
 
 				if (dpx->element[i].refLowQuantity == DPX_UNDEFINED_R32 || isnan(dpx->element[i].refLowQuantity))
@@ -324,10 +324,10 @@
 			case descriptor_CbYCr:
 			case descriptor_CbYACrYA:
 			case descriptor_CbYCrA:
-				if (dpx->element[i].refLowData == DPX_UNDEFINED_U32 || isnan(dpx->element[i].refLowData))
+				if (dpx->element[i].refLowData == DPX_UNDEFINED_U32)
 					dpx->element[i].refLowData = 16.0f / 255.0f * dpx->element[i].maxValue;
 
-				if (dpx->element[i].refHighData == DPX_UNDEFINED_U32 || isnan(dpx->element[i].refHighData))
+				if (dpx->element[i].refHighData == DPX_UNDEFINED_U32)
 					dpx->element[i].refHighData = 235.0f / 255.0f * dpx->element[i].maxValue;
 
 				if (dpx->element[i].refLowQuantity == DPX_UNDEFINED_R32 || isnan(dpx->element[i].refLowQuantity))
