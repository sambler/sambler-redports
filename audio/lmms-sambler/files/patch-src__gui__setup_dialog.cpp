--- ./src/gui/setup_dialog.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./src/gui/setup_dialog.cpp	2014-08-29 03:52:45.161454924 +0930
@@ -60,6 +60,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiDummy.h"
@@ -672,6 +673,11 @@
 					new MidiAlsaRaw::setupWidget( msw );
 #endif
 
+#ifdef LMMS_HAVE_JACK
+    m_midiIfaceSetupWidgets[MidiJack::name()] =
+                    new MidiJack::setupWidget( msw );
+#endif
+
 #ifdef LMMS_HAVE_OSS
 	m_midiIfaceSetupWidgets[MidiOss::name()] =
 					new MidiOss::setupWidget( msw );
