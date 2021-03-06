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
#include <PRP/Message/plArmatureEffectMsg.h>
#include "pyArmatureEffectMsg.h"
#include "pyMessage.h"

extern "C" {

static PyObject* pyArmatureEffectStateMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyArmatureEffectStateMsg* self = (pyArmatureEffectStateMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plArmatureEffectStateMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyArmatureEffectStateMsg_getSurface(pyArmatureEffectStateMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getSurface());
}

static PyObject* pyArmatureEffectStateMsg_getAddSurface(pyArmatureEffectStateMsg* self, void*) {
    return PyBool_FromLong(self->fThis->getAddSurface() ? 1 : 0);
}

static int pyArmatureEffectStateMsg_setSurface(pyArmatureEffectStateMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "surface should be an int");
        return -1;
    }
    self->fThis->setSurface((int8_t)PyInt_AsLong(value));
    return 0;
}

static int pyArmatureEffectStateMsg_setAddSurface(pyArmatureEffectStateMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "addSurface should be a boolean");
        return -1;
    }
    self->fThis->setAddSurface(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyArmatureEffectStateMsg_GetSet[] = {
    { _pycs("surface"), (getter)pyArmatureEffectStateMsg_getSurface,
        (setter)pyArmatureEffectStateMsg_setSurface, NULL, NULL },
    { _pycs("addSurface"), (getter)pyArmatureEffectStateMsg_getAddSurface,
        (setter)pyArmatureEffectStateMsg_setAddSurface, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyArmatureEffectStateMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plArmatureEffectStateMsg", /* tp_name */
    sizeof(pyArmatureEffectStateMsg),      /* tp_basicsize */
    0,                                     /* tp_itemsize */

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
    "plArmatureEffectStateMsg wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyArmatureEffectStateMsg_GetSet,    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyArmatureEffectStateMsg_new,       /* tp_new */
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

PyObject* Init_pyArmatureEffectStateMsg_Type() {
    pyArmatureEffectStateMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyArmatureEffectStateMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyArmatureEffectStateMsg_Type);
    return (PyObject*)&pyArmatureEffectStateMsg_Type;
}

int pyArmatureEffectStateMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyArmatureEffectStateMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyArmatureEffectStateMsg_Type))
        return 1;
    return 0;
}

PyObject* pyArmatureEffectStateMsg_FromArmatureEffectStateMsg(plArmatureEffectStateMsg* msg) {
    if (msg == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyArmatureEffectStateMsg* pyobj = PyObject_New(pyArmatureEffectStateMsg, &pyArmatureEffectStateMsg_Type);
    pyobj->fThis = msg;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
