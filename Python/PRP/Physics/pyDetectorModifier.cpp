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
#include <PRP/Physics/plDetectorModifier.h>
#include "pyDetectorModifier.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"

extern "C" {

static PyObject* pyDetectorModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plDetectorModifier is abstract");
    return NULL;
}

static PyObject* pyDetectorModifier_addReceiver(pyDetectorModifier* self, PyObject* args) {
    PyObject* receiver;
    if (!(PyArg_ParseTuple(args, "O", &receiver) && pyKey_Check(receiver))) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }

    plDetectorModifier::Convert(IConvert((pyCreatable*)self))->addReceiver(*((pyKey*)receiver)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDetectorModifier_clearReceivers(pyDetectorModifier* self) {
    plDetectorModifier::Convert(IConvert((pyCreatable*)self))->clearReceivers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDetectorModifier_delReceiver(pyDetectorModifier* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }

    plDetectorModifier::Convert(IConvert((pyCreatable*)self))->delReceiver((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyDetectorModifier_Methods[] = {
    { "addReceiver", (PyCFunction)pyDetectorModifier_addReceiver, METH_VARARGS,
      "Params: key\n"
      "Adds a notification receiver to this detector" },
    { "clearReceivers", (PyCFunction)pyDetectorModifier_clearReceivers, METH_NOARGS,
      "Removes all receivers from this detector" },
    { "delReceiver", (PyCFunction)pyDetectorModifier_delReceiver, METH_VARARGS,
      "Params: idx\n"
      "Removes a receiver from this detector" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyDetectorModifier_getReceivers(pyDetectorModifier* self, void*) {
    plDetectorModifier* mod = plDetectorModifier::Convert(IConvert((pyCreatable*)self));
    PyObject* sequence = PyTuple_New(mod->getReceivers().size());
    for (size_t i = 0; i < mod->getReceivers().size(); ++i)
        PyTuple_SET_ITEM(sequence, i, pyKey_FromKey(mod->getReceivers()[i]));
    return sequence;
}

static PyObject* pyDetectorModifier_getRemoteMod(pyDetectorModifier* self, void*) {
    return pyKey_FromKey(plDetectorModifier::Convert(IConvert((pyCreatable*)self))->getRemoteMod());
}

static PyObject* pyDetectorModifier_getProxy(pyDetectorModifier* self, void*) {
    return pyKey_FromKey(plDetectorModifier::Convert(IConvert((pyCreatable*)self))->getProxy());
}

static int pyDetectorModifier_setReceivers(pyDetectorModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver");
    return -1;
}

static int pyDetectorModifier_setRemoteMod(pyDetectorModifier* self, PyObject* value, void*) {
    if (value == NULL) {
        plDetectorModifier::Convert(IConvert((pyCreatable*)self))->setRemoteMod(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        plDetectorModifier::Convert(IConvert((pyCreatable*)self))->setRemoteMod(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "remoteMod should be a plKey");
        return -1;
    }
}

static int pyDetectorModifier_setProxy(pyDetectorModifier* self, PyObject* value, void*) {
    if (value == NULL) {
        plDetectorModifier::Convert(IConvert((pyCreatable*)self))->setProxy(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        plDetectorModifier::Convert(IConvert((pyCreatable*)self))->setProxy(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "proxy should be a plKey");
        return -1;
    }
}

static PyGetSetDef pyDetectorModifier_GetSet[] = {
    { _pycs("receivers"), (getter)pyDetectorModifier_getReceivers,
        (setter)pyDetectorModifier_setReceivers, NULL, NULL },
    { _pycs("remoteMod"), (getter)pyDetectorModifier_getRemoteMod,
        (setter)pyDetectorModifier_setRemoteMod, NULL, NULL },
    { _pycs("proxy"), (getter)pyDetectorModifier_getProxy,
        (setter)pyDetectorModifier_setProxy, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDetectorModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDetectorModifier",    /* tp_name */
    sizeof(pyDetectorModifier),         /* tp_basicsize */
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
    "plDetectorModifier wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDetectorModifier_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyDetectorModifier_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDetectorModifier_new,             /* tp_new */
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

PyObject* Init_pyDetectorModifier_Type() {
    pyDetectorModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyDetectorModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyDetectorModifier_Type);
    return (PyObject*)&pyDetectorModifier_Type;
}

int pyDetectorModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pyDetectorModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pyDetectorModifier_Type))
        return 1;
    return 0;
}

PyObject* pyDetectorModifier_FromDetectorModifier(class plDetectorModifier* phys) {
    if (phys == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDetectorModifier* pyphys = PyObject_New(pyDetectorModifier, &pyDetectorModifier_Type);
    pyphys->fThis = phys;
    pyphys->fPyOwned = false;
    return (PyObject*)pyphys;
}

};
