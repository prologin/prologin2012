///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_python.rb
//

#include "interface.hh"

static PyObject* c_module;
static PyObject* py_module;
static PyObject* champ_module;

static void _init_python();

template <typename Lang, typename Cxx>
Lang cxx2lang(Cxx in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
PyObject* cxx2lang<PyObject*, int>(int in)
{
  return PyInt_FromLong(in);
}


template <>
PyObject* cxx2lang<PyObject*, std::string>(std::string in)
{
return PyString_FromString (in.c_str());
}


template <>
PyObject* cxx2lang<PyObject*, bool>(bool in)
{
  return PyBool_FromLong(in);
}

template <typename Cxx>
PyObject* cxx2lang_array(const std::vector<Cxx>& in)
{
  size_t size = in.size();
  PyObject* out = PyList_New(size);

  for (unsigned int i = 0; i < size; ++i)
    PyList_SET_ITEM(out, i, (cxx2lang<PyObject*, Cxx>(in[i])));

  return out;
}

template <typename Lang, typename Cxx>
Cxx lang2cxx(Lang in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
int lang2cxx<PyObject*, int>(PyObject* in)
{
  long out = PyInt_AsLong(in);
  if (out == -1)
    if (PyErr_Occurred())
    {
      throw 42;
    }

  return out;
}

template <>
bool lang2cxx<PyObject*, bool>(PyObject* in)
{
  return (bool)lang2cxx<PyObject*, int>(in);
}

template <>
std::string lang2cxx<PyObject*, std::string>(PyObject* in)
{
  char * out = PyString_AS_STRING(in);
  if (PyErr_Occurred())
    {
      throw 42;
    }
  return out;
}

template <typename Cxx>
std::vector<Cxx> lang2cxx_array(PyObject* in)
{
  if (!PyList_Check(in))
  {
    PyErr_SetString(PyExc_TypeError, "a list is required");
    throw 42;
  }

  std::vector<Cxx> out;
  unsigned int size = PyList_Size(in);

  for (unsigned int i = 0; i < size; ++i)
    out.push_back(lang2cxx<PyObject*, Cxx>(PyList_GET_ITEM(in, i)));

  return out;
}
///
// Type de personnage
//
template <>
PyObject* cxx2lang<PyObject*, perso_classe>(perso_classe in)
{
  return cxx2lang<PyObject*, int>((int)in);
}

template <>
perso_classe lang2cxx<PyObject*, perso_classe>(PyObject* in)
{
  return (perso_classe)lang2cxx<PyObject*, int>(in);
}

///
// Type de zone
//
template <>
PyObject* cxx2lang<PyObject*, zone_type>(zone_type in)
{
  return cxx2lang<PyObject*, int>((int)in);
}

template <>
zone_type lang2cxx<PyObject*, zone_type>(PyObject* in)
{
  return (zone_type)lang2cxx<PyObject*, int>(in);
}

///
// Type d'attaque
//
template <>
PyObject* cxx2lang<PyObject*, attaque_type>(attaque_type in)
{
  return cxx2lang<PyObject*, int>((int)in);
}

template <>
attaque_type lang2cxx<PyObject*, attaque_type>(PyObject* in)
{
  return (attaque_type)lang2cxx<PyObject*, int>(in);
}

///
// Orientation du personnage
//
template <>
PyObject* cxx2lang<PyObject*, orientation>(orientation in)
{
  return cxx2lang<PyObject*, int>((int)in);
}

template <>
orientation lang2cxx<PyObject*, orientation>(PyObject* in)
{
  return (orientation)lang2cxx<PyObject*, int>(in);
}

///
// Erreurs possibles
//
template <>
PyObject* cxx2lang<PyObject*, erreur>(erreur in)
{
  return cxx2lang<PyObject*, int>((int)in);
}

template <>
erreur lang2cxx<PyObject*, erreur>(PyObject* in)
{
  return (erreur)lang2cxx<PyObject*, int>(in);
}

///
// Représente une position sur le terrain du jeu
//
template <>
PyObject* cxx2lang<PyObject*, position>(position in)
{
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, int>(in.x)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.y)));
  PyObject* name = PyString_FromString("position");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
position lang2cxx<PyObject*, position>(PyObject* in)
{
  position out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.x = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.y = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  return out;
}

///
// Représente les informations sur un personnage
//
template <>
PyObject* cxx2lang<PyObject*, perso_info>(perso_info in)
{
  PyObject* tuple = PyTuple_New(4);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, int>(in.equipe)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, perso_classe>(in.classe)));
  PyTuple_SET_ITEM(tuple, 2, (cxx2lang<PyObject*, int>(in.vie)));
  PyTuple_SET_ITEM(tuple, 3, (cxx2lang<PyObject*, orientation>(in.direction)));
  PyObject* name = PyString_FromString("perso_info");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
perso_info lang2cxx<PyObject*, perso_info>(PyObject* in)
{
  perso_info out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.equipe = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.classe = lang2cxx<PyObject*, perso_classe>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(2);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.vie = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(3);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.direction = lang2cxx<PyObject*, orientation>(i);
  Py_DECREF(i);
  return out;
}

