--- src/ffmpeg.imageio/ffmpeginput.cpp.orig	2018-06-14 18:02:46 UTC
+++ src/ffmpeg.imageio/ffmpeginput.cpp
@@ -87,6 +87,9 @@ inline int avpicture_fill(AVPicture *pic
 //we're supposed to use ->codecpar instead.
 #define USE_CODECPAR (LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(57,24,0))
 
+#if (LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(56, 56, 100))
+#  define CODEC_CAP_DELAY AV_CODEC_CAP_DELAY
+#endif
 
 #include <boost/thread/once.hpp>
 
