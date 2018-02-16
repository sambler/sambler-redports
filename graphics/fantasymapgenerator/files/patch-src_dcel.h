--- src/dcel.h.orig	2017-02-26 19:02:32 UTC
+++ src/dcel.h
@@ -103,7 +103,7 @@ public:
 
 	inline Vertex getVertex(int id) {
 		if (!_isVertexInRange(id)) {
-			throw std::range_error("Vertex out of range: " + id);
+			throw std::range_error("Vertex out of range: " + std::to_string(id));
 		}
 		return vertices[id];
 	}
@@ -114,7 +114,7 @@ public:
 
 	inline HalfEdge getHalfEdge(int id) {
 		if (!_isHalfEdgeInRange(id)) {
-			throw std::range_error("HalfEdge out of range: " + id);
+			throw std::range_error("HalfEdge out of range: " + std::to_string(id));
 		}
 		return edges[id];
 	}
@@ -125,77 +125,77 @@ public:
 
 	inline Face getFace(int id) {
 		if (!_isFaceInRange(id)) {
-			throw std::range_error("Face out of range: " + id);
+			throw std::range_error("Face out of range: " + std::to_string(id));
 		}
 		return faces[id];
 	}
 
 	inline void updateVertex(Vertex &v) {
 		if (!_isVertexInRange(v)) {
-			throw std::range_error("Vertex out of range: " + v.id.ref);
+			throw std::range_error("Vertex out of range: " + std::to_string(v.id.ref));
 		}
 		vertices[v.id.ref] = v;
 	}
 
 	inline void updateHalfEdge(HalfEdge &e) {
 		if (!_isHalfEdgeInRange(e)) {
-			throw std::range_error("HalfEdge out of range: " + e.id.ref);
+			throw std::range_error("HalfEdge out of range: " + std::to_string(e.id.ref));
 		}
 		edges[e.id.ref] = e;
 	}
 
 	inline void updateFace(Face &f) {
 		if (!_isFaceInRange(f)) {
-			throw std::range_error("Face out of range: " + f.id.ref);
+			throw std::range_error("Face out of range: " + std::to_string(f.id.ref));
 		}
 		faces[f.id.ref] = f;
 	}
 
 	inline Vertex origin(HalfEdge h) {
 		if (!_isVertexInRange(h.origin)) {
-			throw std::range_error("HalfEdge origin out of range: " + h.origin.ref);
+			throw std::range_error("HalfEdge origin out of range: " + std::to_string(h.origin.ref));
 		}
 		return vertices[h.origin.ref];
 	}
 
 	inline HalfEdge twin(HalfEdge h) {
 		if (!_isHalfEdgeInRange(h.twin)) {
-			throw std::range_error("HalfEdge twin out of range: " + h.twin.ref);
+			throw std::range_error("HalfEdge twin out of range: " + std::to_string(h.twin.ref));
 		}
 		return edges[h.twin.ref];
 	}
 
 	inline Face incidentFace(HalfEdge h) {
 		if (!_isFaceInRange(h.incidentFace)) {
-			throw std::range_error("HalfEdge incident face out of range: " + h.incidentFace.ref);
+			throw std::range_error("HalfEdge incident face out of range: " + std::to_string(h.incidentFace.ref));
 		}
 		return faces[h.incidentFace.ref];
 	}
 
 	inline HalfEdge next(HalfEdge h) {
 		if (!_isHalfEdgeInRange(h.next)) {
-			throw std::range_error("HalfEdge next of range: " + h.next.ref);
+			throw std::range_error("HalfEdge next of range: " + std::to_string(h.next.ref));
 		}
 		return edges[h.next.ref];
 	}
 
 	inline HalfEdge prev(HalfEdge h) {
 		if (!_isHalfEdgeInRange(h.prev)) {
-			throw std::range_error("HalfEdge prev of range: " + h.prev.ref);
+			throw std::range_error("HalfEdge prev of range: " + std::to_string(h.prev.ref));
 		}
 		return edges[h.prev.ref];
 	}
 
 	inline HalfEdge outerComponent(Face f) {
 		if (!_isHalfEdgeInRange(f.outerComponent)) {
-			throw std::range_error("HalfEdge outer component out of range: " + f.outerComponent.ref);
+			throw std::range_error("HalfEdge outer component out of range: " + std::to_string(f.outerComponent.ref));
 		}
 		return edges[f.outerComponent.ref];
 	}
 
 	inline HalfEdge incidentEdge(Vertex v) {
 		if (!_isHalfEdgeInRange(v.incidentEdge)) {
-			throw std::range_error("Vertex incident edge out of range: " + v.incidentEdge.ref);
+			throw std::range_error("Vertex incident edge out of range: " + std::to_string(v.incidentEdge.ref));
 		}
 		return edges[v.incidentEdge.ref];
 	}
