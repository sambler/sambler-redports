--- ./core/pngio.cpp.orig	2012-02-28 04:28:28.000000000 +1030
+++ ./core/pngio.cpp	2012-02-28 16:50:09.000000000 +1030
@@ -410,7 +410,7 @@
 
 	// cleanup
 	png_write_end(png, info);
-	png_destroy_write_struct(&png, &info);
+	//png_destroy_write_struct(&png, &info);
 
 	fclose(fp);
 }
