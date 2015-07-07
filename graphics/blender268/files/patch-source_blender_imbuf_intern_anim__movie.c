--- source/blender/imbuf/intern/anim_movie.c.orig	2015-07-07 07:12:07 UTC
+++ source/blender/imbuf/intern/anim_movie.c
@@ -487,7 +487,7 @@ static int startffmpeg(struct anim *anim
 	}
 
 	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
@@ -508,7 +508,7 @@ static int startffmpeg(struct anim *anim
 		}
 
 	if (videoStream == -1) {
-		av_close_input_file(pFormatCtx);
+		avformat_close_input(&pFormatCtx);
 		return -1;
 	}
 
@@ -517,14 +517,14 @@ static int startffmpeg(struct anim *anim
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
 
@@ -576,7 +576,7 @@ static int startffmpeg(struct anim *anim
 		fprintf(stderr,
 		        "ffmpeg has changed alloc scheme ... ARGHHH!\n");
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrameDeinterlaced);
 		av_free(anim->pFrame);
@@ -617,7 +617,7 @@ static int startffmpeg(struct anim *anim
 		fprintf(stderr,
 		        "Can't transform color space??? Bailing out...\n");
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrameDeinterlaced);
 		av_free(anim->pFrame);
@@ -1143,7 +1143,7 @@ static void free_anim_ffmpeg(struct anim
 
 	if (anim->pCodecCtx) {
 		avcodec_close(anim->pCodecCtx);
-		av_close_input_file(anim->pFormatCtx);
+		avformat_close_input(&anim->pFormatCtx);
 		av_free(anim->pFrameRGB);
 		av_free(anim->pFrame);
 
