--- source/blender/imbuf/intern/indexer.c.orig	2015-07-07 08:54:29 UTC
+++ source/blender/imbuf/intern/indexer.c
@@ -757,7 +757,7 @@ static IndexBuildContext *index_ffmpeg_c
 	}
 
 	if (avformat_find_stream_info(context->iFormatCtx, NULL) < 0) {
-		av_close_input_file(context->iFormatCtx);
+		avformat_close_input(&context->iFormatCtx);
 		MEM_freeN(context);
 		return NULL;
 	}
@@ -777,7 +777,7 @@ static IndexBuildContext *index_ffmpeg_c
 		}
 
 	if (context->videoStream == -1) {
-		av_close_input_file(context->iFormatCtx);
+		avformat_close_input(&context->iFormatCtx);
 		MEM_freeN(context);
 		return NULL;
 	}
@@ -788,7 +788,7 @@ static IndexBuildContext *index_ffmpeg_c
 	context->iCodec = avcodec_find_decoder(context->iCodecCtx->codec_id);
 
 	if (context->iCodec == NULL) {
-		av_close_input_file(context->iFormatCtx);
+		avformat_close_input(&context->iFormatCtx);
 		MEM_freeN(context);
 		return NULL;
 	}
@@ -796,7 +796,7 @@ static IndexBuildContext *index_ffmpeg_c
 	context->iCodecCtx->workaround_bugs = 1;
 
 	if (avcodec_open2(context->iCodecCtx, context->iCodec, NULL) < 0) {
-		av_close_input_file(context->iFormatCtx);
+		avformat_close_input(&context->iFormatCtx);
 		MEM_freeN(context);
 		return NULL;
 	}