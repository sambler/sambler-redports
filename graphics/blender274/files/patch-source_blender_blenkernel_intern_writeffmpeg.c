--- source/blender/blenkernel/intern/writeffmpeg.c.orig	2015-04-01 13:14:23 UTC
+++ source/blender/blenkernel/intern/writeffmpeg.c
@@ -133,8 +133,8 @@ static int write_audio_frame(void) 
 	audio_time += (double) audio_input_samples / (double) c->sample_rate;
 
 #ifdef FFMPEG_HAVE_ENCODE_AUDIO2
-	frame = avcodec_alloc_frame();
-	avcodec_get_frame_defaults(frame);
+	frame = av_frame_alloc();
+	av_frame_unref(frame);
 	frame->pts = audio_time / av_q2d(c->time_base);
 	frame->nb_samples = audio_input_samples;
 	frame->format = c->sample_fmt;
@@ -167,7 +167,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (!got_output) {
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 		return 0;
 	}
 #else
@@ -197,7 +197,7 @@ static int write_audio_frame(void) 
 		if (av_interleaved_write_frame(outfile, &pkt) != 0) {
 			fprintf(stderr, "Error writing audio packet!\n");
 			if (frame)
-				avcodec_free_frame(&frame);
+				av_frame_free(&frame);
 			return -1;
 		}
 
@@ -205,7 +205,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (frame)
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 
 	return 0;
 }
@@ -219,7 +219,7 @@ static AVFrame *alloc_picture(int pix_fm
 	int size;
 	
 	/* allocate space for the struct */
-	f = avcodec_alloc_frame();
+	f = av_frame_alloc();
 	if (!f) return NULL;
 	size = avpicture_get_size(pix_fmt, width, height);
 	/* allocate the actual picture buffer */
@@ -358,8 +358,8 @@ static AVFrame *generate_video_frame(uin
 	int height = c->height;
 	AVFrame *rgb_frame;
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
-		rgb_frame = alloc_picture(PIX_FMT_BGR32, width, height);
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
+		rgb_frame = alloc_picture(AV_PIX_FMT_BGR32, width, height);
 		if (!rgb_frame) {
 			BKE_report(reports, RPT_ERROR, "Could not allocate temporary frame");
 			return NULL;
@@ -409,14 +409,14 @@ static AVFrame *generate_video_frame(uin
 		}
 	}
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
 		sws_scale(img_convert_ctx, (const uint8_t *const *) rgb_frame->data,
 		          rgb_frame->linesize, 0, c->height,
 		          current_frame->data, current_frame->linesize);
 		delete_picture(rgb_frame);
 	}
 
-	current_frame->format = PIX_FMT_BGR32;
+	current_frame->format = AV_PIX_FMT_BGR32;
 	current_frame->width = width;
 	current_frame->height = height;
 
@@ -581,12 +581,12 @@ static AVStream *alloc_video_stream(Rend
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
 
@@ -599,26 +599,26 @@ static AVStream *alloc_video_stream(Rend
 	/* Keep lossless encodes in the RGB domain. */
 	if (codec_id == AV_CODEC_ID_HUFFYUV) {
 		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
-			c->pix_fmt = PIX_FMT_BGRA;
+			c->pix_fmt = AV_PIX_FMT_BGRA;
 		}
 		else {
-			c->pix_fmt = PIX_FMT_RGB32;
+			c->pix_fmt = AV_PIX_FMT_RGB32;
 		}
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
 
@@ -656,7 +656,7 @@ static AVStream *alloc_video_stream(Rend
 
 	current_frame = alloc_picture(c->pix_fmt, c->width, c->height);
 
-	img_convert_ctx = sws_getContext(c->width, c->height, PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
+	img_convert_ctx = sws_getContext(c->width, c->height, AV_PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
 	                                 NULL, NULL, NULL);
 	return st;
 }
