--- src/vertexmap.cpp.orig	2018-02-16 07:47:33 UTC
+++ src/vertexmap.cpp
@@ -68,7 +68,7 @@ void gen::VertexMap::getNeighbourIndices
 
 int gen::VertexMap::getVertexIndex(dcel::Vertex &v) {
     if (!_isInRange(v.id.ref)) {
-        throw std::range_error("Index out of range:" + v.id.ref);
+        throw std::range_error("Index out of range:" + std::to_string(v.id.ref));
     }
     return _vertexIdToMapIndex[v.id.ref];
 }
