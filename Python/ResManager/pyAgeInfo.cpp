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
#include <ResManager/plAgeInfo.h>
#include "pyResManager.h"
#include "Stream/pyStream.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static void pyAgeInfo_dealloc(pyAgeInfo* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyAgeInfo___init__(pyAgeInfo* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyAgeInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAgeInfo* self = (pyAgeInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAgeInfo_readFromFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "readFromFile expects a string");
        return NULL;
    }
    self->fThis->readFromFile(filename);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_writeToFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    int version;
    if (!PyArg_ParseTuple(args, "si", &filename, &version)) {
        PyErr_SetString(PyExc_TypeError, "writeToFile expects string, int");
        return NULL;
    }
    self->fThis->writeToFile(filename, (PlasmaVer)version);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getNumPages(pyAgeInfo* self) {
    return PyInt_FromLong(self->fThis->getNumPages());
}

static PyObject* pyAgeInfo_getPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getPage expects an int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getPage(idx);
        return Py_BuildValue("sii", pe.fName.cstr(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getNumCommonPages(pyAgeInfo* self, PyObject* args) {
    int version;
    if (!PyArg_ParseTuple(args, "i", &version)) {
        PyErr_SetString(PyExc_TypeError, "getNumCommonPages expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getNumCommonPages((PlasmaVer)version));
}

static PyObject* pyAgeInfo_getCommonPage(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPage expects int, int");
        return NULL;
    }
    try {
        plAgeInfo::PageEntry pe = self->fThis->getCommonPage(idx, (PlasmaVer)version);
        return Py_BuildValue("sii", pe.fName.cstr(), pe.fSeqSuffix, pe.fLoadFlags);
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_setPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "i(sii)", &idx, &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "setPage expects int, (string, int, int)");
        return NULL;
    }
    self->fThis->setPage(idx, plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_addPage(pyAgeInfo* self, PyObject* args) {
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "(sii)", &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "addPage expects a tuple(string, int, int)");
        return NULL;
    }
    self->fThis->addPage(plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getPageFilename(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getPageFilename expects int, int");
        return NULL;
    }
    try {
        return PlStr_To_PyStr(self->fThis->getPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getCommonPageFilename(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageFilename expects int, int");
        return NULL;
    }
    try {
        return PlStr_To_PyStr(self->fThis->getCommonPageFilename((size_t)idx, (PlasmaVer)version));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "common page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getPageLoc(pyAgeInfo* self, PyObject* args) {
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getCommonPageLoc(pyAgeInfo* self, PyObject* args) {
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx, &ver)) {
        PyErr_SetString(PyExc_TypeError, "getCommonPageLoc expects int, int");
        return NULL;
    }
    try {
        return pyLocation_FromLocation(self->fThis->getCommonPageLoc((size_t)idx, (PlasmaVer)ver));
    } catch (hsOutOfBoundsException) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }
}

static PyObject* pyAgeInfo_getName(pyAgeInfo* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAgeName());
}

static PyObject* pyAgeInfo_getStartDateTime(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getStartDateTime());
}

static PyObject* pyAgeInfo_getDayLength(pyAgeInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDayLength());
}

static PyObject* pyAgeInfo_getMaxCapacity(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getMaxCapacity());
}

static PyObject* pyAgeInfo_getLingerTime(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getLingerTime());
}

static PyObject* pyAgeInfo_getSeqPrefix(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getSeqPrefix());
}

static PyObject* pyAgeInfo_getReleaseVersion(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getReleaseVersion());
}

static int pyAgeInfo_setName(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setAgeName("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "name must be a string");
            return -1;
        }
        self->fThis->setAgeName(PyStr_To_PlStr(value));
    }
    return 0;
}

static int pyAgeInfo_setStartDateTime(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setStartDateTime(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "startDateTime must be an int");
            return -1;
        }
        self->fThis->setStartDateTime(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setDayLength(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setDayLength(0.0f);
    } else {
        if (!PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "dayLength must be a float");
            return -1;
        }
        self->fThis->setDayLength(PyFloat_AsDouble(value));
    }
    return 0;
}

static int pyAgeInfo_setMaxCapacity(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setMaxCapacity(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "maxCapacity must be an int");
            return -1;
        }
        self->fThis->setMaxCapacity(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setLingerTime(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setLingerTime(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "lingerTime must be an int");
            return -1;
        }
        self->fThis->setLingerTime(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setSeqPrefix(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSeqPrefix(-1);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "seqPrefix must be an int");
            return -1;
        }
        self->fThis->setSeqPrefix(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setReleaseVersion(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setReleaseVersion(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "releaseVersion must be an int");
            return -1;
        }
        self->fThis->setReleaseVersion(PyInt_AsLong(value));
    }
    return 0;
}

