#ifndef UTIL_HPP
#define UTIL_HPP
//#include <QByteArray>

#include <tears.hpp>

namespace Tears
{

/**
 * @brief initalize_tears Initalizes library functions. Must be called once and only once per application run.
 */
void initialize_tears();


/**
 * @brief toUnsignedChar
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
char* toChar(unsigned char* in);

/**
 * @brief toConstUnsignedChar
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
const unsigned char* toConstUnsignedChar(const char* in);

/**
 * @brief toConstUnsignedChar
 * @param in
 * @return Reinterprets in to a constant unsigned char *
 */
const char* toConstChar(const unsigned char* in);

/**
 * @brief toUnsignedChar
 * @param in
 * @return Reinterprets in to a unsigned char *
 */
unsigned char* toUnsignedChar(char* in);

/**
 * @brief toQByteArray Copies length from buffer to a QByteArray
 * @param data
 * @param length Length to copy from data.
 * @return First length bytes from data.
 */
QByteArray toQByteArray(const unsigned char* data, const size_t length);
}

bool noVirtualMemory(const QByteArray &data);
#endif // UTIL_HPP
