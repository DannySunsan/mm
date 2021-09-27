#ifndef __EXPORT_H__
#define __EXPORT_H__

#ifndef _MMUTILITY
#define MUTILITY_DLLEXPORT __declspec(dllimport)
#else
#define MUTILITY_DLLEXPORT __declspec(dllexport)
#endif // !MDebug
#endif