--- source/blender/blenkernel/intern/writeffmpeg.c.orig	2017-01-13 13:17:37 UTC
+++ source/blender/blenkernel/intern/writeffmpeg.c
@@ -70,8 +70,8 @@
 #include "ffmpeg_compat.h"
 
 static int ffmpeg_type = 0;
-static int ffmpeg_codec = CODEC_ID_MPEG4;
-static int ffmpeg_audio_codec = CODEC_ID_NONE;
+static int ffmpeg_codec = AV_CODEC_ID_MPEG4;
+static int ffmpeg_audio_codec = AV_CODEC_ID_NONE;
 static int ffmpeg_video_bitrate = 1150;
 static int ffmpeg_audio_bitrate = 128;
 static int ffmpeg_gop_size = 12;
@@ -106,6 +106,11 @@ static AUD_Device *audio_mixdown_device 
 
 #define PRINT if (G.debug & G_DEBUG_FFMPEG) printf
 
+#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
+#define av_frame_alloc  avcodec_alloc_frame
+#define av_frame_free avcodec_free_frame
+#endif
+
 /* Delete a picture buffer */
 
 static void delete_picture(AVFrame *f)
@@ -119,7 +124,7 @@ static void delete_picture(AVFrame *f)
 static int request_float_audio_buffer(int codec_id)
 {
 	/* If any of these codecs, we prefer the float sample format (if supported) */
-	return codec_id == CODEC_ID_AAC || codec_id == CODEC_ID_AC3 || codec_id == CODEC_ID_VORBIS;
+	return codec_id == AV_CODEC_ID_AAC || codec_id == AV_CODEC_ID_AC3 || codec_id == AV_CODEC_ID_VORBIS;
 }
 
 #ifdef WITH_AUDASPACE
@@ -326,7 +331,7 @@ static int write_video_frame(RenderData 
 		frame->top_field_first = ((rd->mode & R_ODDFIELD) != 0);
 	}
 
