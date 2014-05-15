#include "tears.hpp"
#include "tears/util.hpp"
#include <QDebug>
#include <limits>

/* this was missing in my systems sodium implementation (probably due to master branch being six months ahead of a release)
 TODO: remove these lines once a version of Sodium that exports the constants is available */
#ifndef crypto_secretbox_MACBYTES
#define crypto_secretbox_xsalsa20poly1305_MACBYTES (crypto_secretbox_xsalsa20poly1305_ZEROBYTES - crypto_secretbox_xsalsa20poly1305_BOXZEROBYTES)
#define crypto_secretbox_MACBYTES crypto_secretbox_xsalsa20poly1305_MACBYTES
#endif

namespace Tears
{

using namespace Tears;

Crypto::Crypto()
{
}

QByteArray Crypto::secretBox(const QByteArray &data, const QByteArray &nonce, const QByteArray &key)
{
    static QByteArray failure = "";

    // Verify pre-conditions
    if((size_t)key.size() != Crypto::secretBoxKeyBytes)
    {
        qDebug() <<"Crypto::secretBox() failed due to key size preconditions.";
        return failure;
    }
    else if((size_t)nonce.length() != Crypto::secretBoxNonceBytes)
    {
        qDebug() <<"Crypto::secretBox() failed due to nounce size preconditions.";
        return failure;
    }
    else if((size_t)data.length() > std::numeric_limits<std::size_t>::max() - crypto_secretbox_ZEROBYTES)
    {
        qDebug() <<"Crypto::secretBox() failed due to data length preconditions.";
        return failure;
    }
    const unsigned char *n = toConstUnsignedChar(nonce.constData());
    const unsigned char *k = toConstUnsignedChar(key.constData());

    size_t boxedLen = data.length()+crypto_secretbox_ZEROBYTES;
    QByteArray cipherText;
    cipherText.resize(boxedLen);

    // Copy message to buffer after required zero bytes
    QByteArray message;
    message = data.rightJustified(boxedLen, '\0');
    if((size_t)message.length() != boxedLen || (size_t)cipherText.length() != boxedLen)
    {
        qDebug() << "Crypto::secretBox() failed to allocate sufficient memory";
        return failure;
    }
    // Satisfy ZEROBYTES precondition
    sodium_memzero(message.data(), crypto_secretbox_ZEROBYTES);
    sodium_memzero(cipherText.data(), crypto_secretbox_ZEROBYTES);

    int result = crypto_secretbox(toUnsignedChar(cipherText.data()),
                                  toConstUnsignedChar(message.constData()),
                                  boxedLen, n, k);

    // Don't leave our buffer in memory
    wipe(message);

    if(result != TEARS_SODIUM_SUCCESS)
    {
        qDebug() <<"Crypto::secretBox() failed due to crypto_secretbox()";
        return failure;
    }

    cipherText = cipherText.remove(0, crypto_secretbox_BOXZEROBYTES);
    return cipherText;
}

QByteArray Crypto::secretBoxOpen(const QByteArray &data, const QByteArray &nonce, const QByteArray &key)
{
    static QByteArray failure = "";

    // Verify pre-conditions
    if((size_t)key.size() != Crypto::secretBoxKeyBytes)
    {
        qDebug() <<"Crypto::secretBoxOpen() failed due to key not being of size:"
                <<  Crypto::secretBoxKeyBytes;
        return failure;
    }
    else if((size_t)nonce.length() != Crypto::secretBoxNonceBytes)
    {
        qDebug() <<"Crypto::secretBoxOpen() failed due to nounce not being of size:"
                << Crypto::secretBoxNonceBytes;
        return failure;
    }
    else if((size_t)data.length() > (size_t)std::numeric_limits<std::size_t>::max()-crypto_secretbox_BOXZEROBYTES
            || (size_t)data.length() < crypto_secretbox_MACBYTES)
    {
        qDebug() <<"Crypto::secretBoxOpen() failed due to data length preconditions.";
        return failure;
    }
    const unsigned char *n = toConstUnsignedChar(nonce.constData());
    const unsigned char *k = toConstUnsignedChar(key.constData());

    size_t boxedLen = data.length() + crypto_secretbox_BOXZEROBYTES;
    QByteArray cipherText(boxedLen, '\0');
    cipherText = data.rightJustified(boxedLen, '\0');
    if((size_t)cipherText.length() != boxedLen)
    {
        qDebug()<<"Crypto::secretBoxOpen ciphertext buffer could not be allocated.";
        return failure;
    }

    // Satisfy precondition
    sodium_memzero(cipherText.data(), crypto_secretbox_BOXZEROBYTES);

    QByteArray message(boxedLen+crypto_secretbox_MACBYTES, '\0');
    message.resize(boxedLen+crypto_secretbox_MACBYTES);

    if((size_t)message.length() != boxedLen+crypto_secretbox_MACBYTES)
    {
        qDebug()<<"Crypto::secretBoxOpen message buffer could not be allocated";
        return failure;
    }

    int result = crypto_secretbox_open(
                toUnsignedChar(message.data()),
                toConstUnsignedChar(cipherText.constData()),
                boxedLen, n, k);

    if(result != TEARS_SODIUM_SUCCESS)
    {
        qDebug() <<"Crypto::secretBoxOpen() failed due to crypto_secretbox_open()";
        return failure;
    }

    // return the last dataLength bytes and crop off zero bytes on the end
    return message.mid(crypto_secretbox_ZEROBYTES, data.length()-crypto_secretbox_MACBYTES);
}

const QByteArray Crypto::secretBoxNonce()
{
    return Crypto::getRandom(Crypto::secretBoxNonceBytes);
}

const QByteArray Crypto::secretBoxKey()
{
    QByteArray key = Crypto::getRandom(Crypto::secretBoxKeyBytes);
    return Tears::lockMemory(key.constData()) ? key:QByteArray();
}

const QByteArray Crypto::getRandom(size_t size)
{
    QByteArray data;
    data.resize(size);
    randombytes_buf(data.data(), size);
    return data;
}

void Crypto::wipe(QByteArray &data)
{
    sodium_memzero(data.data(), data.length());
}

void Crypto::wipe(QString &data)
{
    // QString doesn't have any way of accessing the memory directly :(
    data.fill('\0');
}

void Crypto::printBinary(const unsigned char *bin, const size_t binLength)
{
    char hex[2*binLength];
    sodium_bin2hex(hex, 2*binLength,bin, binLength);
    qDebug()<<hex;
}

} // End of Tears NS

