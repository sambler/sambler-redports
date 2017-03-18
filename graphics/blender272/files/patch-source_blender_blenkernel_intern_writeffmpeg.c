--- source/blender/blenkernel/intern/writeffmpeg.c.orig	2014-10-20 18:28:22 UTC
+++ source/blender/blenkernel/intern/writeffmpeg.c
@@ -57,7 +57,6 @@
 #include "BKE_sound.h"
 #include "BKE_writeffmpeg.h"
 
-#include "IMB_imbuf_types.h"
 #include "IMB_imbuf.h"
 
 #include "ffmpeg_compat.h"
@@ -134,8 +133,8 @@ static int write_audio_frame(void) 
 	audio_time += (double) audio_input_samples / (double) c->sample_rate;
 
 #ifdef FFMPEG_HAVE_ENCODE_AUDIO2
-	frame = avcodec_alloc_frame();
-	avcodec_get_frame_defaults(frame);
+	frame = av_frame_alloc();
+	av_frame_unref(frame);
 	frame->pts = audio_time / av_q2d(c->time_base);
 	frame->nb_samples = audio_input_samples;
 	frame->format = c->sample_fmt;
@@ -168,7 +167,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (!got_output) {
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 		return 0;
 	}
 #else
@@ -198,7 +197,7 @@ static int write_audio_frame(void) 
 		if (av_interleaved_write_frame(outfile, &pkt) != 0) {
 			fprintf(stderr, "Error writing audio packet!\n");
 			if (frame)
-				avcodec_free_frame(&frame);
+				av_frame_free(&frame);
 			return -1;
 		}
 
@@ -206,7 +205,7 @@ static int write_audio_frame(void) 
 	}
 
 	if (frame)
-		avcodec_free_frame(&frame);
+		av_frame_free(&frame);
 
 	return 0;
 }
@@ -220,7 +219,7 @@ static AVFrame *alloc_picture(int pix_fm
 	int size;
 	
 	/* allocate space for the struct */
-	f = avcodec_alloc_frame();
+	f = av_frame_alloc();
 	if (!f) return NULL;
 	size = avpicture_get_size(pix_fmt, width, height);
 	/* allocate the actual picture buffer */
@@ -359,8 +358,8 @@ static AVFrame *generate_video_frame(uin
 	int height = c->height;
 	AVFrame *rgb_frame;
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
-		rgb_frame = alloc_picture(PIX_FMT_BGR32, width, height);
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
+		rgb_frame = alloc_picture(AV_PIX_FMT_BGR32, width, height);
 		if (!rgb_frame) {
 			BKE_report(reports, RPT_ERROR, "Could not allocate temporary frame");
 			return NULL;
@@ -410,14 +409,14 @@ static AVFrame *generate_video_frame(uin
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
 
@@ -470,8 +469,8 @@ static int ffmpeg_proprty_valid(AVCodecC
 {
 	int valid = 1;
 
-	if (strcmp(prop_name, "video") == 0) {
-		if (strcmp(curr->name, "bf") == 0) {
+	if (STREQ(prop_name, "video")) {
+		if (STREQ(curr->name, "bf")) {
 			/* flash codec doesn't support b frames */
 			valid &= c->codec_id != AV_CODEC_ID_FLV1;
 		}
@@ -484,7 +483,6 @@ static void set_ffmpeg_properties(Render
                                   AVDictionary **dictionary)
 {
 	IDProperty *prop;
-	void *iter;
 	IDProperty *curr;
 
 	/* TODO(sergey): This is actually rather stupid, because changing
@@ -495,7 +493,7 @@ static void set_ffmpeg_properties(Render
 	 *
 	 * For as long we don't allow editing properties in the interface
 	 * it's all good. bug if we allow editing them, we'll need to
-	 * repace it with some smarter code which would port settings
+	 * replace it with some smarter code which would port settings
 	 * from deprecated to new one.
 	 */
 	ffmpeg_set_expert_options(rd);
@@ -509,9 +507,7 @@ static void set_ffmpeg_properties(Render
 		return;
 	}
 
-	iter = IDP_GetGroupIterator(prop);
-
-	while ((curr = IDP_GroupIterNext(iter)) != NULL) {
+	for (curr = prop->data.group.first; curr; curr = curr->next) {
 		if (ffmpeg_proprty_valid(c, prop_name, curr))
 			set_ffmpeg_property_option(c, curr, dictionary);
 	}
@@ -585,12 +581,12 @@ static AVStream *alloc_video_stream(Rend
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
 
@@ -602,31 +598,35 @@ static AVStream *alloc_video_stream(Rend
 	
 	/* Keep lossless encodes in the RGB domain. */
 	if (codec_id == AV_CODEC_ID_HUFFYUV) {
-		/* HUFFYUV was PIX_FMT_YUV422P before */
-		c->pix_fmt = PIX_FMT_RGB32;
+		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
+			c->pix_fmt = AV_PIX_FMT_BGRA;
+		}
+		else {
+			c->pix_fmt = AV_PIX_FMT_RGB32;
+		}
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
 
 	if ((of->oformat->flags & AVFMT_GLOBALHEADER)
 #if 0
-	    || !strcmp(of->oformat->name, "mp4")
-	    || !strcmp(of->oformat->name, "mov")
-	    || !strcmp(of->oformat->name, "3gp")
+	    || STREQ(of->oformat->name, "mp4")
+	    || STREQ(of->oformat->name, "mov")
+	    || STREQ(of->oformat->name, "3gp")
 #endif
 	    )
 	{
@@ -656,7 +656,7 @@ static AVStream *alloc_video_stream(Rend
 
 	current_frame = alloc_picture(c->pix_fmt, c->width, c->height);
 
-	img_convert_ctx = sws_getContext(c->width, c->height, PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
+	img_convert_ctx = sws_getContext(c->width, c->height, AV_PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
 	                                 NULL, NULL, NULL);
 	return st;
 }
@@ -696,7 +696,7 @@ static AVStream *alloc_audio_stream(Rend
 	}
 
 	if (codec->sample_fmts) {
-		/* check if the prefered sample format for this codec is supported.
+		/* check if the preferred sample format for this codec is supported.
 		 * this is because, depending on the version of libav, and with the whole ffmpeg/libav fork situation,
 		 * you have various implementations around. float samples in particular are not always supported.
 		 */
@@ -1632,6 +1632,12 @@ bool BKE_ffmpeg_alpha_channel_is_support
 	if (codec == AV_CODEC_ID_PNG)
 		return true;
 
+	if (codec == AV_CODEC_ID_PNG)
+		return true;
+
+	if (codec == AV_CODEC_ID_HUFFYUV)
+		return true;
+
 #ifdef FFMPEG_FFV1_ALPHA_SUPPORTED
 	if (codec == AV_CODEC_ID_FFV1)
 		return true;