-	outsize = avcodec_encode_video(c, video_buffer, video_buffersize,  frame);
+	outsize = avcodec_encode_video2(c, video_buffer, video_buffersize,  frame);
 
 	if (outsize > 0) {
 		AVPacket packet;
@@ -367,8 +372,8 @@ static AVFrame *generate_video_frame(uin
 	int height = c->height;
 	AVFrame *rgb_frame;
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
-		rgb_frame = alloc_picture(PIX_FMT_BGR32, width, height);
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
+		rgb_frame = alloc_picture(AV_PIX_FMT_BGR32, width, height);
 		if (!rgb_frame) {
 			BKE_report(reports, RPT_ERROR, "Could not allocate temporary frame");
 			return NULL;
@@ -418,7 +423,7 @@ static AVFrame *generate_video_frame(uin
 		}
 	}
 
-	if (c->pix_fmt != PIX_FMT_BGR32) {
+	if (c->pix_fmt != AV_PIX_FMT_BGR32) {
 		sws_scale(img_convert_ctx, (const uint8_t *const *) rgb_frame->data,
 		          rgb_frame->linesize, 0, c->height,
 		          current_frame->data, current_frame->linesize);
@@ -481,7 +486,7 @@ static int ffmpeg_proprty_valid(AVCodecC
 	if (strcmp(prop_name, "video") == 0) {
 		if (strcmp(curr->name, "bf") == 0) {
 			/* flash codec doesn't support b frames */
-			valid &= c->codec_id != CODEC_ID_FLV1;
+			valid &= c->codec_id != AV_CODEC_ID_FLV1;
 		}
 	}
 
@@ -578,40 +583,40 @@ static AVStream *alloc_video_stream(Rend
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
 
-	if (codec_id == CODEC_ID_H264) {
+	if (codec_id == AV_CODEC_ID_H264) {
 		/* correct wrong default ffmpeg param which crash x264 */
 		c->qmin = 10;
 		c->qmax = 51;
 	}
 	
 	/* Keep lossless encodes in the RGB domain. */
-	if (codec_id == CODEC_ID_HUFFYUV) {
+	if (codec_id == AV_CODEC_ID_HUFFYUV) {
 		/* HUFFYUV was PIX_FMT_YUV422P before */
-		c->pix_fmt = PIX_FMT_RGB32;
+		c->pix_fmt = AV_PIX_FMT_RGB32;
 	}
 
-	if (codec_id == CODEC_ID_FFV1) {
-		c->pix_fmt = PIX_FMT_RGB32;
+	if (codec_id == AV_CODEC_ID_FFV1) {
+		c->pix_fmt = AV_PIX_FMT_RGB32;
 	}
 
-	if (codec_id == CODEC_ID_QTRLE) {
+	if (codec_id == AV_CODEC_ID_QTRLE) {
 		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
-			c->pix_fmt = PIX_FMT_ARGB;
+			c->pix_fmt = AV_PIX_FMT_ARGB;
 		}
 	}
 
-	if (codec_id == CODEC_ID_PNG) {
+	if (codec_id == AV_CODEC_ID_PNG) {
 		if (rd->im_format.planes == R_IMF_PLANES_RGBA) {
-			c->pix_fmt = PIX_FMT_ARGB;
+			c->pix_fmt = AV_PIX_FMT_ARGB;
 		}
 	}
 
@@ -643,7 +648,7 @@ static AVStream *alloc_video_stream(Rend
 		return NULL;
 	}
 
-	if (codec_id == CODEC_ID_QTRLE) {
+	if (codec_id == AV_CODEC_ID_QTRLE) {
 		/* normally it should be enough to have buffer with actual image size,
 		 * but some codecs like QTRLE might store extra information in this buffer,
 		 * so it should be a way larger */
@@ -660,7 +665,7 @@ static AVStream *alloc_video_stream(Rend
 	
 	current_frame = alloc_picture(c->pix_fmt, c->width, c->height);
 
-	img_convert_ctx = sws_getContext(c->width, c->height, PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
+	img_convert_ctx = sws_getContext(c->width, c->height, AV_PIX_FMT_BGR32, c->width, c->height, c->pix_fmt, SWS_BICUBIC,
 	                                 NULL, NULL, NULL);
 	return st;
 }
@@ -833,7 +838,7 @@ static int start_ffmpeg_impl(struct Rend
 	
 	of->oformat = fmt;
 	of->packet_size = rd->ffcodecdata.mux_packet_size;
-	if (ffmpeg_audio_codec != CODEC_ID_NONE) {
+	if (ffmpeg_audio_codec != AV_CODEC_ID_NONE) {
 		ffmpeg_dict_set_int(&opts, "muxrate", rd->ffcodecdata.mux_rate);
 	}
 	else {
@@ -855,37 +860,37 @@ static int start_ffmpeg_impl(struct Rend
 			fmt->video_codec = ffmpeg_codec;
 			break;
 		case FFMPEG_OGG:
-			fmt->video_codec = CODEC_ID_THEORA;
+			fmt->video_codec = AV_CODEC_ID_THEORA;
 			break;
 		case FFMPEG_DV:
-			fmt->video_codec = CODEC_ID_DVVIDEO;
+			fmt->video_codec = AV_CODEC_ID_DVVIDEO;
 			break;
 		case FFMPEG_MPEG1:
-			fmt->video_codec = CODEC_ID_MPEG1VIDEO;
+			fmt->video_codec = AV_CODEC_ID_MPEG1VIDEO;
 			break;
 		case FFMPEG_MPEG2:
-			fmt->video_codec = CODEC_ID_MPEG2VIDEO;
+			fmt->video_codec = AV_CODEC_ID_MPEG2VIDEO;
 			break;
 		case FFMPEG_H264:
-			fmt->video_codec = CODEC_ID_H264;
+			fmt->video_codec = AV_CODEC_ID_H264;
 			break;
 		case FFMPEG_XVID:
-			fmt->video_codec = CODEC_ID_MPEG4;
+			fmt->video_codec = AV_CODEC_ID_MPEG4;
 			break;
 		case FFMPEG_FLV:
-			fmt->video_codec = CODEC_ID_FLV1;
+			fmt->video_codec = AV_CODEC_ID_FLV1;
 			break;
 		case FFMPEG_MP3:
-			fmt->audio_codec = CODEC_ID_MP3;
+			fmt->audio_codec = AV_CODEC_ID_MP3;
 		case FFMPEG_WAV:
-			fmt->video_codec = CODEC_ID_NONE;
+			fmt->video_codec = AV_CODEC_ID_NONE;
 			break;
 		case FFMPEG_MPEG4:
 		default:
-			fmt->video_codec = CODEC_ID_MPEG4;
+			fmt->video_codec = AV_CODEC_ID_MPEG4;
 			break;
 	}
-	if (fmt->video_codec == CODEC_ID_DVVIDEO) {
+	if (fmt->video_codec == AV_CODEC_ID_DVVIDEO) {
 		if (rectx != 720) {
 			BKE_report(reports, RPT_ERROR, "Render width has to be 720 pixels for DV!");
 			return 0;
@@ -901,15 +906,15 @@ static int start_ffmpeg_impl(struct Rend
 	}
 	
 	if (ffmpeg_type == FFMPEG_DV) {
-		fmt->audio_codec = CODEC_ID_PCM_S16LE;
-		if (ffmpeg_audio_codec != CODEC_ID_NONE && rd->ffcodecdata.audio_mixrate != 48000 && rd->ffcodecdata.audio_channels != 2) {
+		fmt->audio_codec = AV_CODEC_ID_PCM_S16LE;
+		if (ffmpeg_audio_codec != AV_CODEC_ID_NONE && rd->ffcodecdata.audio_mixrate != 48000 && rd->ffcodecdata.audio_channels != 2) {
 			BKE_report(reports, RPT_ERROR, "FFMPEG only supports 48khz / stereo audio for DV!");
 			av_dict_free(&opts);
 			return 0;
 		}
 	}
 	
-	if (fmt->video_codec != CODEC_ID_NONE) {
+	if (fmt->video_codec != AV_CODEC_ID_NONE) {
 		video_stream = alloc_video_stream(rd, fmt->video_codec, of, rectx, recty, error, sizeof(error));
 		PRINT("alloc video stream %p\n", video_stream);
 		if (!video_stream) {
@@ -923,7 +928,7 @@ static int start_ffmpeg_impl(struct Rend
 		}
 	}
 
-	if (ffmpeg_audio_codec != CODEC_ID_NONE) {
+	if (ffmpeg_audio_codec != AV_CODEC_ID_NONE) {
 		audio_stream = alloc_audio_stream(rd, fmt->audio_codec, of, error, sizeof(error));
 		if (!audio_stream) {
 			if (error[0])
@@ -968,7 +973,7 @@ static int start_ffmpeg_impl(struct Rend
  * and then the bidirectionally-predicted frames. What this means in practice 
  * is that the encoder may not immediately produce one output frame for each 
  * input frame. These delayed frames must be flushed before we close the 
- * stream. We do this by calling avcodec_encode_video with NULL for the last 
+ * stream. We do this by calling avcodec_encode_video2 with NULL for the last 
  * parameter.
  * </p>
  */
@@ -983,7 +988,7 @@ static void flush_ffmpeg(void)
 		AVPacket packet;
 		av_init_packet(&packet);
 		
-		outsize = avcodec_encode_video(c, video_buffer, video_buffersize, NULL);
+		outsize = avcodec_encode_video2(c, video_buffer, video_buffersize, NULL);
 		if (outsize < 0) {
 			fprintf(stderr, "Error encoding delayed frame %d\n", outsize);
 			break;
@@ -1421,7 +1426,7 @@ static void ffmpeg_set_expert_options(Re
 	if (rd->ffcodecdata.properties)
 		IDP_FreeProperty(rd->ffcodecdata.properties);
 
-	if (codec_id == CODEC_ID_H264) {
+	if (codec_id == AV_CODEC_ID_H264) {
 		/*
 		 * All options here are for x264, but must be set via ffmpeg.
 		 * The names are therefore different - Search for "x264 to FFmpeg option mapping"
@@ -1464,7 +1469,7 @@ static void ffmpeg_set_expert_options(Re
 		if (rd->ffcodecdata.flags & FFMPEG_LOSSLESS_OUTPUT)
 			BKE_ffmpeg_property_add_string(rd, "video", "cqp:0");
 	}
-	else if (codec_id == CODEC_ID_DNXHD) {
+	else if (codec_id == AV_CODEC_ID_DNXHD) {
 		if (rd->ffcodecdata.flags & FFMPEG_LOSSLESS_OUTPUT)
 			BKE_ffmpeg_property_add_string(rd, "video", "mbd:rd");
 	}
@@ -1528,7 +1533,7 @@ void BKE_ffmpeg_preset_set(RenderData *r
 
 		case FFMPEG_PRESET_H264:
 			rd->ffcodecdata.type = FFMPEG_AVI;
-			rd->ffcodecdata.codec = CODEC_ID_H264;
+			rd->ffcodecdata.codec = AV_CODEC_ID_H264;
 			rd->ffcodecdata.video_bitrate = 6000;
 			rd->ffcodecdata.gop_size = isntsc ? 18 : 15;
 			rd->ffcodecdata.rc_max_rate = 9000;
@@ -1543,11 +1548,11 @@ void BKE_ffmpeg_preset_set(RenderData *r
 		case FFMPEG_PRESET_XVID:
 			if (preset == FFMPEG_PRESET_XVID) {
 				rd->ffcodecdata.type = FFMPEG_AVI;
-				rd->ffcodecdata.codec = CODEC_ID_MPEG4;
+				rd->ffcodecdata.codec = AV_CODEC_ID_MPEG4;
 			}
 			else if (preset == FFMPEG_PRESET_THEORA) {
 				rd->ffcodecdata.type = FFMPEG_OGG; // XXX broken
-				rd->ffcodecdata.codec = CODEC_ID_THEORA;
+				rd->ffcodecdata.codec = AV_CODEC_ID_THEORA;
 			}
 
 			rd->ffcodecdata.video_bitrate = 6000;
@@ -1574,7 +1579,7 @@ void BKE_ffmpeg_image_type_verify(Render
 		    rd->ffcodecdata.audio_codec <= 0 ||
 		    rd->ffcodecdata.video_bitrate <= 1)
 		{
-			rd->ffcodecdata.codec = CODEC_ID_MPEG2VIDEO;
+			rd->ffcodecdata.codec = AV_CODEC_ID_MPEG2VIDEO;
 
 			BKE_ffmpeg_preset_set(rd, FFMPEG_PRESET_DVD);
 		}
@@ -1585,26 +1590,26 @@ void BKE_ffmpeg_image_type_verify(Render
 		audio = 1;
 	}
 	else if (imf->imtype == R_IMF_IMTYPE_H264) {
-		if (rd->ffcodecdata.codec != CODEC_ID_H264) {
+		if (rd->ffcodecdata.codec != AV_CODEC_ID_H264) {
 			BKE_ffmpeg_preset_set(rd, FFMPEG_PRESET_H264);
 			audio = 1;
 		}
 	}
 	else if (imf->imtype == R_IMF_IMTYPE_XVID) {
-		if (rd->ffcodecdata.codec != CODEC_ID_MPEG4) {
+		if (rd->ffcodecdata.codec != AV_CODEC_ID_MPEG4) {
 			BKE_ffmpeg_preset_set(rd, FFMPEG_PRESET_XVID);
 			audio = 1;
 		}
 	}
 	else if (imf->imtype == R_IMF_IMTYPE_THEORA) {
-		if (rd->ffcodecdata.codec != CODEC_ID_THEORA) {
+		if (rd->ffcodecdata.codec != AV_CODEC_ID_THEORA) {
 			BKE_ffmpeg_preset_set(rd, FFMPEG_PRESET_THEORA);
 			audio = 1;
 		}
 	}
 
 	if (audio && rd->ffcodecdata.audio_codec < 0) {
-		rd->ffcodecdata.audio_codec = CODEC_ID_NONE;
+		rd->ffcodecdata.audio_codec = AV_CODEC_ID_NONE;
 		rd->ffcodecdata.audio_bitrate = 128;
 	}
 }
@@ -1618,14 +1623,14 @@ int BKE_ffmpeg_alpha_channel_is_supporte
 {
 	int codec = rd->ffcodecdata.codec;
 
-	if (codec == CODEC_ID_QTRLE)
+	if (codec == AV_CODEC_ID_QTRLE)
 		return TRUE;
 
-	if (codec == CODEC_ID_PNG)
+	if (codec == AV_CODEC_ID_PNG)
 		return TRUE;
 
 #ifdef FFMPEG_FFV1_ALPHA_SUPPORTED
-	if (codec == CODEC_ID_FFV1)
+	if (codec == AV_CODEC_ID_FFV1)
 		return TRUE;
 #endif
 
