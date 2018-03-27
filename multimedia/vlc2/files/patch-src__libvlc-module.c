--- src/libvlc-module.c.orig	2014-10-14 16:37:03 UTC
+++ src/libvlc-module.c
@@ -777,8 +777,8 @@
 #  define DVD_DEVICE     "/dev/sr0"
 #  define CD_DEVICE      "/dev/sr0"
 # else
-#  define DVD_DEVICE     "/dev/dvd"
-#  define CD_DEVICE      "/dev/cdrom"
+#  define DVD_DEVICE     "${WITH_DVD_DEVICE}"
+#  define CD_DEVICE      "${WITH_CDROM_DEVICE}"
 # endif
 #endif
 
