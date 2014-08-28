--- ./include/AudioPortAudio.h.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./include/AudioPortAudio.h	2014-08-29 05:37:23.566455269 +0930
@@ -45,7 +45,7 @@
 
 #ifdef LMMS_HAVE_PORTAUDIO
 
-#include <portaudio.h>
+#include <portaudio2/portaudio.h>
 
 #include "AudioDevice.h"
 
