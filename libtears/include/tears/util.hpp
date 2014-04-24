#ifndef UTIL_HPP
#define UTIL_HPP
//#include <QByteArray>

#include <tears.hpp>


namespace Tears
{
/** @defgroup util Utility functions
 * @brief Utility functions used throughout the codebase
 * @details The toChar()/toConstUnsignedChar() methods that just do a
 * reinterpret are used because it enables better auto-completion in text
 * editors / IDEs.
 *
 * @{
 */

/**
 * @brief Initializes library functions
 * @details Should be called once per application run to allow defaults to be selected.
 */
TEARS_EXPORT
void initialize_tears();


/**
 * @brief Reinterpretation of in
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
TEARS_EXPORT
char* toChar(unsigned char* in);

/**
 * @brief Reinterpretation of in
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
TEARS_EXPORT
const unsigned char* toConstUnsignedChar(const char* in);

/**
 * @brief Reinterpretation of in
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
TEARS_EXPORT
const char* toConstChar(const unsigned char* in);

/**
 * @brief Reinterpretation of in
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
TEARS_EXPORT
unsigned char* toUnsignedChar(char* in);

/**
 * @brief Copies length from buffer to a QByteArray
 * @param data
 * @param length Number of chars to copy from data.
 * @return QByteArray with first length bytes from data.
 */
TEARS_EXPORT
QByteArray toQByteArray(const unsigned char* data, const size_t length);

/**
 * @brief Prevents the data of the ByteArray from being swapped to disk.
 * @details If the data is deep-copied or reallocated then it may still be swapped.
 * @param data
 * @return true if no error.
 */
TEARS_EXPORT
bool lockMemory(const QByteArray &data);

/**
 * @brief Allows the data of the ByteArray to be swapped to disk again.
 *
 * @param data
 * @return true if no error.
 */
TEARS_EXPORT
bool unlockMemory(const QByteArray &data);

/**@}*/
} // End of Tears NS
#endif // UTIL_HPP
