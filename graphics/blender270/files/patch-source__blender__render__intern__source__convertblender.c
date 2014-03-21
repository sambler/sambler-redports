--- ./source/blender/render/intern/source/convertblender.c.orig	2014-03-21 19:29:00.232421668 +1030
+++ ./source/blender/render/intern/source/convertblender.c	2014-03-21 19:32:40.913419969 +1030
@@ -5873,7 +5873,9 @@
 	re->lay= lay;
 
 	/* renderdata setup and exceptions */
-	re->r= scene->r;
+	BLI_freelistN(&re->r.layers);
+	re->r = scene->r;
+	BLI_duplicatelist(&re->r.layers, &scene->r.layers);
 	
 	RE_init_threadcount(re);
 	
