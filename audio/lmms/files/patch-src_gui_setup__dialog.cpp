--- src/gui/setup_dialog.cpp.orig	2015-03-08 02:47:14 UTC
+++ src/gui/setup_dialog.cpp
@@ -60,6 +60,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiDummy.h"
@@ -672,6 +673,11 @@ setupDialog::setupDialog( ConfigTabs _ta
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
