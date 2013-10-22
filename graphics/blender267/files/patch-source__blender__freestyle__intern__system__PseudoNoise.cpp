--- source/blender/freestyle/intern/system/PseudoNoise.cpp.orig	2013-05-31 23:05:00.673380982 +0930
+++ source/blender/freestyle/intern/system/PseudoNoise.cpp	2013-05-31 23:06:28.945381873 +0930
@@ -46,7 +46,7 @@
 real PseudoNoise::linearNoise(real x)
 {
 	real tmp;
-	int i = abs(modf(x, &tmp)) * NB_VALUE_NOISE;
+	int i = abs((int)(modf(x, &tmp) * NB_VALUE_NOISE));
 	real x1 = _values[i], x2 = _values[(i + 1) % NB_VALUE_NOISE];
 	real t = modf(x * NB_VALUE_NOISE, &tmp);
 	return x1 * (1 - t) + x2 * t;
@@ -65,7 +65,7 @@
 real PseudoNoise::smoothNoise(real x)
 {
 	real tmp;
-	int i = abs(modf(x, &tmp)) * NB_VALUE_NOISE;
+	int i = abs((int)(modf(x, &tmp) * NB_VALUE_NOISE));
 	int h = i - 1;
 	if (h < 0) {
 		h = NB_VALUE_NOISE + h;
