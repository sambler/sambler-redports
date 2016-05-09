--- sdlkit.h.orig	2016-05-09 12:22:23 UTC
+++ sdlkit.h
@@ -92,7 +92,7 @@ static void ddkSetMode (int width, int h
 
 #include <gtk/gtk.h>
 #include <string.h>
-#include <malloc.h>
+#include <stdlib.h>
 
 #if GTK_CHECK_VERSION(3,0,0)
 