static PyMethodDef pyAgeInfo_Methods[] = {
    { "readFromFile", (PyCFunction)pyAgeInfo_readFromFile, METH_VARARGS,
      "Params: filename\n"
      "Reads the AgeInfo from a .age file" },
    { "writeToFile", (PyCFunction)pyAgeInfo_writeToFile, METH_VARARGS,
      "Params: filename, version\n"
      "Write the AgeInfo to a .age file" },
    { "getNumPages", (PyCFunction)pyAgeInfo_getNumPages, METH_NOARGS,
      "Returns the number of pages described by this AgeInfo" },
    { "getPage", (PyCFunction)pyAgeInfo_getPage, METH_VARARGS,
      "Params: idx\n"
      "Returns a tuple (name, pageNum, loadFlags) for the specified page" },
    { "getNumCommonPages", (PyCFunction)pyAgeInfo_getNumCommonPages, METH_VARARGS,
      "Params: version\n"
      "Returns the number of common pages described by this AgeInfo" },
    { "getCommonPage", (PyCFunction)pyAgeInfo_getCommonPage, METH_VARARGS,
      "Params: idx, version\n"
      "Returns a tuple (name, pageNum, loadFlags) for the specified common page" },
    { "setPage", (PyCFunction)pyAgeInfo_setPage, METH_VARARGS,
      "Params: idx, (name, pageNum, loadFlags)\n"
      "Sets info for the specified page" },
    { "addPage", (PyCFunction)pyAgeInfo_addPage, METH_VARARGS,
      "Params: (name, pageNum, loadFlags)\n"
      "Adds a page to the AgeInfo" },
    { "getPageFilename", (PyCFunction)pyAgeInfo_getPageFilename, METH_VARARGS,
      "Params: idx, version\n"
      "Returns the standard Page Filename for the specified page" },
    { "getCommonPageFilename", (PyCFunction)pyAgeInfo_getCommonPageFilename, METH_VARARGS,
      "Params: idx, version\n"
      "Returns the standard Page Filename for the specified common page" },
    { "getPageLoc", (PyCFunction)pyAgeInfo_getPageLoc, METH_VARARGS,
      "Params: idx\n"
      "Returns a plLocation for the specified page" },
    { "getCommonPageLoc", (PyCFunction)pyAgeInfo_getCommonPageLoc, METH_VARARGS,
      "Params: idx\n"
      "Returns a plLocation for the specified common page" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAgeInfo_GetSet[] = {
    { _pycs("name"), (getter)pyAgeInfo_getName, (setter)pyAgeInfo_setName,
        _pycs("The Name of the age"), NULL },
    { _pycs("startDateTime"), (getter)pyAgeInfo_getStartDateTime,
        (setter)pyAgeInfo_setStartDateTime, NULL, NULL },
    { _pycs("dayLength"), (getter)pyAgeInfo_getDayLength,
        (setter)pyAgeInfo_setDayLength, NULL, NULL },
    { _pycs("maxCapacity"), (getter)pyAgeInfo_getMaxCapacity,
        (setter)pyAgeInfo_setMaxCapacity, NULL, NULL },
    { _pycs("lingerTime"), (getter)pyAgeInfo_getLingerTime,
        (setter)pyAgeInfo_setLingerTime, NULL, NULL },
    { _pycs("seqPrefix"), (getter)pyAgeInfo_getSeqPrefix,
        (setter)pyAgeInfo_setSeqPrefix, NULL, NULL },
    { _pycs("releaseVersion"), (getter)pyAgeInfo_getReleaseVersion,
        (setter)pyAgeInfo_setReleaseVersion, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAgeInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAgeInfo",             /* tp_name */
    sizeof(pyAgeInfo),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyAgeInfo_dealloc,      /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    NULL,                               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAgeInfo_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeInfo_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyAgeInfo___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeInfo_new,                      /* tp_new */
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

PyObject* Init_pyAgeInfo_Type() {
    if (PyType_Ready(&pyAgeInfo_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagPreventAutoLoad",
                         PyInt_FromLong(plAgeInfo::kPreventAutoLoad));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagLoadIfSDLPresent",
                         PyInt_FromLong(plAgeInfo::kLoadIfSDLPresent));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsLocalOnly",
                         PyInt_FromLong(plAgeInfo::kIsLocalOnly));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsVolatile",
                         PyInt_FromLong(plAgeInfo::kIsVolatile));

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageTextures",
                         PyInt_FromLong(plAgeInfo::kTextures));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageGlobal",
                         PyInt_FromLong(plAgeInfo::kGlobal));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kNumCommonPages",
                         PyInt_FromLong(plAgeInfo::kNumCommonPages));

    PyObject* list = PyList_New(plAgeInfo::kNumCommonPages);
    for (size_t i=0; i<plAgeInfo::kNumCommonPages; i++)
        PyList_SET_ITEM(list, i, PlStr_To_PyStr(plAgeInfo::kCommonPages[i]));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kCommonPages", list);

    Py_INCREF(&pyAgeInfo_Type);
    return (PyObject*)&pyAgeInfo_Type;
}

int pyAgeInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyAgeInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyAgeInfo_Type))
        return 1;
    return 0;
}

PyObject* pyAgeInfo_FromAgeInfo(class plAgeInfo* age) {
    if (age == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAgeInfo* obj = PyObject_New(pyAgeInfo, &pyAgeInfo_Type);
    obj->fThis = age;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
