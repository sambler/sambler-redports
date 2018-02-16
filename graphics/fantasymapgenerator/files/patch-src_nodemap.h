--- src/nodemap.h.orig	2017-02-26 19:02:32 UTC
+++ src/nodemap.h
@@ -56,7 +56,7 @@ public:
 
     T operator()(int idx) {
         if (!_isInRange(idx)) {
-            throw std::range_error("Index out of range:" + idx);
+            throw std::range_error("Index out of range:" + std::to_string(idx));
         }
         return _nodes[idx];
     }
@@ -71,7 +71,7 @@ public:
 
     T* getPointer(int idx) {
         if (!_isInRange(idx)) {
-            throw std::range_error("Index out of range:" + idx);
+            throw std::range_error("Index out of range:" + std::to_string(idx));
         }
         return &_nodes[idx];
     }
@@ -86,7 +86,7 @@ public:
 
     void set(int idx, T val) {
         if (!_isInRange(idx)) {
-            throw std::range_error("Index out of range:" + idx);
+            throw std::range_error("Index out of range:" + std::to_string(idx));
         }
         _nodes[idx] = val;
     }
@@ -101,7 +101,7 @@ public:
 
     void getNeighbours(int idx, std::vector<T> &nbs) {
         if (!_isInRange(idx)) {
-            throw std::range_error("Index out of range:" + idx);
+            throw std::range_error("Index out of range:" + std::to_string(idx));
         }
         std::vector<int> indices;
         indices.reserve(3);
