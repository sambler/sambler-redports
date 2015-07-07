--- source/blender/blenfont/intern/blf_glyph.c.orig	2013-06-28 13:05:15 UTC
+++ source/blender/blenfont/intern/blf_glyph.c
@@ -279,8 +279,8 @@ GlyphBLF *blf_glyph_add(FontBLF *font, u
 	g->xoff = -1;
 	g->yoff = -1;
 	bitmap = slot->bitmap;
-	g->width = bitmap.width;
-	g->height = bitmap.rows;
+	g->width = (int)bitmap.width;
+	g->height = (int)bitmap.rows;
 
 	if (g->width && g->height) {
 		if (sharp) {
