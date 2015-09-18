--- plugins/MidiImport/portsmf/allegrosmfrd.cpp.orig	2015-03-08 02:47:14 UTC
+++ plugins/MidiImport/portsmf/allegrosmfrd.cpp
@@ -327,7 +327,7 @@ void Alg_midifile_reader::Mf_sysex(int l
 
 void Alg_midifile_reader::Mf_arbitrary(int len, char *msg)
 {
-    Mf_error("arbitrary data ignored");
+    Mf_error((char *)"arbitrary data ignored");
 }
 
 
@@ -341,11 +341,11 @@ void Alg_midifile_reader::Mf_metamisc(in
 
 void Alg_midifile_reader::Mf_seqnum(int n)
 {
-    Mf_error("seqnum data ignored");
+    Mf_error((char *)"seqnum data ignored");
 }
 
 
-static const char *fpsstr[4] = {"24", "25", "29.97", "30"};
+static const char *fpsstr[4] = {(char *)"24", (char *)"25", (char *)"29.97", (char *)"30"};
 
 void Alg_midifile_reader::Mf_smpte(int hours, int mins, int secs,
                                    int frames, int subframes)
