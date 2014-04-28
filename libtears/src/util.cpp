#include <sodium.h>
#include "tears/util.hpp"
#include <QByteArray>

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

bool lockMemory(const QByteArray &data, CryptoFlags flags)
{
    if(flags == NoLockMemory)
    {
        return true;
    }

    // Return true if flag is not equal to FailOnLockFailure
    return sodium_mlock((void*const)data.constData(), data.length()) == TEARS_SODIUM_SUCCESS
            || flags != FailOnLockFailure;
}

bool unlockMemory(const QByteArray &data, CryptoFlags flags)
{
    if(flags == NoLockMemory)
    {
        return true;
    }

    return sodium_munlock((void*const)data.constData(), data.length()) == TEARS_SODIUM_SUCCESS
            || flags != FailOnLockFailure;
}

} // End of Tears NS
