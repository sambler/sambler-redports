--- ./plugins/sf2_player/sf2_player.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./plugins/sf2_player/sf2_player.cpp	2014-08-29 05:37:23.613455337 +0930
@@ -23,6 +23,10 @@
  *
  */
 
+#include <math.h>
+#if __FreeBSD_version <= 704100 || (__FreeBSD_version >= 800000 && __FreeBSD_version < 802502) || (__FreeBSD_version >= 900000 && __FreeBSD_version < 900027)
+	#define log2(x)             ( log (x) * (1./M_LN2) )
+#endif
 #include <QtCore/QDebug>
 #include <QtGui/QLayout>
 #include <QtGui/QLabel>
