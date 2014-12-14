--- source/blender/blenfont/intern/blf_glyph.c.orig	2014-10-21 22:38:11.000000000 +1030
+++ source/blender/blenfont/intern/blf_glyph.c	2014-12-14 15:47:30.636191334 +1030
@@ -262,8 +262,8 @@
 	g->xoff = -1;
 	g->yoff = -1;
 	bitmap = slot->bitmap;
-	g->width = bitmap.width;
-	g->height = bitmap.rows;
+	g->width = (int)bitmap.width;
+	g->height = (int)bitmap.rows;
 
 	if (g->width && g->height) {
 		if (sharp) {
