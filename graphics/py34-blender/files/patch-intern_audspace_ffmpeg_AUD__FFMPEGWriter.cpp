--- intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp.orig	2015-10-24 05:32:52 UTC
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
@@ -224,7 +224,9 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 				if(avio_open(&m_formatCtx->pb, filename.c_str(), AVIO_FLAG_WRITE))
 					AUD_THROW(AUD_ERROR_FILE, file_error);
 
-				avformat_write_header(m_formatCtx, NULL);
+				if(avformat_write_header(m_formatCtx, NULL) < 0) {
+					throw;
+				}
 			}
 			catch(AUD_Exception&)
 			{
