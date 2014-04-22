#ifndef UTIL_HPP
#define UTIL_HPP
//#include <QByteArray>

#include <tears.hpp>

namespace Tears
{
/**
 * @brief initalize_tears Initalizes library functions. Must be called once and only once per application run.
 */
TEARS_EXPORT void initialize_tears();


/**
 * @brief toUnsignedChar
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
TEARS_EXPORT char* toChar(unsigned char* in);

/**
 * @brief toConstUnsignedChar
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
TEARS_EXPORT const unsigned char* toConstUnsignedChar(const char* in);

/**
 * @brief toConstUnsignedChar
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
TEARS_EXPORT const char* toConstChar(const unsigned char* in);

/**
 * @brief toUnsignedChar
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
TEARS_EXPORT unsigned char* toUnsignedChar(char* in);

/**
 * @brief toQByteArray Copies length from buffer to a QByteArray
 * @param data
 * @param length Length to copy from data.
 * @return First length bytes from data.
 */
TEARS_EXPORT QByteArray toQByteArray(const unsigned char* data, const size_t length);

TEARS_EXPORT bool noVirtualMemory(const QByteArray &data);

} // End of Tears::Util NS
#endif // UTIL_HPP
