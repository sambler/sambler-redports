--- source/blender/imbuf/intern/indexer.c.orig	2014-06-26 06:13:52 UTC
+++ source/blender/imbuf/intern/indexer.c
@@ -515,7 +515,7 @@ static struct proxy_output_ctx *alloc_pr
 		rv->c->pix_fmt = rv->codec->pix_fmts[0];
 	}
 	else {
-		rv->c->pix_fmt = PIX_FMT_YUVJ420P;
+		rv->c->pix_fmt = AV_PIX_FMT_YUVJ420P;
 	}
 
 	rv->c->sample_aspect_ratio =
@@ -550,7 +550,7 @@ static struct proxy_output_ctx *alloc_pr
 	if (st->codec->width != width || st->codec->height != height ||
 	    st->codec->pix_fmt != rv->c->pix_fmt)
 	{
-		rv->frame = avcodec_alloc_frame();
+		rv->frame = av_frame_alloc();
 		avpicture_fill((AVPicture *) rv->frame,
 		               MEM_mallocN(avpicture_get_size(
 		                               rv->c->pix_fmt,
@@ -901,7 +901,7 @@ static int index_rebuild_ffmpeg(FFmpegIn
 
 	memset(&next_packet, 0, sizeof(AVPacket));
 
-	in_frame = avcodec_alloc_frame();
+	in_frame = av_frame_alloc();
 
 	stream_size = avio_size(context->iFormatCtx->pb);
 
