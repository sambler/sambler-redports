--- ./plugins/midi_import/portsmf/allegrosmfrd.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./plugins/midi_import/portsmf/allegrosmfrd.cpp	2014-08-29 05:37:23.606455297 +0930
@@ -327,7 +327,7 @@
 
 void Alg_midifile_reader::Mf_arbitrary(int len, char *msg)
 {
-    Mf_error("arbitrary data ignored");
+    Mf_error((char *)"arbitrary data ignored");
 }
 
 
@@ -341,11 +341,11 @@
 
 void Alg_midifile_reader::Mf_seqnum(int n)
 {
-    Mf_error("seqnum data ignored");
+    Mf_error((char *)"seqnum data ignored");
 }
 
 
-static const char *fpsstr[4] = {"24", "25", "29.97", "30"};
+static const char *fpsstr[4] = {(char *)"24", (char *)"25", (char *)"29.97", (char *)"30"};
 
 void Alg_midifile_reader::Mf_smpte(int hours, int mins, int secs,
                                    int frames, int subframes)
