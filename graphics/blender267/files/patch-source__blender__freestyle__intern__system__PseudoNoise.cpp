--- source/blender/freestyle/intern/system/PseudoNoise.cpp.orig	2013-05-29 15:56:09 UTC
+++ source/blender/freestyle/intern/system/PseudoNoise.cpp
@@ -46,7 +46,7 @@ void PseudoNoise::init(long seed)
 real PseudoNoise::linearNoise(real x)
 {
 	real tmp;
-	int i = abs(modf(x, &tmp)) * NB_VALUE_NOISE;
+	int i = abs((int)(modf(x, &tmp) * NB_VALUE_NOISE));
 	real x1 = _values[i], x2 = _values[(i + 1) % NB_VALUE_NOISE];
 	real t = modf(x * NB_VALUE_NOISE, &tmp);
 	return x1 * (1 - t) + x2 * t;
@@ -64,7 +64,7 @@ static real LanczosWindowed(real t)
 real PseudoNoise::smoothNoise(real x)
 {
 	real tmp;
-	int i = abs(modf(x, &tmp)) * NB_VALUE_NOISE;
+	int i = abs((int)(modf(x, &tmp) * NB_VALUE_NOISE));
 	int h = i - 1;
 	if (h < 0) {
 		h = NB_VALUE_NOISE + h;
