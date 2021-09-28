#pragma once

#define TYPEDEFINECLASS(Classname) \
typedef RefCounterPtr<Classname> Classname##Ptr;\
typedef Classname* Classname##P;\
typedef Classname& Classname##R;\
typedef const Classname Classname##C;\
typedef const Classname& Classname##CR;