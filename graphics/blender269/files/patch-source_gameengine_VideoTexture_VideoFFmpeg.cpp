--- source/gameengine/VideoTexture/VideoFFmpeg.cpp.orig	2015-07-07 09:02:51 UTC
+++ source/gameengine/VideoTexture/VideoFFmpeg.cpp
@@ -99,7 +99,7 @@ bool VideoFFmpeg::release()
 	}
 	if (m_formatCtx)
 	{
-		av_close_input_file(m_formatCtx);
+		avformat_close_input(&m_formatCtx);
 		m_formatCtx = NULL;
 	}
 	if (m_frame)
@@ -176,7 +176,7 @@ int VideoFFmpeg::openStream(const char *
 
 	if (avformat_find_stream_info(formatCtx, NULL) < 0)
 	{
-		av_close_input_file(formatCtx);
+		avformat_close_input(&formatCtx);
 		return -1;
 	}
 
@@ -195,7 +195,7 @@ int VideoFFmpeg::openStream(const char *
 
 	if (videoStream==-1) 
 	{
-		av_close_input_file(formatCtx);
+		avformat_close_input(&formatCtx);
 		return -1;
 	}
 
@@ -205,13 +205,13 @@ int VideoFFmpeg::openStream(const char *
 	codec=avcodec_find_decoder(codecCtx->codec_id);
 	if (codec==NULL) 
 	{
-		av_close_input_file(formatCtx);
+		avformat_close_input(&formatCtx);
 		return -1;
 	}
 	codecCtx->workaround_bugs = 1;
 	if (avcodec_open2(codecCtx, codec, NULL) < 0)
 	{
-		av_close_input_file(formatCtx);
+		avformat_close_input(&formatCtx);
 		return -1;
 	}
 
@@ -278,7 +278,7 @@ int VideoFFmpeg::openStream(const char *
 	if (!m_imgConvertCtx) {
 		avcodec_close(m_codecCtx);
 		m_codecCtx = NULL;
-		av_close_input_file(m_formatCtx);
+		avformat_close_input(&m_formatCtx);
 		m_formatCtx = NULL;
 		av_free(m_frame);
 		m_frame = NULL;
