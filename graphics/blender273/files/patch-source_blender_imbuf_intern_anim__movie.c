--- source/blender/imbuf/intern/anim_movie.c.orig	2015-01-13 16:28:28 UTC
+++ source/blender/imbuf/intern/anim_movie.c
@@ -560,12 +560,12 @@ static int startffmpeg(struct anim *anim
 	anim->next_pts = -1;
 	anim->next_packet.stream_index = -1;
 
-	anim->pFrame = avcodec_alloc_frame();
+	anim->pFrame = av_frame_alloc();
 	anim->pFrameComplete = false;
-	anim->pFrameDeinterlaced = avcodec_alloc_frame();
-	anim->pFrameRGB = avcodec_alloc_frame();
+	anim->pFrameDeinterlaced = av_frame_alloc();
+	anim->pFrameRGB = av_frame_alloc();
 
-	if (avpicture_get_size(PIX_FMT_RGBA, anim->x, anim->y) !=
+	if (avpicture_get_size(AV_PIX_FMT_RGBA, anim->x, anim->y) !=
 	    anim->x * anim->y * 4)
 	{
 		fprintf(stderr,
@@ -604,7 +604,7 @@ static int startffmpeg(struct anim *anim
 	        anim->pCodecCtx->pix_fmt,
 	        anim->x,
 	        anim->y,
-	        PIX_FMT_RGBA,
+	        AV_PIX_FMT_RGBA,
 	        SWS_FAST_BILINEAR | SWS_PRINT_INFO | SWS_FULL_CHR_H_INT,
 	        NULL, NULL, NULL);
 		
@@ -675,25 +675,12 @@ static void ffmpeg_postprocess(struct an
 
 
 	if (anim->ib_flags & IB_animdeinterlace) {
-		if (avpicture_deinterlace(
-		        (AVPicture *)
-		        anim->pFrameDeinterlaced,
-		        (const AVPicture *)
-		        anim->pFrame,
-		        anim->pCodecCtx->pix_fmt,
-		        anim->pCodecCtx->width,
-		        anim->pCodecCtx->height) < 0)
-		{
-			filter_y = true;
-		}
-		else {
-			input = anim->pFrameDeinterlaced;
-		}
+		input = anim->pFrameDeinterlaced;
 	}
 	
 	avpicture_fill((AVPicture *) anim->pFrameRGB,
 	               (unsigned char *) ibuf->rect,
-	               PIX_FMT_RGBA, anim->x, anim->y);
+	               AV_PIX_FMT_RGBA, anim->x, anim->y);
 
 	if (ENDIAN_ORDER == B_ENDIAN) {
 		int *dstStride   = anim->pFrameRGB->linesize;
