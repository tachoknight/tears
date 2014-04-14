#include <sodium.h>
#include "tears/util.hpp"
#include <QByteArray>
#ifdef WINDOWS
#include <Windows.h>
#include <WinBase.h>
#else
#include <sys/mman.h>
#endif
namespace Tears
{

void initialize_tears()
{
    sodium_init();
}

char *toChar(unsigned char *in)
{
    return reinterpret_cast<char*>(in);
}

const unsigned char *toConstUnsignedChar(const char *in)
{
    return reinterpret_cast<const unsigned char*>(in);
}

const char *toConstChar(const unsigned char *in)
{
    return reinterpret_cast<const char*>(in);
}

unsigned char *toUnsignedChar(char *in)
{
    return reinterpret_cast<unsigned char*>(in);
}

QByteArray toQByteArray(const unsigned char *data, const size_t length)
{
    QByteArray output;
    output.resize(length);

    // Copy data if we could make it long enough.
    if((size_t)output.length() != length)
    {
        output.clear();
    }
     else
    {
        memcpy(output.data(), toConstChar(data), output.length());
    }
    return output;
}

}

/**
 * @brief noVirtualMemory Prevents the data of the ByteArray from being swapped to disk.
 * @param data
 * @return true if no error. Data must not be subject to any operations that may deep-copy, reallocate it or it may still be swapped.
 */
bool noVirtualMemory(const QByteArray &data)
{
#ifdef WINDOWS
    // TODO: Do something similar for Windows, VirtualLock()?
#else
    return mlock(data.constData(), data.length()) == 0;
#endif
}
