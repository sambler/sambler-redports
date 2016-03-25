--- src/core/audio/AudioJack.cpp.orig	2016-02-17 05:57:44 UTC
+++ src/core/audio/AudioJack.cpp
@@ -40,7 +40,7 @@
 #include "LcdSpinBox.h"
 #include "AudioPort.h"
 #include "MainWindow.h"
-
+#include "MidiJack.h"
 
 
 
@@ -51,6 +51,7 @@ AudioJack::AudioJack( bool & _success_fu
 								_mixer ),
 	m_client( NULL ),
 	m_active( false ),
+	m_midiClient( NULL ),
 	m_tempOutBufs( new jack_default_audio_sample_t *[channels()] ),
 	m_outBuf( new surroundSampleFrame[mixer()->framesPerPeriod()] ),
 	m_framesDoneInCurBuf( 0 ),
@@ -122,7 +123,15 @@ void AudioJack::restartAfterZombified()
 
 
 
+AudioJack* AudioJack::addMidiClient(MidiJack *midiClient)
+{
+	if( m_client == NULL )
+		return NULL;
 
+	m_midiClient = midiClient;
+
+	return this;
+}
 
 bool AudioJack::initJackClient()
 {
@@ -330,6 +339,14 @@ void AudioJack::renamePort( AudioPort * 
 
 int AudioJack::processCallback( jack_nframes_t _nframes, void * _udata )
 {
+	// do midi processing first so that midi input can
+	// add to the following sound processing
+	if( m_midiClient && _nframes > 0 )
+	{
+		m_midiClient->JackMidiRead(_nframes);
+		m_midiClient->JackMidiWrite(_nframes);
+	}
+
 	for( int c = 0; c < channels(); ++c )
 	{
 		m_tempOutBufs[c] =
