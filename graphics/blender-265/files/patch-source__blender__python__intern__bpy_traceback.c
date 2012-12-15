--- ./source/blender/python/intern/bpy_traceback.c.orig	2012-12-15 21:44:09.968421690 +1030
+++ ./source/blender/python/intern/bpy_traceback.c	2012-12-15 21:45:10.022032402 +1030
@@ -39,6 +39,74 @@
 	return PyBytes_AS_STRING((*coerce = PyUnicode_EncodeFSDefault(tb->tb_frame->f_code->co_filename)));
 }
 
+#if PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION == 2
+/* copied from pythonrun.c, 3.2.0 */
+static int
+parse_syntax_error(PyObject *err, PyObject **message, const char **filename,
+					int *lineno, int *offset, const char **text)
+{
+	long hold;
+	PyObject *v;
+
+	/* old style errors */
+	if (PyTuple_Check(err))
+		return PyArg_ParseTuple(err, "O(ziiz)", message, filename,
+								lineno, offset, text);
+
+	/* new style errors.  `err' is an instance */
+
+	if (!(v = PyObject_GetAttrString(err, "msg")))
+		goto finally;
+	*message = v;
+
+	if (!(v = PyObject_GetAttrString(err, "filename")))
+		goto finally;
+	if (v == Py_None)
+		*filename = NULL;
+	else if (!(*filename = _PyUnicode_AsString(v)))
+		goto finally;
+
+	Py_DECREF(v);
+	if (!(v = PyObject_GetAttrString(err, "lineno")))
+		goto finally;
+	hold = PyLong_AsLong(v);
+	Py_DECREF(v);
+	v = NULL;
+	if (hold < 0 && PyErr_Occurred())
+		goto finally;
+	*lineno = (int)hold;
+
+	if (!(v = PyObject_GetAttrString(err, "offset")))
+		goto finally;
+	if (v == Py_None) {
+		*offset = -1;
+		Py_DECREF(v);
+		v = NULL;
+	}
+	else {
+		hold = PyLong_AsLong(v);
+		Py_DECREF(v);
+		v = NULL;
+		if (hold < 0 && PyErr_Occurred())
+			goto finally;
+		*offset = (int)hold;
+	}
+
+	if (!(v = PyObject_GetAttrString(err, "text")))
+		goto finally;
+	if (v == Py_None)
+		*text = NULL;
+	else if (!PyUnicode_Check(v) || !(*text = _PyUnicode_AsString(v)))
+		 goto finally;
+	Py_DECREF(v);
+	return 1;
+
+finally:
+	Py_XDECREF(v);
+	return 0;
+}
+/* end copied function! */
+#else /* py3.3 */
 /* copied from pythonrun.c, 3.3.0 */
 static int
 parse_syntax_error(PyObject *err, PyObject **message, const char **filename,
@@ -116,6 +184,7 @@
 	return 0;
 }
 /* end copied function! */
+#endif /* python version */
 
 
 void python_script_error_jump(const char *filepath, int *lineno, int *offset)
