--- intern/ffmpeg/ffmpeg_compat.h.orig	2013-01-14 04:24:09.000000000 +1030
+++ intern/ffmpeg/ffmpeg_compat.h	2013-02-22 22:04:00.461610551 +1030
@@ -113,7 +113,7 @@
 #define avformat_close_input(x) av_close_input_file(*(x))
 #endif
 
-#if ((LIBAVCODEC_VERSION_MAJOR < 53) || (LIBAVCODEC_VERSION_MAJOR == 53 && LIBAVCODEC_VERSION_MINOR < 35))
+#if ((LIBAVCODEC_VERSION_MAJOR < 52) || (LIBAVCODEC_VERSION_MAJOR == 53 && LIBAVCODEC_VERSION_MINOR < 42) || (LIBAVCODEC_VERSION_MAJOR == 52 && LIBAVCODEC_VERSION_MINOR < 123))
 static inline
 int avcodec_open2(AVCodecContext *avctx, AVCodec *codec, AVDictionary **options)
 {
@@ -122,14 +122,16 @@
 }
 #endif
 
-#if ((LIBAVFORMAT_VERSION_MAJOR < 53) || (LIBAVFORMAT_VERSION_MAJOR == 53 && LIBAVFORMAT_VERSION_MINOR < 21))
+#if ((LIBAVFORMAT_VERSION_MAJOR < 52) || (LIBAVFORMAT_VERSION_MAJOR == 53 && LIBAVFORMAT_VERSION_MINOR < 24) || (LIBAVFORMAT_VERSION_MAJOR == 52 && LIBAVFORMAT_VERSION_MINOR < 112))
 static inline
 AVStream *avformat_new_stream(AVFormatContext *s, AVCodec *c)
 {
 	/* TODO: no codec is taking into account */
 	return av_new_stream(s, 0);
 }
+#endif
 
+#if ((LIBAVFORMAT_VERSION_MAJOR > 53) || ((LIBAVFORMAT_VERSION_MAJOR == 53) && (LIBAVFORMAT_VERSION_MINOR > 32)) || ((LIBAVFORMAT_VERSION_MAJOR == 53) && (LIBAVFORMAT_VERSION_MINOR == 24) && (LIBAVFORMAT_VERSION_MICRO >= 100)))
 static inline
 int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options)
 {
