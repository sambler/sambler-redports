--- core/ustring.cpp.orig	2018-01-10 13:56:14 UTC
+++ core/ustring.cpp
@@ -3164,7 +3164,7 @@ String String::http_unescape() const {
 			if ((ord1 >= '0' && ord1 <= '9') || (ord1 >= 'A' && ord1 <= 'Z')) {
 				CharType ord2 = ord_at(i + 2);
 				if ((ord2 >= '0' && ord2 <= '9') || (ord2 >= 'A' && ord2 <= 'Z')) {
-					char bytes[2] = { ord1, ord2 };
+					char bytes[2] = { static_cast<char>(ord1), static_cast<char>(ord2) };
 					res += (char)strtol(bytes, NULL, 16);
 					i += 2;
 				}
