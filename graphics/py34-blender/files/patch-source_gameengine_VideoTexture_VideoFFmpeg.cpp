--- source/gameengine/VideoTexture/VideoFFmpeg.cpp.orig	2015-11-04 20:32:15 UTC
+++ source/gameengine/VideoTexture/VideoFFmpeg.cpp
@@ -140,23 +140,23 @@ bool VideoFFmpeg::release()
 AVFrame	*VideoFFmpeg::allocFrameRGB()
 {
 	AVFrame *frame;
-	frame = avcodec_alloc_frame();
+	frame = av_frame_alloc();
 	if (m_format == RGBA32)
 	{
 		avpicture_fill((AVPicture*)frame, 
 			(uint8_t*)MEM_callocN(avpicture_get_size(
-				PIX_FMT_RGBA,
+				AV_PIX_FMT_RGBA,
 				m_codecCtx->width, m_codecCtx->height),
 				"ffmpeg rgba"),
-			PIX_FMT_RGBA, m_codecCtx->width, m_codecCtx->height);
+			AV_PIX_FMT_RGBA, m_codecCtx->width, m_codecCtx->height);
 	} else 
 	{
 		avpicture_fill((AVPicture*)frame, 
 			(uint8_t*)MEM_callocN(avpicture_get_size(
-				PIX_FMT_RGB24,
+				AV_PIX_FMT_RGB24,
 				m_codecCtx->width, m_codecCtx->height),
 				"ffmpeg rgb"),
-			PIX_FMT_RGB24, m_codecCtx->width, m_codecCtx->height);
+			AV_PIX_FMT_RGB24, m_codecCtx->width, m_codecCtx->height);
 	}
 	return frame;
 }
@@ -236,8 +236,8 @@ int VideoFFmpeg::openStream(const char *
 	m_codecCtx = codecCtx;
 	m_formatCtx = formatCtx;
 	m_videoStream = videoStream;
-	m_frame = avcodec_alloc_frame();
-	m_frameDeinterlaced = avcodec_alloc_frame();
+	m_frame = av_frame_alloc();
+	m_frameDeinterlaced = av_frame_alloc();
 
 	// allocate buffer if deinterlacing is required
 	avpicture_fill((AVPicture*)m_frameDeinterlaced, 
@@ -248,10 +248,10 @@ int VideoFFmpeg::openStream(const char *
 		m_codecCtx->pix_fmt, m_codecCtx->width, m_codecCtx->height);
 
 	// check if the pixel format supports Alpha
-	if (m_codecCtx->pix_fmt == PIX_FMT_RGB32 ||
-		m_codecCtx->pix_fmt == PIX_FMT_BGR32 ||
-		m_codecCtx->pix_fmt == PIX_FMT_RGB32_1 ||
-		m_codecCtx->pix_fmt == PIX_FMT_BGR32_1) 
+	if (m_codecCtx->pix_fmt == AV_PIX_FMT_RGB32 ||
+		m_codecCtx->pix_fmt == AV_PIX_FMT_BGR32 ||
+		m_codecCtx->pix_fmt == AV_PIX_FMT_RGB32_1 ||
+		m_codecCtx->pix_fmt == AV_PIX_FMT_BGR32_1) 
 	{
 		// allocate buffer to store final decoded frame
 		m_format = RGBA32;
@@ -262,7 +262,7 @@ int VideoFFmpeg::openStream(const char *
 			m_codecCtx->pix_fmt,
 			m_codecCtx->width,
 			m_codecCtx->height,
-			PIX_FMT_RGBA,
+			AV_PIX_FMT_RGBA,
 			SWS_FAST_BILINEAR,
 			NULL, NULL, NULL);
 	} else
@@ -276,7 +276,7 @@ int VideoFFmpeg::openStream(const char *
 			m_codecCtx->pix_fmt,
 			m_codecCtx->width,
 			m_codecCtx->height,
-			PIX_FMT_RGB24,
+			AV_PIX_FMT_RGB24,
 			SWS_FAST_BILINEAR,
 			NULL, NULL, NULL);
 	}
@@ -392,15 +392,7 @@ void *VideoFFmpeg::cacheThread(void *dat
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
@@ -1057,15 +1049,7 @@ AVFrame *VideoFFmpeg::grabFrame(long pos
 
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
