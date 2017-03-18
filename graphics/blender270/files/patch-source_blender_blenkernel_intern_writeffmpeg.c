--- source/blender/blenkernel/intern/writeffmpeg.c.orig	2014-04-12 00:20:37 UTC
+++ source/blender/blenkernel/intern/writeffmpeg.c
@@ -140,8 +140,8 @@ static int write_audio_frame(void) 
 	audio_time += (double) audio_input_samples / (double) c->sample_rate;
 
 #ifdef FFMPEG_HAVE_ENCODE_AUDIO2
-	frame = avcodec_alloc_frame();
-	avcodec_get_frame_defaults(frame);
+	frame = av_frame_alloc();
+	av_frame_unref(frame);
 	frame->pts = audio_time / av_q2d(c->time_base);
 	frame->nb_samples = audio_input_samples;
 	frame->format = c->sample_fmt;
@@ -174,7 +174,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (!got_output) {
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 		return 0;
 	}
 #else
@@ -204,7 +204,7 @@ static int write_audio_frame(void) 
 		if (av_interleaved_write_frame(outfile, &pkt) != 0) {
 			fprintf(stderr, "Error writing audio packet!\n");
 			if (frame)
-				avcodec_free_frame(&frame);
+				av_frame_free(&frame);
 			return -1;
 		}
 
@@ -212,7 +212,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (frame)
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 
 	return 0;
 }
@@ -226,7 +226,7 @@ static AVFrame *alloc_picture(int pix_fm
 	int size;
 	
 	/* allocate space for the struct */
-	f = avcodec_alloc_frame();
+	f = av_frame_alloc();
 	if (!f) return NULL;
 	size = avpicture_get_size(pix_fmt, width, height);
 	/* allocate the actual picture buffer */
@@ -365,8 +365,8 @@ static AVFrame *generate_video_frame(uin
 	int height = c->height;
 	AVFrame *rgb_frame;
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
-		rgb_frame = alloc_picture(PIX_FMT_BGR32, width, height);
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
+		rgb_frame = alloc_picture(AV_PIX_FMT_BGR32, width, height);
 		if (!rgb_frame) {
 			BKE_report(reports, RPT_ERROR, "Could not allocate temporary frame");
 			return NULL;
@@ -416,7 +416,7 @@ static AVFrame *generate_video_frame(uin
 		}
 	}
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
 		sws_scale(img_convert_ctx, (const uint8_t *const *) rgb_frame->data,
 		          rgb_frame->linesize, 0, c->height,
 		          current_frame->data, current_frame->linesize);
@@ -573,12 +573,12 @@ static AVStream *alloc_video_stream(Rend
 	}
 	else {
 		/* makes HuffYUV happy ... */
-		c->pix_fmt = PIX_FMT_YUV422P;
+		c->pix_fmt = AV_PIX_FMT_YUV422P;
 	}
 
 	if (ffmpeg_type == FFMPEG_XVID) {
 		/* arghhhh ... */
-		c->pix_fmt = PIX_FMT_YUV420P;
+		c->pix_fmt = AV_PIX_FMT_YUV420P;
 		c->codec_tag = (('D' << 24) + ('I' << 16) + ('V' << 8) + 'X');
 	}
 
@@ -590,23 +590,23 @@ static AVStream *alloc_video_stream(Rend
 	
 	/* Keep lossless encodes in the RGB domain. */
 	if (codec_id == AV_CODEC_ID_HUFFYUV) {
-		/* HUFFYUV was PIX_FMT_YUV422P before */
-		c->pix_fmt = PIX_FMT_RGB32;
+		/* HUFFYUV was AV_PIX_FMT_YUV422P before */
+		c->pix_fmt = AV_PIX_FMT_RGB32;
 	}
 
 	if (codec_id == AV_CODEC_ID_FFV1) {
-		c->pix_fmt = PIX_FMT_RGB32;
+		c->pix_fmt = AV_PIX_FMT_RGB32;
 	}
 
 	if (codec_id == AV_CODEC_ID_QTRLE) {
 		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
-			c->pix_fmt = PIX_FMT_ARGB;
+			c->pix_fmt = AV_PIX_FMT_ARGB;
 		}
 	}
 
 	if (codec_id == AV_CODEC_ID_PNG) {
 		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
-			c->pix_fmt = PIX_FMT_RGBA;
+			c->pix_fmt = AV_PIX_FMT_RGBA;
 		}
 	}
 
@@ -644,7 +644,7 @@ static AVStream *alloc_video_stream(Rend
 
 	current_frame = alloc_picture(c->pix_fmt, c->width, c->height);
 
-	img_convert_ctx = sws_getContext(c->width, c->height, PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
+	img_convert_ctx = sws_getContext(c->width, c->height, AV_PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
 	                                 NULL, NULL, NULL);
 	return st;
 }
