--- ./source/blender/imbuf/intern/jp2.c.orig	2013-10-22 22:32:34.268016672 +1030
+++ ./source/blender/imbuf/intern/jp2.c	2013-10-22 22:34:51.360016596 +1030
@@ -328,7 +328,7 @@
 }
 
 void cinema_parameters(opj_cparameters_t *parameters){
-	parameters->tile_size_on = false;
+	parameters->tile_size_on = 0; /* FALSE */
 	parameters->cp_tdx=1;
 	parameters->cp_tdy=1;
 	
