--- intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp.orig	2014-06-26 06:13:52 UTC
+++ intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp
@@ -170,7 +170,7 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
 
 			if(codec->sample_fmts) {
-				// Check if the prefered sample format for this codec is supported.
+				// Check if the preferred sample format for this codec is supported.
 				const enum AVSampleFormat *p = codec->sample_fmts;
 				for(; *p != -1; p++) {
 					if(*p == m_stream->codec->sample_fmt)
@@ -202,7 +202,7 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 			m_frame = av_frame_alloc();
 			if (!m_frame)
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
-			avcodec_get_frame_defaults(m_frame);
+			av_frame_unref(m_frame);
 			m_frame->linesize[0]    = m_input_size * samplesize;
 			m_frame->format         = m_codecCtx->sample_fmt;
 			m_frame->nb_samples     = m_input_size;
