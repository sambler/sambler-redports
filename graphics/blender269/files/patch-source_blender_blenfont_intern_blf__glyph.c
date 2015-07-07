--- source/blender/blenfont/intern/blf_glyph.c.orig	2013-09-01 00:46:04 UTC
+++ source/blender/blenfont/intern/blf_glyph.c
@@ -273,8 +273,8 @@ GlyphBLF *blf_glyph_add(FontBLF *font, u
 	g->xoff = -1;
 	g->yoff = -1;
 	bitmap = slot->bitmap;
-	g->width = bitmap.width;
-	g->height = bitmap.rows;
+	g->width = (int)bitmap.width;
+	g->height = (int)bitmap.rows;
 
 	if (g->width && g->height) {
 		if (sharp) {
