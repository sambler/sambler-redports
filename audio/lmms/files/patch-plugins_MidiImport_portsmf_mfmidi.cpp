--- plugins/MidiImport/portsmf/mfmidi.cpp.orig	2015-06-11 08:38:27 UTC
+++ plugins/MidiImport/portsmf/mfmidi.cpp
@@ -28,7 +28,7 @@ void Midifile_reader::midifile()
     ntrks = readheader();
     if (midifile_error) return;
     if (ntrks <= 0) {
-        mferror("No tracks!");
+        mferror((char *)"No tracks!");
         /* no need to return since midifile_error is set */
     }
     while (ntrks-- > 0 && !midifile_error) readtrack();
@@ -42,13 +42,13 @@ int Midifile_reader::readmt(const char *
     char b[4];
     char buff[32];
     int c;
-    const char *errmsg = "expecting ";
+    const char *errmsg = (char *)"expecting ";
 
     retry:
     while ( nread<4 ) {
         c = Mf_getc();
         if ( c == EOF ) {
-            errmsg = "EOF while expecting ";
+            errmsg = (char *)"EOF while expecting ";
             goto err;
         }
         b[nread++] = c;
@@ -78,7 +78,7 @@ int Midifile_reader::egetc()
     int c = Mf_getc();
 
     if ( c == EOF ) {
-        mferror("premature EOF");
+        mferror((char *)"premature EOF");
         return EOF;
     }
     Mf_toberead--;
@@ -90,7 +90,7 @@ int Midifile_reader::readheader()
 {
     int format, ntrks, division;
 
-    if ( readmt("MThd",Mf_skipinit) == EOF )
+    if ( readmt((char *)"MThd",Mf_skipinit) == EOF )
         return(0);
 
     Mf_toberead = read32bit();
@@ -127,7 +127,7 @@ void Midifile_reader::readtrack()
     int status = 0;         /* (possibly running) status byte */
     int needed;
 
-    if ( readmt("MTrk",0) == EOF )
+    if ( readmt((char *)"MTrk",0) == EOF )
         return;
 
     Mf_toberead = read32bit();
@@ -147,12 +147,12 @@ void Midifile_reader::readtrack()
        if (midifile_error) return;
 
         if ( sysexcontinue && c != 0xf7 ) {
-            mferror("didn't find expected continuation of a sysex");
+            mferror((char *)"didn't find expected continuation of a sysex");
             return;
         }
         if ( (c & 0x80) == 0 ) {        /* running status? */
             if ( status == 0 ) {
-                mferror("unexpected running status");
+                mferror((char *)"unexpected running status");
                 return;
             }
             running = 1;
