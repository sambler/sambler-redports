--- intern/audaspace/ffmpeg/AUD_FFMPEGReader.cpp.orig	2015-10-24 05:32:52 UTC
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
@@ -389,9 +389,7 @@ void AUD_FFMPEGReader::seek(int position
 							int length = AUD_DEFAULT_BUFFER_SIZE;
 							AUD_Buffer buffer(length * AUD_SAMPLE_SIZE(m_specs));
 							bool eos;
-							for(int len = position - m_position;
-								length == AUD_DEFAULT_BUFFER_SIZE;
-								len -= AUD_DEFAULT_BUFFER_SIZE)
+							for(int len = position - m_position; len > 0; len -= AUD_DEFAULT_BUFFER_SIZE)
 							{
 								if(len < AUD_DEFAULT_BUFFER_SIZE)
 									length = len;
