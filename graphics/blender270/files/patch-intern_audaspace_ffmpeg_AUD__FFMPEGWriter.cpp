--- intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp.orig	2014-04-12 00:16:41 UTC
+++ intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp
@@ -202,7 +202,7 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 			m_frame = av_frame_alloc();
 			if (!m_frame)
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
-			avcodec_get_frame_defaults(m_frame);
+			av_frame_unref(m_frame);
 			m_frame->linesize[0]    = m_input_size * samplesize;
 			m_frame->format         = m_codecCtx->sample_fmt;
 			m_frame->nb_samples     = m_input_size;
