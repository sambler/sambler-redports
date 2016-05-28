--- drivers/rtaudio/RtAudio.h.orig	2016-05-13 06:06:31 UTC
+++ drivers/rtaudio/RtAudio.h
@@ -6,7 +6,13 @@
 
 #elif defined(UNIX_ENABLED)
 
+#if defined(OSS_ENABLED)
+#define __LINUX_OSS__
+#elif defined(ALSA_ENABLED)
 #define __LINUX_ALSA__
+#elif defined(PULSEAUDIO_ENABLED)
+#define __LINUX_PULSE__
+#endif
 
 #elif defined(WINDOWS_ENABLED)
 