///
// Retourne la taille de la carte.
//
static PyObject* p_carte_taille(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, position>(api_carte_taille());
  } catch (...) { return NULL; }
}

///
// Retourne la position de départ des personnages sur la map.
//
static PyObject* p_carte_depart(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, position>(api_carte_depart());
  } catch (...) { return NULL; }
}

///
// Retourne la nature de la zone désignée par ``pos``.
//
static PyObject* p_carte_zone_type(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, zone_type>(api_carte_zone_type(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Retourne la liste des personnages sur la zone.
//
static PyObject* p_carte_zone_perso(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_carte_zone_perso(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie la longueur du chemin le plus court entre deux points. Renvoie -1 en cas de positions invalides ou de chemin inexistant.
//
static PyObject* p_distance(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_distance(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Renvoie le chemin le plus court entre deux points. Si le chemin n'existe pas, ou si les positions sont invalides, le chemin renvoyé est vide.
//
static PyObject* p_chemin(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_chemin(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Déplace le personnage ``perso`` en suivant un le chemin ``chemin`` donné sous forme d'une suite de ``position``, orientant le personnage sur la zone d'arrivée dans la direction ``orientation``.
//
static PyObject* p_perso_deplace(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
  if (!PyArg_ParseTuple(args, "OOO", &a0, &a1, &a2)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_perso_deplace(lang2cxx<PyObject*, perso_info>(a0), lang2cxx_array<position>(a1), lang2cxx<PyObject*, orientation>(a2)));
  } catch (...) { return NULL; }
}

///
// Récupère la liste des zones sur lesquelles des personnages ont été aperçus dans la pénombre par ``perso``.
//
static PyObject* p_perso_penombre(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_perso_penombre(lang2cxx<PyObject*, perso_info>(a0)));
  } catch (...) { return NULL; }
}

///
// Récupère la liste des zones dans le champs de vision de ``perso``.
//
static PyObject* p_perso_vision(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_perso_vision(lang2cxx<PyObject*, perso_info>(a0)));
  } catch (...) { return NULL; }
}

///
// Récupère la liste des zones dans le champs de vision de ``perso`` où sont situés un ou plusieurs personnages (amis ou ennemis).
//
static PyObject* p_perso_vision_personnages(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_perso_vision_personnages(lang2cxx<PyObject*, perso_info>(a0)));
  } catch (...) { return NULL; }
}

///
// Récupère la liste des positions sur lesquelles le palantír du voleur voit d'autre personnages.
//
static PyObject* p_palantir_vision(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_palantir_vision());
  } catch (...) { return NULL; }
}

///
// Récupère la liste des zones sur lesquelles l'elfe peut voir via son attaque "I See What You Did There".
//
static PyObject* p_elfe_vision(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_elfe_vision());
  } catch (...) { return NULL; }
}

///
// Effectue l'attaque ``attaque`` avec le personnage ``perso`` sur la zone ``pos``.
//
static PyObject* p_perso_attaque(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
  if (!PyArg_ParseTuple(args, "OOO", &a0, &a1, &a2)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_perso_attaque(lang2cxx<PyObject*, perso_info>(a0), lang2cxx<PyObject*, attaque_type>(a1), lang2cxx<PyObject*, position>(a2)));
  } catch (...) { return NULL; }
}

///
// Retourne le temps de recharge restant pour l'attaque ``attaque`` du personnage ``perso``.
//
static PyObject* p_perso_attaque_recharge(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_perso_attaque_recharge(lang2cxx<PyObject*, perso_info>(a0), lang2cxx<PyObject*, attaque_type>(a1)));
  } catch (...) { return NULL; }
}

///
// Retourne le numéro de votre équipe
//
static PyObject* p_mon_equipe(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_mon_equipe());
  } catch (...) { return NULL; }
}

///
// Retourne les scores de chaque équipe
//
static PyObject* p_scores(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_scores());
  } catch (...) { return NULL; }
}

///
// Retourne le nombre d'équipes sur le terrain
//
static PyObject* p_nombre_equipes(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_nombre_equipes());
  } catch (...) { return NULL; }
}

