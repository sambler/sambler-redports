--- source/gameengine/VideoTexture/VideoFFmpeg.cpp.orig	2015-07-07 06:07:10 UTC
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
@@ -385,15 +385,7 @@ void *VideoFFmpeg::cacheThread(void *dat
 					{
 						if (video->m_deinterlace) 
 						{
-							if (avpicture_deinterlace(
-								(AVPicture*) video->m_frameDeinterlaced,
-								(const AVPicture*) video->m_frame,
-								video->m_codecCtx->pix_fmt,
-								video->m_codecCtx->width,
-								video->m_codecCtx->height) >= 0)
-							{
-								input = video->m_frameDeinterlaced;
-							}
+							input = video->m_frameDeinterlaced;
 						}
 						// convert to RGB24
 						sws_scale(video->m_imgConvertCtx,
@@ -1032,15 +1024,7 @@ AVFrame *VideoFFmpeg::grabFrame(long pos
 
 				if (m_deinterlace) 
 				{
-					if (avpicture_deinterlace(
-						(AVPicture*) m_frameDeinterlaced,
-						(const AVPicture*) m_frame,
-						m_codecCtx->pix_fmt,
-						m_codecCtx->width,
-						m_codecCtx->height) >= 0)
-					{
-						input = m_frameDeinterlaced;
-					}
+					input = m_frameDeinterlaced;
 				}
 				// convert to RGB24
 				sws_scale(m_imgConvertCtx,
