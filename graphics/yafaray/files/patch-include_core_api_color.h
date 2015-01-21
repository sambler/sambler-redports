--- include/core_api/color.h.orig	2013-09-04 02:33:17.000000000 +0930
+++ include/core_api/color.h	2015-01-22 10:13:48.135702499 +1030
@@ -53,8 +54,8 @@
 		color_t(CFLOAT g) { R=G=B=g; }
 		color_t(CFLOAT af[3]) { R=af[0];  G=af[1];  B=af[2]; }
 		bool isBlack() const { return ((R==0) && (G==0) && (B==0)); }
-		bool isNaN() const { return (isnan(R) || isnan(G) || isnan(B)); }
-		bool isInf() const { return (isinf(R) || isinf(G) || isinf(B)); }
+		bool isNaN() const { return (std::isnan(R) || std::isnan(G) || std::isnan(B)); }
+		bool isInf() const { return (std::isinf(R) || std::isinf(G) || std::isinf(B)); }
 		~color_t() {}
 		void set(CFLOAT r, CFLOAT g, CFLOAT b) { R=r;  G=g;  B=b; }
 
