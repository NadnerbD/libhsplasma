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
#include <PRP/Physics/plCollisionDetector.h>
#include "pyCollisionDetector.h"
#include "pyDetectorModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyCollisionDetector_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plCollisionDetector is abstract");
    return NULL;
}

static PyObject* pyCollisionDetector_getType(pyCollisionDetector* self, void*) {
    return PyInt_FromLong(plCollisionDetector::Convert(IConvert((pyCreatable*)self))->getType());
}

static int pyCollisionDetector_setType(pyCollisionDetector* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    plCollisionDetector::Convert(IConvert((pyCreatable*)self))->setType(PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyCollisionDetector_GetSet[] = {
    { _pycs("type"), (getter)pyCollisionDetector_getType,
       (setter)pyCollisionDetector_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCollisionDetector_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCollisionDetector",   /* tp_name */
    sizeof(pyCollisionDetector),        /* tp_basicsize */
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
    "plCollisionDetector wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCollisionDetector_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCollisionDetector_new,            /* tp_new */
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

PyObject* Init_pyCollisionDetector_Type() {
    pyCollisionDetector_Type.tp_base = &pyDetectorModifier_Type;
    if (PyType_Ready(&pyCollisionDetector_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeEnter",
        PyInt_FromLong(plCollisionDetector::kTypeEnter));
    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeExit",
        PyInt_FromLong(plCollisionDetector::kTypeExit));
    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeAny",
        PyInt_FromLong(plCollisionDetector::kTypeAny));
    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeUnEnter",
        PyInt_FromLong(plCollisionDetector::kTypeUnEnter));
    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeUnExit",
        PyInt_FromLong(plCollisionDetector::kTypeUnExit));
    PyDict_SetItemString(pyCollisionDetector_Type.tp_dict, "kTypeBump",
        PyInt_FromLong(plCollisionDetector::kTypeBump));

    Py_INCREF(&pyCollisionDetector_Type);
    return (PyObject*)&pyCollisionDetector_Type;
}

int pyCollisionDetector_Check(PyObject* obj) {
    if (obj->ob_type == &pyCollisionDetector_Type
        || PyType_IsSubtype(obj->ob_type, &pyCollisionDetector_Type))
        return 1;
    return 0;
}

PyObject* pyCollisionDetector_FromCollisionDetector(class plCollisionDetector* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCollisionDetector* py = PyObject_New(pyCollisionDetector, &pyCollisionDetector_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
