--- source/blender/imbuf/intern/util.c.orig	2015-07-07 06:04:34 UTC
+++ source/blender/imbuf/intern/util.c
@@ -312,7 +312,7 @@ static int isffmpeg(const char *filename
 
 	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
 		if (UTIL_DEBUG) fprintf(stderr, "isffmpeg: avformat_find_stream_info failed\n");
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return 0;
 	}
 
@@ -331,7 +331,7 @@ static int isffmpeg(const char *filename
 		}
 
 	if (videoStream == -1) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return 0;
 	}
 
@@ -340,17 +340,17 @@ static int isffmpeg(const char *filename
 	/* Find the decoder for the video stream */
 	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
 	if (pCodec == NULL) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return 0;
 	}
 
 	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return 0;
 	}
 
 	avcodec_close(pCodecCtx);
-	av_close_input_file(pFormatCtx);
+	avformat_close_input(&pFormatCtx);
 
 	return 1;
 }
