#include "tears.hpp"
#include "tears/hashing.hpp"
#include <sodium.h>
#include <sodium/crypto_auth_hmacsha256.h>

namespace Tears
{

Hashing::Hashing(QObject *parent) :
    QObject(parent)
{
}

QByteArray Hashing::PBKDF2_SHA256_easy(const QString &password, const QByteArray &salt, const size_t &count, const size_t &dkLen)
{
    QByteArray buffer;
    buffer.resize(dkLen);

    return Hashing::PBKDF2_SHA256( password.toUtf8(), salt, count, dkLen, buffer);
}

QByteArray Hashing::PBKDF2_SHA256(const QByteArray &key, const QByteArray &saltin, const quint64 &count, const quint64 &dkLen, QByteArray &buffer)
{
    static const QByteArray failure = "";
    crypto_auth_hmacsha256_state context;
    crypto_auth_hmacsha256_state hmacContext;
    size_t i = 0,  j, k, clen;
    const qint8 bufLen = 32;
    const qint8 internalSaltLen = 4;
    quint8 internalSalt[internalSaltLen];
    quint8 Ubuf[bufLen];
    quint8 Tbuf[bufLen];
    size_t keyLength = key.length();
    size_t saltLength = saltin.length();
    const quint8 * pkey = toConstUnsignedChar(key.constData());
    const quint8 * psalt = toConstUnsignedChar(saltin.constData());

    if((size_t)buffer.size() != dkLen)
    {
        return failure;
    }
    // Initial seed
    crypto_auth_hmacsha256_init(&context, pkey, keyLength);
    crypto_auth_hmacsha256_update(&context, psalt, saltLength);


    while((i*bufLen) < dkLen)
    {
        internalSalt[0] = ((i+1) >> 24) & 0xff;
        internalSalt[1] = ((i+1) >> 16) & 0xff;
        internalSalt[2] = ((i+1) >> 8) & 0xff;
        internalSalt[3] = (i+1) & 0xff;

        memcpy(&hmacContext, &context, sizeof(crypto_auth_hmacsha256_state));
        crypto_auth_hmacsha256_update(&hmacContext, internalSalt, 4);
        crypto_auth_hmacsha256_final(&hmacContext, Ubuf);

        memcpy(Tbuf, Ubuf, bufLen);
        for(j=1; j<count; ++j)
        {
            crypto_auth_hmacsha256_init(&hmacContext, pkey, keyLength);
            crypto_auth_hmacsha256_update(&hmacContext, Ubuf, bufLen);
            crypto_auth_hmacsha256_final(&hmacContext, Ubuf);

            for(k=0; k<bufLen;++k)
            {
                Tbuf[k] ^= Ubuf[k];
            }
        }

        clen = dkLen - i*bufLen;
        if(clen > bufLen)
        {
            clen = bufLen;
        }
        memcpy(toUnsignedChar(buffer.data())+ i*bufLen , Tbuf, clen);

        ++i;
    }

    sodium_memzero( &context, sizeof(crypto_auth_hmacsha256_state) );//*/
    return buffer;
}

} // End of Tears NS
