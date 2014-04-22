#ifndef TEARS_HPP
#define TEARS_HPP

#include <QtCore/QtGlobal>

#if defined(TEARS_LIBRARY)
#  define TEARS_EXPORT Q_DECL_EXPORT
#else
#  define TEARS_EXPORT Q_DECL_IMPORT
#endif

#define TEARS_SODIUM_SUCCESS 0

#include <sodium.h>
#include <QByteArray>

#include <tears/crypto.hpp>
#include <tears/hashing.hpp>
#include <tears/util.hpp>

#endif // TEARS_HPP
