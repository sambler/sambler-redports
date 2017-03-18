--- intern/audaspace/ffmpeg/AUD_FFMPEGReader.cpp.orig	2015-03-25 21:26:13 UTC
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
