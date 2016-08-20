--- plugins/sf2_player/sf2_player.cpp.orig	2015-03-08 02:47:14 UTC
+++ plugins/sf2_player/sf2_player.cpp
@@ -23,6 +23,11 @@
  *
  */
 
+#include <math.h>
+#include <sys/param.h>
+#if __FreeBSD_version <= 704100 || (__FreeBSD_version >= 800000 && __FreeBSD_version < 802502) || (__FreeBSD_version >= 900000 && __FreeBSD_version < 900027)
+	#define log2(x)             ( log (x) * (1./M_LN2) )
+#endif
 #include <QDebug>
 #include <QLayout>
 #include <QLabel>
