--- src/core/Mixer.cpp.orig	2015-03-08 02:47:14 UTC
+++ src/core/Mixer.cpp
@@ -52,6 +52,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiDummy.h"
@@ -855,6 +856,19 @@ MidiClient * Mixer::tryMidiClients()
 	}
 #endif
 
+#ifdef LMMS_HAVE_JACK
+    if( client_name == MidiJack::name() || client_name == "" )
+    {
+        MidiJack * moss = new MidiJack;
+        if( moss->isRunning() )
+        {
+            m_midiClientName = MidiJack::name();
+            return moss;
+        }
+        delete moss;
+    }
+#endif
+
 #ifdef LMMS_HAVE_OSS
 	if( client_name == MidiOss::name() || client_name == "" )
 	{
