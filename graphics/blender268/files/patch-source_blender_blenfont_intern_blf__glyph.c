--- source/blender/blenfont/intern/blf_glyph.c.orig	2013-06-28 22:35:15.000000000 +0930
+++ source/blender/blenfont/intern/blf_glyph.c	2014-12-14 15:38:42.226227857 +1030
@@ -279,8 +279,8 @@
 	g->xoff = -1;
 	g->yoff = -1;
 	bitmap = slot->bitmap;
-	g->width = bitmap.width;
-	g->height = bitmap.rows;
+	g->width = (int)bitmap.width;
+	g->height = (int)bitmap.rows;
 
 	if (g->width && g->height) {
 		if (sharp) {
