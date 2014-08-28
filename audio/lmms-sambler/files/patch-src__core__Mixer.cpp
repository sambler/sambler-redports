--- ./src/core/Mixer.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./src/core/Mixer.cpp	2014-08-29 03:52:45.156454776 +0930
@@ -53,6 +53,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiDummy.h"
@@ -858,6 +859,19 @@
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
