--- ./plugins/midi_import/portsmf/allegrord.cpp.orig	2014-08-16 16:35:46.000000000 +0930
+++ ./plugins/midi_import/portsmf/allegrord.cpp	2014-08-29 05:37:23.603454722 +0930
@@ -109,19 +109,19 @@
     if (attributes) {
         Alg_parameters_ptr a;
         bool in_seconds = seq->get_units_are_seconds();
-        if ((a = Alg_parameters::remove_key(&attributes, "tempor"))) {
+        if ((a = Alg_parameters::remove_key(&attributes, (char *)"tempor"))) {
             double tempo = a->parm.r;
             seq->insert_tempo(tempo, seq->get_time_map()->time_to_beat(time));
         }
-        if ((a = Alg_parameters::remove_key(&attributes, "beatr"))) {
+        if ((a = Alg_parameters::remove_key(&attributes, (char *)"beatr"))) {
             double beat = a->parm.r;
             seq->insert_beat(time, beat);
         }
-        if ((a = Alg_parameters::remove_key(&attributes, "timesig_numr"))) {
+        if ((a = Alg_parameters::remove_key(&attributes, (char *)"timesig_numr"))) {
             tsnum = a->parm.r;
             ts_flag = true;
         }
-        if ((a = Alg_parameters::remove_key(&attributes, "timesig_denr"))) {
+        if ((a = Alg_parameters::remove_key(&attributes, (char *)"timesig_denr"))) {
             tsden = a->parm.r;
             ts_flag = true;
         }
@@ -210,56 +210,56 @@
                 }
                 if (first == 'V') {
                     if (voice_flag) {
-                        parse_error(field, 0, "Voice specified twice");
+                        parse_error(field, 0, (char *)"Voice specified twice");
                     } else {
                         voice = parse_chan(field);
                     }
                     voice_flag = true;
                 } else if (first == 'T') {
                     if (time_flag) {
-                        parse_error(field, 0, "Time specified twice");
+                        parse_error(field, 0, (char *)"Time specified twice");
                     } else {
                         time = parse_dur(field, 0.0);
                     }
                     time_flag = true;
                 } else if (first == 'N') {
                     if (next_flag) {
-                        parse_error(field, 0, "Next specified twice");
+                        parse_error(field, 0, (char *)"Next specified twice");
                     } else {
                         next = parse_dur(field, time);
                     }
                     next_flag = true;
                 } else if (first == 'K') {
                     if (new_key_flag) {
-                        parse_error(field, 0, "Key specified twice");
+                        parse_error(field, 0, (char *)"Key specified twice");
                     } else {
                         new_key = parse_key(field);
                         new_key_flag = true;
                     }
                 } else if (first == 'L') {
                     if (loud_flag) {
-                        parse_error(field, 0, "Loudness specified twice");
+                        parse_error(field, 0, (char *)"Loudness specified twice");
                     } else {
                         loud = parse_loud(field);
                     }
                     loud_flag = true;
                 } else if (first == 'P') {
                     if (new_pitch_flag) {
-                        parse_error(field, 0, "Pitch specified twice");
+                        parse_error(field, 0, (char *)"Pitch specified twice");
                     } else {
                         new_pitch = parse_pitch(field);
                         new_pitch_flag = true;
                     }
                 } else if (first == 'U') {
                     if (dur_flag) {
-                        parse_error(field, 0, "Dur specified twice");
+                        parse_error(field, 0, (char *)"Dur specified twice");
                     } else {
                         dur = parse_dur(field, time);
                         dur_flag = true;
                     }
                 } else if (strchr("SIQHW", first)) {
                     if (dur_flag) {
-                        parse_error(field, 0, "Dur specified twice");
+                        parse_error(field, 0, (char *)"Dur specified twice");
                     } else {
                         // prepend 'U' to field, copy EOS too
                         field.insert(0, 1, 'U');
@@ -268,7 +268,7 @@
                     }
                 } else if (strchr("ABCDEFG", first)) {
                     if (new_pitch_flag) {
-                        parse_error(field, 0, "Pitch specified twice");
+                        parse_error(field, 0, (char *)"Pitch specified twice");
                     } else {
                         // prepend 'P' to field
                         field.insert(0, 1, 'P');
@@ -283,7 +283,7 @@
                         parm.s = NULL; // protect string from deletion by destructor
                     }
                 } else {
-                    parse_error(field, 0, "Unknown field");
+                    parse_error(field, 0, (char *)"Unknown field");
                 }
 
                 if (error_flag) {
@@ -404,7 +404,7 @@
 long Alg_reader::parse_chan(string &field)
 {
     const char *int_string = field.c_str() + 1;
-    const char *msg = "Integer or - expected";
+    const char *msg = (char *)"Integer or - expected";
     const char *p = int_string;
     char c;
     // check that all chars in int_string are digits or '-':
@@ -431,7 +431,7 @@
 long Alg_reader::parse_int(string &field)
 {
     const char *int_string = field.c_str() + 1;
-    const char *msg = "Integer expected";
+    const char *msg = (char *)"Integer expected";
     const char *p = int_string;
     char c;
     // check that all chars in int_string are digits:
@@ -472,7 +472,7 @@
 
 double Alg_reader::parse_real(string &field)
 {
-    const char *msg = "Real expected";
+    const char *msg = (char *)"Real expected";
     int last = find_real_in(field, 1);
     string real_string = field.substr(1, last - 1);
     if (last <= 1 || last < (int) field.length()) {
@@ -501,8 +501,8 @@
 
 double Alg_reader::parse_dur(string &field, double base)
 {
-    const char *msg = "Duration expected";
-    const char *durs = "SIQHW";
+    const char *msg = (char *)"Duration expected";
+    const char *durs = (char *)"SIQHW";
     const char *p;
     int last;
     double dur;
@@ -554,7 +554,7 @@
                 a_string, seq->get_time_map()->beat_to_time(
                         seq->get_time_map()->time_to_beat(base) + dur));
     }
-    parse_error(field, n, "Unexpected character in duration");
+    parse_error(field, n, (char *)"Unexpected character in duration");
     return dur;
 }
 
@@ -568,7 +568,7 @@
 
 double Alg_reader::parse_loud(string &field)
 {
-    const char *msg = "Loudness expected";
+    const char *msg = (char *)"Loudness expected";
     if (isdigit(field[1])) {
         return parse_int(field);
     } else {
@@ -594,8 +594,8 @@
 //
 long Alg_reader::parse_key(string &field)
 {
-    const char *msg = "Pitch expected";
-    const char *pitches = "ABCDEFG";
+    const char *msg = (char *)"Pitch expected";
+    const char *pitches = (char *)"ABCDEFG";
     const char *p;
     if (isdigit(field[1])) {
         // This routine would not have been called if field = "P<number>"
@@ -629,7 +629,7 @@
         int oct = atoi(octave.c_str());
         return parse_after_key(key + oct * 12, field, last);
     }
-    parse_error(field, n, "Unexpected character in pitch");
+    parse_error(field, n, (char *)"Unexpected character in pitch");
     return key;
 }
 
@@ -654,7 +654,7 @@
                 param->set_attr(symbol_table.insert_string(attr.c_str()));
                 parse_val(param, field, i + 1);
             } else {
-                parse_error(field, 0, "attribute needs to end with typecode: i,a,r,s, or l");
+                parse_error(field, 0, (char *)"attribute needs to end with typecode: i,a,r,s, or l");
             }
             return !error_flag;
         }
@@ -706,7 +706,7 @@
             } else if (!period && s[pos] == '.') {
                 period = true;
             } else {
-                parse_error(s, pos, "Unexpected char in number");
+                parse_error(s, pos, (char *)"Unexpected char in number");
                 return false;
             }
             pos = pos + 1;
@@ -727,7 +727,7 @@
             }
         }
     } else {
-        parse_error(s, i, "invalid value");
+        parse_error(s, i, (char *)"invalid value");
         return false;
     }
     return true;
