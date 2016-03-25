--- src/core/Mixer.cpp.orig	2016-02-17 05:57:44 UTC
+++ src/core/Mixer.cpp
@@ -49,6 +49,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiApple.h"
@@ -892,6 +873,19 @@ MidiClient * Mixer::tryMidiClients()
 	}
 #endif
 
+#ifdef LMMS_HAVE_JACK
+	if( client_name == MidiJack::name() || client_name == "" )
+	{
+		MidiJack * mjack = new MidiJack;
+		if( mjack->isRunning() )
+		{
+			m_midiClientName = MidiJack::name();
+			return mjack;
+		}
+		delete mjack;
+	}
+#endif
+
 #ifdef LMMS_HAVE_OSS
 	if( client_name == MidiOss::name() || client_name == "" )
 	{
