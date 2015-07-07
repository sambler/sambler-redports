--- source/blender/imbuf/intern/anim_movie.c.orig	2015-07-07 08:48:58 UTC
+++ source/blender/imbuf/intern/anim_movie.c
@@ -486,7 +486,7 @@ static int startffmpeg(struct anim *anim
 	}
 
 	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
@@ -507,7 +507,7 @@ static int startffmpeg(struct anim *anim
 		}
 
 	if (videoStream == -1) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
@@ -516,14 +516,14 @@ static int startffmpeg(struct anim *anim
 	/* Find the decoder for the video stream */
 	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
 	if (pCodec == NULL) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
 	pCodecCtx->workaround_bugs = 1;
 
 	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
@@ -575,7 +575,7 @@ static int startffmpeg(struct anim *anim
 		fprintf(stderr,
 		        "ffmpeg has changed alloc scheme ... ARGHHH!\n");
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrameDeinterlaced);
 		av_free(anim->pFrame);
@@ -616,7 +616,7 @@ static int startffmpeg(struct anim *anim
 		fprintf(stderr,
 		        "Can't transform color space??? Bailing out...\n");
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrameDeinterlaced);
 		av_free(anim->pFrame);
@@ -1142,7 +1142,7 @@ static void free_anim_ffmpeg(struct anim
 
 	if (anim->pCodecCtx) {
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrame);
 
