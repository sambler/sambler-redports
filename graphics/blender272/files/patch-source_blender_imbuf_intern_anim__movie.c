--- source/blender/imbuf/intern/anim_movie.c.orig	2014-10-20 18:28:23 UTC
+++ source/blender/imbuf/intern/anim_movie.c
@@ -70,12 +70,8 @@
 
 #include "MEM_guardedalloc.h"
 
-#include "DNA_userdef_types.h"
-
 #include "BKE_global.h"
 
-#include "imbuf.h"
-
 #ifdef WITH_AVI
 #  include "AVI_avi.h"
 #endif
@@ -89,7 +85,6 @@
 #include "IMB_imbuf_types.h"
 #include "IMB_imbuf.h"
 
-#include "IMB_allocimbuf.h"
 #include "IMB_anim.h"
 #include "IMB_indexer.h"
 
@@ -565,12 +560,12 @@ static int startffmpeg(struct anim *anim
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
@@ -609,7 +604,7 @@ static int startffmpeg(struct anim *anim
 	        anim->pCodecCtx->pix_fmt,
 	        anim->x,
 	        anim->y,
-	        PIX_FMT_RGBA,
+	        AV_PIX_FMT_RGBA,
 	        SWS_FAST_BILINEAR | SWS_PRINT_INFO | SWS_FULL_CHR_H_INT,
 	        NULL, NULL, NULL);
 		
@@ -680,25 +675,12 @@ static void ffmpeg_postprocess(struct an
 
 
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
@@ -1319,25 +1301,27 @@ struct ImBuf *IMB_anim_absolute(struct a
 
 	filter_y = (anim->ib_flags & IB_animdeinterlace);
 
-	if (anim->curtype == 0) {
-		ibuf = anim_getnew(anim);
-		if (ibuf == NULL) {
-			return(NULL);
+	if (preview_size == IMB_PROXY_NONE) {
+		if (anim->curtype == 0) {
+			ibuf = anim_getnew(anim);
+			if (ibuf == NULL) {
+				return(NULL);
+			}
+
+			IMB_freeImBuf(ibuf); /* ???? */
+			ibuf = NULL;
 		}
 
-		IMB_freeImBuf(ibuf); /* ???? */
-		ibuf = NULL;
+		if (position < 0) return(NULL);
+		if (position >= anim->duration) return(NULL);
 	}
-
-	if (position < 0) return(NULL);
-	if (position >= anim->duration) return(NULL);
-
-	if (preview_size != IMB_PROXY_NONE) {
+	else {
 		struct anim *proxy = IMB_anim_open_proxy(anim, preview_size);
 
 		if (proxy) {
 			position = IMB_anim_index_get_frame_index(
 			    anim, tc, position);
+
 			return IMB_anim_absolute(
 			           proxy, position,
 			           IMB_TC_NONE, IMB_PROXY_NONE);
