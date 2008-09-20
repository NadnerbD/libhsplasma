#include <Python.h>
#include <PRP/plSceneNode.h>
#include "pySceneNode.h"
#include "KeyedObject/pyKey.h"
#include "KeyedObject/pyKeyedObject.h"
#include "pyCreatable.h"

extern "C" {

static PyObject* pySceneNode_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySceneNode* self = (pySceneNode*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSceneNode();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySceneNode_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySceneNode_FromSceneNode(plSceneNode::Convert(cre->fThis));
}

static PyObject* pySceneNode_clear(pySceneNode* self) {
    self->fThis->getSceneObjects().clear();
    self->fThis->getPoolObjects().clear();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addSceneObject(pySceneNode* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObject expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObject expects a plKey");
        return NULL;
    }
    self->fThis->getSceneObjects().append(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addPoolObject(pySceneNode* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObject expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObject expects a plKey");
        return NULL;
    }
    self->fThis->getPoolObjects().append(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addSceneObjects(pySceneNode* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    hsTArray<plKey> addend;
    addend.setSize(PyList_Size(list));
    for (size_t i=0; i<addend.getSize(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getSceneObjects().append(addend);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addPoolObjects(pySceneNode* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    hsTArray<plKey> addend;
    addend.setSize(PyList_Size(list));
    for (size_t i=0; i<addend.getSize(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getPoolObjects().append(addend);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_numSceneObjects(pySceneNode* self) {
    return PyInt_FromLong(self->fThis->getNumSceneObjects());
}

static PyObject* pySceneNode_numPoolObjects(pySceneNode* self) {
    return PyInt_FromLong(self->fThis->getNumPoolObjects());
}

static PyObject* pySceneNode_getSceneObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumSceneObjects());
    for (size_t i=0; i<self->fThis->getNumSceneObjects(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getSceneObject(i)));
    return list;
}

static PyObject* pySceneNode_getPoolObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumPoolObjects());
    for (size_t i=0; i<self->fThis->getNumPoolObjects(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPoolObject(i)));
    return list;
}

static int pySceneNode_setSceneObjects(pySceneNode* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Scene Objects, use addSceneObjects");
    return -1;
}

static int pySceneNode_setPoolObjects(pySceneNode* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Pool Objects, use addPoolObjects");
    return -1;
}

PyMethodDef pySceneNode_Methods[] = {
    { "Convert", (PyCFunction)pySceneNode_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSceneNode" },
    { "clear", (PyCFunction)pySceneNode_clear, METH_NOARGS,
      "Removes all objects from the Scene Node" },
    { "addSceneObject", (PyCFunction)pySceneNode_addSceneObject, METH_VARARGS,
      "Params: key\n"
      "Adds the Scene Object to the Scene Node" },
    { "addPoolObject", (PyCFunction)pySceneNode_addPoolObject, METH_VARARGS,
      "Params: key\n"
      "Adds the Object to the Scene Node" },
    { "addSceneObjects", (PyCFunction)pySceneNode_addSceneObjects, METH_VARARGS,
      "Params: keyArray\n"
      "Adds multiple Scene Objects to the Scene Node" },
    { "addPoolObject", (PyCFunction)pySceneNode_addPoolObjects, METH_VARARGS,
      "Params: keyArray\n"
      "Adds multiple Object to the Scene Node" },
    { "numSceneObjects", (PyCFunction)pySceneNode_numSceneObjects, METH_NOARGS,
      "Faster than len(plSceneNode.sceneObjects)" },
    { "numPoolObjects", (PyCFunction)pySceneNode_numPoolObjects, METH_NOARGS,
      "Faster than len(plSceneNode.poolObjects)" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pySceneNode_GetSet[] = {
    { "sceneObjects", (getter)pySceneNode_getSceneObjects,
      (setter)pySceneNode_setSceneObjects, NULL, NULL },
    { "poolObjects", (getter)pySceneNode_getPoolObjects,
      (setter)pySceneNode_setPoolObjects, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySceneNode_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSceneNode",             /* tp_name */
    sizeof(pySceneNode),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plSceneNode wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySceneNode_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pySceneNode_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySceneNode_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySceneNode_Type() {
    pySceneNode_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pySceneNode_Type) < 0)
        return NULL;

    Py_INCREF(&pySceneNode_Type);
    return (PyObject*)&pySceneNode_Type;
}

int pySceneNode_Check(PyObject* obj) {
    if (obj->ob_type == &pySceneNode_Type
        || PyType_IsSubtype(obj->ob_type, &pySceneNode_Type))
        return 1;
    return 0;
}

PyObject* pySceneNode_FromSceneNode(class plSceneNode* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySceneNode* node = PyObject_New(pySceneNode, &pySceneNode_Type);
    node->fThis = obj;
    node->fPyOwned = false;
    return (PyObject*)node;
}

}