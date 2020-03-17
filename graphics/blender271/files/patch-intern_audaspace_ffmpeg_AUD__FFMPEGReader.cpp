--- intern/audaspace/ffmpeg/AUD_FFMPEGReader.cpp.orig	2014-06-26 06:13:52 UTC
+++ intern/audaspace/ffmpeg/AUD_FFMPEGReader.cpp
@@ -58,9 +58,9 @@ int AUD_FFMPEGReader::decode(AVPacket& p
 		got_frame = 0;
 
 		if(!frame)
-			frame = avcodec_alloc_frame();
+			frame = av_frame_alloc();
 		else
-			avcodec_get_frame_defaults(frame);
+			av_frame_unref(frame);
 
 		read_length = avcodec_decode_audio4(m_codecCtx, frame, &got_frame, &packet);
 		if(read_length < 0)
@@ -264,9 +264,9 @@ AUD_FFMPEGReader::AUD_FFMPEGReader(boost
 		m_membuffer(buffer),
 		m_membufferpos(0)
 {
-	m_membuf = reinterpret_cast<data_t*>(av_malloc(FF_MIN_BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE));
+	m_membuf = reinterpret_cast<data_t*>(av_malloc(AV_INPUT_BUFFER_MIN_SIZE + AV_INPUT_BUFFER_PADDING_SIZE));
 
-	m_aviocontext = avio_alloc_context(m_membuf, FF_MIN_BUFFER_SIZE, 0, this,
+	m_aviocontext = avio_alloc_context(m_membuf, AV_INPUT_BUFFER_MIN_SIZE, 0, this,
 									   read_packet, NULL, seek_packet);
 
 	if(!m_aviocontext)
