--- src/ffmpeg.imageio/ffmpeginput.cpp.orig	2017-09-03 13:28:17 UTC
+++ src/ffmpeg.imageio/ffmpeginput.cpp
@@ -237,7 +237,7 @@ FFmpegInput::open (const std::string &na
     m_frame = av_frame_alloc();
     m_rgb_frame = av_frame_alloc();
     m_rgb_buffer.resize(
-        avpicture_get_size (PIX_FMT_RGB24,
+        avpicture_get_size (AV_PIX_FMT_RGB24,
         m_codec_context->width,
         m_codec_context->height),
         0
@@ -265,7 +265,7 @@ FFmpegInput::open (const std::string &na
         pixFormat,
         m_codec_context->width,
         m_codec_context->height,
-        PIX_FMT_RGB24,
+        AV_PIX_FMT_RGB24,
         SWS_AREA,
         NULL,
         NULL,
@@ -362,7 +362,7 @@ FFmpegInput::read_frame(int pos)
                 (
                     reinterpret_cast<AVPicture*>(m_rgb_frame),
                     &m_rgb_buffer[0],
-                    PIX_FMT_RGB24,
+                    AV_PIX_FMT_RGB24,
                     m_codec_context->width,
                     m_codec_context->height
                 );
