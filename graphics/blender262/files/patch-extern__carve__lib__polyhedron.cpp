--- ./extern/carve/lib/polyhedron.cpp.orig	2013-10-23 01:34:49 UTC
+++ ./extern/carve/lib/polyhedron.cpp
@@ -233,7 +233,7 @@
       }
 
       std::vector<mesh::Mesh<3> *> meshes;
-      mesh::Mesh<3>::create(mesh_faces.begin(), mesh_faces.end(), meshes);
+      mesh::Mesh<3>::create(mesh_faces.begin(), mesh_faces.end(), meshes, mesh::MeshOptions());
       mesh::MeshSet<3> *meshset = new mesh::MeshSet<3>(vertex_storage, meshes);
 
       manifold_is_closed.resize(meshset->meshes.size());
