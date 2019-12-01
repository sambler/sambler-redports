--- source/gameengine/Ketsji/KX_GameObject.cpp.orig	2019-11-30 15:03:30 UTC
+++ source/gameengine/Ketsji/KX_GameObject.cpp
@@ -2564,7 +2564,7 @@ PyObject *KX_GameObject::pyattr_get_is_suspend_dynamic
   KX_GameObject *self = static_cast<KX_GameObject *>(self_v);
 
   // Only objects with a physics controller can be suspended
-  PYTHON_CHECK_PHYSICS_CONTROLLER(self, attrdef->m_name, nullptr);
+  PYTHON_CHECK_PHYSICS_CONTROLLER(self, attrdef->m_name.c_str(), nullptr);
 
   return PyBool_FromLong(self->IsDynamicsSuspended());
 }
