--- include/AudioPortAudio.h.orig	2016-03-25 18:11:14 UTC
+++ include/AudioPortAudio.h
@@ -45,11 +45,7 @@ public:
 
 #ifdef LMMS_HAVE_PORTAUDIO
 
-#if defined(__FreeBSD__)
-#include <portaudio2/portaudio.h>
-#else
 #include <portaudio.h>
-#endif
 
 #include "AudioDevice.h"
 #include "AudioDeviceSetupWidget.h"