///
// Retourne le numéro du tour actuel
//
static PyObject* p_tour_actuel(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_tour_actuel());
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type perso_classe
//
static PyObject* p_afficher_perso_classe(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_perso_classe(lang2cxx<PyObject*, perso_classe>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type zone_type
//
static PyObject* p_afficher_zone_type(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_zone_type(lang2cxx<PyObject*, zone_type>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type attaque_type
//
static PyObject* p_afficher_attaque_type(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_attaque_type(lang2cxx<PyObject*, attaque_type>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type orientation
//
static PyObject* p_afficher_orientation(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_orientation(lang2cxx<PyObject*, orientation>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type erreur
//
static PyObject* p_afficher_erreur(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_erreur(lang2cxx<PyObject*, erreur>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type position
//
static PyObject* p_afficher_position(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_position(lang2cxx<PyObject*, position>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type perso_info
//
static PyObject* p_afficher_perso_info(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_perso_info(lang2cxx<PyObject*, perso_info>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

static PyObject* p_get_dump(PyObject* self, PyObject* args)
{
    const char* dump = api_get_dump();
    PyObject* py_dump = PyString_FromString(dump);
    return py_dump;
}


/*
** Api functions to register.
*/
static PyMethodDef api_callback[] = {
  {"carte_taille", p_carte_taille, METH_VARARGS, "carte_taille"},  {"carte_depart", p_carte_depart, METH_VARARGS, "carte_depart"},  {"carte_zone_type", p_carte_zone_type, METH_VARARGS, "carte_zone_type"},  {"carte_zone_perso", p_carte_zone_perso, METH_VARARGS, "carte_zone_perso"},  {"distance", p_distance, METH_VARARGS, "distance"},  {"chemin", p_chemin, METH_VARARGS, "chemin"},  {"perso_deplace", p_perso_deplace, METH_VARARGS, "perso_deplace"},  {"perso_penombre", p_perso_penombre, METH_VARARGS, "perso_penombre"},  {"perso_vision", p_perso_vision, METH_VARARGS, "perso_vision"},  {"perso_vision_personnages", p_perso_vision_personnages, METH_VARARGS, "perso_vision_personnages"},  {"palantir_vision", p_palantir_vision, METH_VARARGS, "palantir_vision"},  {"elfe_vision", p_elfe_vision, METH_VARARGS, "elfe_vision"},  {"perso_attaque", p_perso_attaque, METH_VARARGS, "perso_attaque"},  {"perso_attaque_recharge", p_perso_attaque_recharge, METH_VARARGS, "perso_attaque_recharge"},  {"mon_equipe", p_mon_equipe, METH_VARARGS, "mon_equipe"},  {"scores", p_scores, METH_VARARGS, "scores"},  {"nombre_equipes", p_nombre_equipes, METH_VARARGS, "nombre_equipes"},  {"tour_actuel", p_tour_actuel, METH_VARARGS, "tour_actuel"},  {"afficher_perso_classe", p_afficher_perso_classe, METH_VARARGS, "afficher_perso_classe"},  {"afficher_zone_type", p_afficher_zone_type, METH_VARARGS, "afficher_zone_type"},  {"afficher_attaque_type", p_afficher_attaque_type, METH_VARARGS, "afficher_attaque_type"},  {"afficher_orientation", p_afficher_orientation, METH_VARARGS, "afficher_orientation"},  {"afficher_erreur", p_afficher_erreur, METH_VARARGS, "afficher_erreur"},  {"afficher_position", p_afficher_position, METH_VARARGS, "afficher_position"},  {"afficher_perso_info", p_afficher_perso_info, METH_VARARGS, "afficher_perso_info"}, {"get_dump", p_get_dump, METH_VARARGS, "get_dump"}, {NULL, NULL, 0, NULL}
};

static void _initapi()
{
  c_module = Py_InitModule("_api", api_callback);
  c_module = Py_InitModule("_api", api_callback);
}

/*
** Inititialize python, register API functions,
** and load .py file
*/
static void _init_python()
{
  PyObject* name;
  const char* champion_path;
      
  champion_path = getenv("CHAMPION_PATH");
  if (champion_path == NULL)
    champion_path = ".";

  setenv("PYTHONPATH", champion_path, 1);

  static char program_name[] = "stechec";
  Py_SetProgramName(program_name);
  Py_Initialize();
  _initapi();

  name = PyString_FromString("prologin");
  champ_module = PyImport_Import(name);
  Py_DECREF(name);
  if (champ_module == NULL)
    if (PyErr_Occurred())
    {
      PyErr_Print();
      abort();
    }

  name = PyString_FromString("api");
  py_module = PyImport_Import(name);
  Py_DECREF(name);
  if (py_module == NULL)
    if (PyErr_Occurred())
    {
      PyErr_Print();
      abort();
    }
}

/*
** Run a python function.
*/
static PyObject* _call_python_function(const char* name)
{
  static bool initialized = false;

  if (!initialized)
  {
    initialized = true;
    _init_python();
  }

  PyObject *arglist, *func;
  PyObject *result = NULL;
  
  func = PyObject_GetAttrString(champ_module, (char*)name);
  if (func && PyCallable_Check(func))
  {
    arglist = Py_BuildValue("()");
    result = PyEval_CallObject(func, arglist);
    Py_XDECREF(arglist);
    Py_DECREF(func);
  }
  if (result == NULL && PyErr_Occurred())
    PyErr_Print();

  return result;
}

/*
** Functions called from stechec to C.
*/
extern "C" void partie_init()
{
  PyObject* _retval = _call_python_function("partie_init");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void jouer_placement()
{
  PyObject* _retval = _call_python_function("jouer_placement");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void jouer_deplacement()
{
  PyObject* _retval = _call_python_function("jouer_deplacement");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void jouer_attaque()
{
  PyObject* _retval = _call_python_function("jouer_attaque");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void partie_fin()
{
  PyObject* _retval = _call_python_function("partie_fin");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

