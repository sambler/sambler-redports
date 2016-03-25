--- src/gui/SetupDialog.cpp.orig	2016-02-17 05:57:44 UTC
+++ src/gui/SetupDialog.cpp
@@ -63,6 +63,7 @@
 // platform-specific midi-interface-classes
 #include "MidiAlsaRaw.h"
 #include "MidiAlsaSeq.h"
+#include "MidiJack.h"
 #include "MidiOss.h"
 #include "MidiWinMM.h"
 #include "MidiApple.h"
@@ -140,7 +141,6 @@ SetupDialog::SetupDialog( ConfigTabs _ta
 	setWindowIcon( embed::getIconPixmap( "setup_general" ) );
 	setWindowTitle( tr( "Setup LMMS" ) );
 	setModal( true );
-	setFixedSize( 452, 520 );
 
 	Engine::projectJournal()->setJournalling( false );
 
@@ -412,8 +412,8 @@ SetupDialog::SetupDialog( ConfigTabs _ta
 	pathScroll->move( 0, 30 );
 	pathSelectors->resize( 360, pathsHeight - 50 );
 
-	const int txtLength = 284;
-	const int btnStart = 297;
+	const int txtLength = 285;
+	const int btnStart = 305;
 
 
 	// working-dir
@@ -840,6 +840,11 @@ SetupDialog::SetupDialog( ConfigTabs _ta
 					MidiSetupWidget::create<MidiAlsaRaw>( msw );
 #endif
 
+#ifdef LMMS_HAVE_JACK
+	m_midiIfaceSetupWidgets[MidiJack::name()] =
+					MidiSetupWidget::create<MidiJack>( msw );
+#endif
+
 #ifdef LMMS_HAVE_OSS
 	m_midiIfaceSetupWidgets[MidiOss::name()] =
 					MidiSetupWidget::create<MidiOss>( msw );
