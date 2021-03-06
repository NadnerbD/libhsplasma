/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PyPlasma.h>
#include <PRP/Light/plDirectionalLightInfo.h>
#include "pyLightInfo.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLimitedDirLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLimitedDirLightInfo* self = (pyLimitedDirLightInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLimitedDirLightInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLimitedDirLightInfo_getWidth(pyLimitedDirLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getWidth());
}

static PyObject* pyLimitedDirLightInfo_getHeight(pyLimitedDirLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getHeight());
}

static PyObject* pyLimitedDirLightInfo_getDepth(pyLimitedDirLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDepth());
}

static int pyLimitedDirLightInfo_setWidth(pyLimitedDirLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "width should be a float");
        return -1;
    }
    self->fThis->setWidth(PyFloat_AsDouble(value));
    return 0;
}

static int pyLimitedDirLightInfo_setHeight(pyLimitedDirLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "height should be a float");
        return -1;
    }
    self->fThis->setHeight(PyFloat_AsDouble(value));
    return 0;
}

static int pyLimitedDirLightInfo_setDepth(pyLimitedDirLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "depth should be a float");
        return -1;
    }
    self->fThis->setDepth(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyLimitedDirLightInfo_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLimitedDirLightInfo_GetSet[] = {
    { _pycs("width"), (getter)pyLimitedDirLightInfo_getWidth,
        (setter)pyLimitedDirLightInfo_setWidth, NULL, NULL },
    { _pycs("height"), (getter)pyLimitedDirLightInfo_getHeight,
        (setter)pyLimitedDirLightInfo_setHeight, NULL, NULL },
    { _pycs("depth"), (getter)pyLimitedDirLightInfo_getDepth,
        (setter)pyLimitedDirLightInfo_setDepth, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLimitedDirLightInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLimitedDirLightInfo", /* tp_name */
    sizeof(pyLimitedDirLightInfo),      /* tp_basicsize */
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
    "plLimitedDirLightInfo wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLimitedDirLightInfo_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyLimitedDirLightInfo_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLimitedDirLightInfo_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyLimitedDirLightInfo_Type() {
    pyLimitedDirLightInfo_Type.tp_base = &pyDirectionalLightInfo_Type;
    if (PyType_Ready(&pyLimitedDirLightInfo_Type) < 0)
        return NULL;

    Py_INCREF(&pyLimitedDirLightInfo_Type);
    return (PyObject*)&pyLimitedDirLightInfo_Type;
}

int pyLimitedDirLightInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyLimitedDirLightInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyLimitedDirLightInfo_Type))
        return 1;
    return 0;
}

PyObject* pyLimitedDirLightInfo_FromLimitedDirLightInfo(class plLimitedDirLightInfo* light) {
    if (light == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLimitedDirLightInfo* pyLight = PyObject_New(pyLimitedDirLightInfo, &pyLimitedDirLightInfo_Type);
    pyLight->fThis = light;
    pyLight->fPyOwned = false;
    return (PyObject*)pyLight;
}

}
