--- include/AudioJack.h.orig	2016-02-17 05:57:44 UTC
+++ include/AudioJack.h
@@ -37,9 +37,9 @@
 #include "AudioDevice.h"
 #include "AudioDeviceSetupWidget.h"
 
-
 class QLineEdit;
 class LcdSpinBox;
+class MidiJack;
 
 
 class AudioJack : public QObject, public AudioDevice
@@ -49,6 +49,12 @@ public:
 	AudioJack( bool & _success_ful, Mixer* mixer );
 	virtual ~AudioJack();
 
+	// this is to allow the jack midi connection to use the same jack client connection
+	// the jack callback is handled here, we call the midi client so that it can read
+	// it's midi data during the callback
+	AudioJack * addMidiClient(MidiJack *midiClient);
+	jack_client_t * jackClient() {return m_client;};
+
 	inline static QString name()
 	{
 		return QT_TRANSLATE_NOOP( "setupWidget",
@@ -98,6 +104,7 @@ private:
 	bool m_active;
 	bool m_stopped;
 
+	MidiJack *m_midiClient;
 	QVector<jack_port_t *> m_outputPorts;
 	jack_default_audio_sample_t * * m_tempOutBufs;
 	surroundSampleFrame * m_outBuf;
