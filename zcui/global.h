#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef CUI_EXPORTS
#define CUI_API __declspec(dllexport)
#define CUI_TEMPLATE __declspec(dllexport)
#else
#define CUI_API __declspec(dllimport)
#define CUI_TEMPLATE
#endif

#endif // GLOBAL_H