--- drivers/rtaudio/audio_driver_rtaudio.cpp.orig	2016-05-13 06:06:31 UTC
+++ drivers/rtaudio/audio_driver_rtaudio.cpp
@@ -18,8 +18,14 @@
 
 #ifdef OSX_ENABLED
 	return "RtAudio-OSX";
-#elif defined(UNIX_ENABLED)
+#elif defined(UNIX_ENABLED) && (defined(ALSA_ENABLED) || defined(PULSEAUDIO_ENABLED) || defined(OSS_ENABLED))
+#if defined(OSS_ENABLED)
+	return "RtAudio-OSS";
+#elif defined(ALSA_ENABLED)
 	return "RtAudio-ALSA";
+#elif defined(PULSEAUDIO_ENABLED)
+	return "RtAudio-PulseAudio";
+#endif
 #elif defined(WINDOWS_ENABLED)
 	return "RtAudio-DirectSound";
 #else
