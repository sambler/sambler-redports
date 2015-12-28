--- src/raw.imageio/rawinput.cpp.orig	2015-12-28 13:09:30 UTC
+++ src/raw.imageio/rawinput.cpp
@@ -197,6 +197,7 @@ RawInput::open (const std::string &name,
         if (demosaic == demosaic_algs[d])
             m_processor.imgdata.params.user_qual = d;
         else if (demosaic == "none") {
+#if defined(LIBRAW_DECODER_FLATFIELD)
             // See if we can access the Bayer patterned data for this raw file
             libraw_decoder_info_t decoder_info;
             m_processor.get_decoder_info(&decoder_info);
@@ -204,7 +205,7 @@ RawInput::open (const std::string &name,
                 error("Unable to extract unbayered data from file \"%s\"", name.c_str());
                 return false;
             }
-
+#endif
             // User has selected no demosaicing, so no processing needs to be done
             m_process = false;
 
