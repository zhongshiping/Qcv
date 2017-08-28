#ifndef __CORE_DEF_H__
#define __CORE_DEF_H__

#include <QtGlobal>

#ifdef QcvCore_EXPORTS
#define Qcv_API Q_DECL_EXPORT
#else
#define Qcv_API Q_DECL_IMPORT
#endif

#endif //!__CORE_DEF_H__