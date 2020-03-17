--- intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp.orig	2014-06-26 06:13:52 UTC
+++ intern/audaspace/ffmpeg/AUD_FFMPEGWriter.cpp
@@ -163,14 +163,14 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 		try
 		{
 			if(m_formatCtx->oformat->flags & AVFMT_GLOBALHEADER)
-				m_codecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
+				m_codecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
 
 			AVCodec* codec = avcodec_find_encoder(m_codecCtx->codec_id);
 			if(!codec)
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
 
 			if(codec->sample_fmts) {
-				// Check if the prefered sample format for this codec is supported.
+				// Check if the preferred sample format for this codec is supported.
 				const enum AVSampleFormat *p = codec->sample_fmts;
 				for(; *p != -1; p++) {
 					if(*p == m_stream->codec->sample_fmt)
@@ -185,11 +185,11 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 			if(avcodec_open2(m_codecCtx, codec, NULL))
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
 
-			m_output_buffer.resize(FF_MIN_BUFFER_SIZE);
+			m_output_buffer.resize(AV_INPUT_BUFFER_MIN_SIZE);
 			int samplesize = AUD_MAX(AUD_SAMPLE_SIZE(m_specs), AUD_DEVICE_SAMPLE_SIZE(m_specs));
 
 			if(m_codecCtx->frame_size <= 1) {
-				m_input_size = FF_MIN_BUFFER_SIZE * 8 / m_codecCtx->bits_per_coded_sample / m_codecCtx->channels;
+				m_input_size = AV_INPUT_BUFFER_MIN_SIZE * 8 / m_codecCtx->bits_per_coded_sample / m_codecCtx->channels;
 				m_input_buffer.resize(m_input_size * samplesize);
 			}
 			else
@@ -202,7 +202,7 @@ AUD_FFMPEGWriter::AUD_FFMPEGWriter(std::
 			m_frame = av_frame_alloc();
 			if (!m_frame)
 				AUD_THROW(AUD_ERROR_FFMPEG, codec_error);
-			avcodec_get_frame_defaults(m_frame);
+			av_frame_unref(m_frame);
 			m_frame->linesize[0]    = m_input_size * samplesize;
 			m_frame->format         = m_codecCtx->sample_fmt;
 			m_frame->nb_samples     = m_input_size;
