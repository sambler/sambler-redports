--- ./liboslexec/automata.cpp.orig	2012-08-31 06:58:32.000000000 +0930
+++ ./liboslexec/automata.cpp	2012-10-27 15:54:13.710663429 +1030
@@ -263,7 +263,7 @@
     std::string s;
     for (size_t i = 0; i < m_states.size(); ++i) {
         char temp[32];
-        snprintf(temp, 32, "%ld : ", i);
+        snprintf(temp, 32, "%zd : ", i);
         s += temp + m_states[i]->tostr() + "\n";
     }
     return s;
@@ -411,7 +411,7 @@
     std::string s;
     for (size_t i = 0; i < m_states.size(); ++i) {
         char temp[32];
-        snprintf(temp, 32, "%ld : ", i);
+        snprintf(temp, 32, "%zd : ", i);
         s += temp + m_states[i]->tostr() + "\n";
     }
     return s;
