--- extern/rangetree/range_tree.hh.orig	2012-12-31 01:12:29 UTC
+++ extern/rangetree/range_tree.hh
@@ -35,6 +35,12 @@ struct RangeTree {
 			: min(t), max(t), single(true)
 		{}
 
+                Range& operator=(const Range& v) {
+                        *this = v;
+                        return *this;
+                }
+
+
 		bool operator<(const Range& v) const {
 			return max < v.min;
 		}
