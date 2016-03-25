--- src/core/midi/MidiJack.cpp.orig	2016-03-25 20:39:00 UTC
+++ src/core/midi/MidiJack.cpp
@@ -0,0 +1,214 @@
+/*
+ * MidiJack.cpp - MIDI client for Jack
+ *
+ * Copyright (c) 2015 Shane Ambler <develop/at/shaneware.biz>
+ *
+ * This file is part of LMMS - http://lmms.io
+ *
+ * This program is free software; you can redistribute it and/or
+ * modify it under the terms of the GNU General Public
+ * License as published by the Free Software Foundation; either
+ * version 2 of the License, or (at your option) any later version.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
+ * General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public
+ * License along with this program (see COPYING); if not, write to the
+ * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
+ * Boston, MA 02110-1301 USA.
+ *
+ */
+
+#include "MidiJack.h"
+
+#ifdef LMMS_HAVE_JACK
+
+#include <QCompleter>
+#include <QDirModel>
+#include <QMessageBox>
+#include <QTranslator>
+
+#ifdef LMMS_HAVE_STDLIB_H
+#include <stdlib.h>
+#endif
+
+#include "ConfigManager.h"
+#include "gui_templates.h"
+#include "GuiApplication.h"
+#include "Engine.h"
+#include "Mixer.h"
+#include "MainWindow.h"
+
+/* callback functions for jack */
+static int JackMidiProcessCallback(jack_nframes_t nframes, void *arg)
+{
+	MidiJack *jmd = (MidiJack *)arg;
+
+	if (nframes <= 0)
+		return (0);
+
+	jmd->JackMidiRead(nframes);
+	jmd->JackMidiWrite(nframes);
+
+	return (0);
+}
+
+static void JackMidiShutdown(void *arg)
+{
+	// TODO: support translations here
+	const QString mess_short = "JACK server down";
+	const QString mess_long = "The JACK server seems to have been shutdown.";
+	QMessageBox::information( gui->mainWindow(), mess_short, mess_long );
+}
+
+MidiJack::MidiJack() :
+	MidiClientRaw(),
+	m_input_port( NULL ),
+	m_output_port( NULL ),
+	m_quit( false )
+{
+	// if jack is used for audio then we share the connection
+	// AudioJack creates and maintains the jack connection
+	// and also handles the callback, we pass it our address
+	// so that we can also process during the callback
+
+	if(Engine::mixer()->audioDevName() == AudioJack::name() )
+	{
+		// if a jack connection has been created for audio we use that
+		m_jackAudio = dynamic_cast<AudioJack*>(Engine::mixer()->audioDev())->addMidiClient(this);
+	}else{
+		m_jackAudio = NULL;
+		m_jackClient = jack_client_open(probeDevice().toLatin1().data(),
+										JackNoStartServer, NULL);
+
+		if(m_jackClient)
+		{
+			jack_set_process_callback(m_jackClient,
+							JackMidiProcessCallback, this);
+			jack_on_shutdown(m_jackClient,
+							JackMidiShutdown, 0);
+		}
+	}
+
+	if(jackClient())
+	{
+		m_output_port = jack_port_register(
+				jackClient(), "midi_TX", JACK_DEFAULT_MIDI_TYPE,
+				JackPortIsOutput, 0);
+
+		m_input_port = jack_port_register(
+				jackClient(), "midi_RX", JACK_DEFAULT_MIDI_TYPE,
+				JackPortIsInput, 0);
+
+		if(jack_activate(jackClient()) == 0 )
+		{
+			// only start thread, if we have an active jack client.
+			start( QThread::LowPriority );
+		}
+	}
+}
+
+MidiJack::~MidiJack()
+{
+	if(jackClient())
+	{
+		if( jack_port_unregister( jackClient(), m_input_port) != 0){
+			printf("Failed to unregister jack midi input\n");
+		}
+
+		if( jack_port_unregister( jackClient(), m_output_port) != 0){
+			printf("Failed to unregister jack midi output\n");
+		}
+
+		if(m_jackClient)
+		{
+			// an m_jackClient means we are handling the jack connection
+			if( jack_deactivate(m_jackClient) != 0){
+				printf("Failed to deactivate jack midi client\n");
+			}
+
+			if( jack_client_close(m_jackClient) != 0){
+				printf("Failed close jack midi client\n");
+			}
+		}
+	}
+	if( isRunning() )
+	{
+		m_quit = true;
+		wait( 1000 );
+		terminate();
+	}
+}
+
+jack_client_t* MidiJack::jackClient()
+{
+	if( m_jackAudio == NULL && m_jackClient == NULL)
+		return NULL;
+
+	if( m_jackAudio == NULL && m_jackClient )
+		return m_jackClient;
+
+	return m_jackAudio->jackClient();
+}
+
+QString MidiJack::probeDevice()
+{
+	QString jid = ConfigManager::inst()->value( "midijack", "lmms" );
+	if( jid.isEmpty() )
+	{
+		return "lmms";
+	}
+	return jid;
+}
+
+void MidiJack::sendByte( const unsigned char c )
+{
+	//m_midiDev.putChar( c );
+}
+
+// we read data from jack
+void MidiJack::JackMidiRead(jack_nframes_t nframes)
+{
+	unsigned int i,b;
+	void* port_buf = jack_port_get_buffer(m_input_port, nframes);
+	jack_midi_event_t in_event;
+	jack_nframes_t event_index = 0;
+	jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
+
+	jack_midi_event_get(&in_event, port_buf, 0);
+	for(i=0; i<nframes; i++)
+	{
+		if((in_event.time == i) && (event_index < event_count))
+		{
+			// lmms is setup to parse bytes coming from a device
+			// parse it byte by byte as it expects
+			for(b=0;b<in_event.size;b++)
+				parseData( *(in_event.buffer + b) );
+
+			event_index++;
+			if(event_index < event_count)
+				jack_midi_event_get(&in_event, port_buf, event_index);
+		}
+	}
+}
+
+// we write data to jack
+void MidiJack::JackMidiWrite(jack_nframes_t nframes)
+{
+	// TODO: write midi data to jack port
+}
+
+void MidiJack::run()
+{
+	while( m_quit == false )
+	{
+		// we sleep the thread to keep it alive
+		// midi processing is handled by jack server callbacks
+		sleep(1);
+	}
+}
+
+#endif // LMMS_HAVE_JACK
