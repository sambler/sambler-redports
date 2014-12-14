--- source/blender/blenfont/intern/blf_glyph.c.orig	2014-04-12 00:16:41.000000000 +0930
+++ source/blender/blenfont/intern/blf_glyph.c	2014-12-14 15:46:10.217196976 +1030
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
