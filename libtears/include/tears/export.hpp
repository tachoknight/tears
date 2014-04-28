#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/QtGlobal>

#if defined(TEARS_LIBRARY)
/**
 * Exports or Imports the function if it is built or used as a shared library
 */
#  define TEARS_EXPORT Q_DECL_EXPORT
#else
/**
 * Exports or Imports the function if it is built or used as a shared library
 */
#  define TEARS_EXPORT Q_DECL_IMPORT
#endif

/**
 * libSodium generally return -1 when failed and 0 when successful.
 **/
#define TEARS_SODIUM_SUCCESS 0

#endif // EXPORT_H
