--- src/avbin.c.orig	2016-10-26 09:54:18 UTC
+++ src/avbin.c	2016-10-26
@@ -34,6 +34,9 @@
 
 static int32_t avbin_thread_count = 1;
 
+/* this has been removed from ffmpeg2 add as temp solution */
+#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio
+
 struct _AVbinFile {
     AVFormatContext *context;
     AVPacket *packet;
@@ -487,9 +490,9 @@ int32_t avbin_decode_video(AVbinStream *
         return AVBIN_RESULT_ERROR;
 
 
-    avpicture_fill(&picture_rgb, data_out, PIX_FMT_RGB24, width, height);
+    avpicture_fill(&picture_rgb, data_out, AV_PIX_FMT_RGB24, width, height);
     static struct SwsContext *img_convert_ctx = NULL;
-    img_convert_ctx = sws_getCachedContext(img_convert_ctx,width, height,stream->codec_context->pix_fmt,width, height,PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
+    img_convert_ctx = sws_getCachedContext(img_convert_ctx,width, height,stream->codec_context->pix_fmt,width, height,AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
     sws_scale(img_convert_ctx, (const uint8_t* const*)stream->frame->data, stream->frame->linesize,0, height, picture_rgb.data, picture_rgb.linesize);
     
     return used;
