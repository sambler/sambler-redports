--- src/gui/setup_dialog.cpp
+++ src/gui/setup_dialog.cpp
@@ -60,6 +60,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiDummy.h"
@@ -647,6 +648,11 @@ setupDialog::setupDialog( ConfigTabs _tab_to_open ) :
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

