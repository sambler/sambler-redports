--- extern/libmv/third_party/glog/src/demangle.cc.orig	2018-07-02 23:34:08 UTC
+++ extern/libmv/third_party/glog/src/demangle.cc
@@ -167,7 +167,7 @@ static size_t StrLen(const char *str) {
 // Returns true if "str" has at least "n" characters remaining.
 static bool AtLeastNumCharsRemaining(const char *str, int n) {
   for (int i = 0; i < n; ++i) {
-    if (str == '\0') {
+    if (str[i] == '\0') {
       return false;
     }
   }
@@ -223,9 +223,6 @@ static bool ParseTwoCharToken(State *sta
 // Returns true and advances "mangled_cur" if we find any character in
 // "char_class" at "mangled_cur" position.
 static bool ParseCharClass(State *state, const char *char_class) {
-  if (state->mangled_cur == '\0') {
-    return false;
-  }
   const char *p = char_class;
   for (; *p != '\0'; ++p) {
     if (state->mangled_cur[0] == *p) {
