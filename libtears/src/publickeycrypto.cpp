#include "tears.hpp"
#include "tears/util.hpp"
#include <QDebug>
#include <limits>

namespace Tears
{

// Initialize QString static constants
const QString Tears::PublicKeyCrypto::boxPrimitive = QString(crypto_box_PRIMITIVE);

QByteArray PublicKeyCrypto::box(const QByteArray &data, const QByteArray &nonce, const QByteArray &publicKey, const QByteArray &secretKey)
{
    QByteArray key = boxBeforeNM(publicKey, secretKey);
    return boxAfterNM(data, nonce, key);
}

QByteArray PublicKeyCrypto::boxAfterNM(const QByteArray &data, const QByteArray &nonce, const QByteArray &key)
{
    if(key.length() != boxBeforeNMBytes)
    {
        qDebug()<< "PublicKeyCrypto::boxAfterNM failed due to key length";
        return QByteArray();
    }
    if(nonce.length() != boxNonceBytes)
    {
        qDebug()<< "PublicKeyCrypto::boxAfterNM failed due to nonce length";
        return QByteArray();
    }

    QByteArray message ;//= data.leftJustified(boxZeroBytes);
    message.resize(boxZeroBytes);
    message.insert(boxZeroBytes, data);
    unsigned char * msg = toUnsignedChar(message.data());
    sodium_memzero(msg, boxZeroBytes);

    QByteArray cipher;
    size_t clen = message.length();
    cipher.resize(clen);
    if((size_t)cipher.length() != clen)
    {
        qDebug()<< "PublicKeyCrypto::boxAfterNM failed to resize ciphertext buffer";
        return QByteArray();
    }
    unsigned char *ctxt = toUnsignedChar(cipher.data());
    int result = crypto_box_afternm(
                ctxt,
                (const unsigned char *)msg, message.length(),
                toConstUnsignedChar(nonce.constData()),
                toConstUnsignedChar(key.constData()));

    if(result == TEARS_SODIUM_SUCCESS)
    {
        // Skip box zero bytes
        return cipher.mid(boxBoxZeroBytes);
    }
    else
    {
        qDebug()<<"PublicKeyCrypto::boxAfterNM call to crypto_box_afternm() failed";
        return QByteArray();
    }
}

QByteArray PublicKeyCrypto::boxBeforeNM(const QByteArray &publicKey, const QByteArray &secretKey)
{
    if(publicKey.length() != boxPublicKeyBytes || secretKey.length() != boxSecretKeyBytes)
    {
        return QByteArray();
    }
    QByteArray key;
    key.resize(boxBeforeNMBytes);
    if(key.length() != boxBeforeNMBytes)
    {
        return QByteArray();
    }

    int result = crypto_box_beforenm(
                toUnsignedChar(key.data()),
                toConstUnsignedChar(publicKey.constData()),
                toConstUnsignedChar(secretKey.constData())
                );

    return (result == TEARS_SODIUM_SUCCESS)? key : QByteArray();
}

QByteArray PublicKeyCrypto::boxOpen(const QByteArray &encryptedData, const QByteArray nonce, const QByteArray &publicKey, const QByteArray &secretKey)
{
    QByteArray key = boxBeforeNM(publicKey, secretKey);
    return boxOpenAfterNM(encryptedData, nonce, key);
}

QByteArray PublicKeyCrypto::boxOpenAfterNM(const QByteArray &cipherData, const QByteArray &nonce, const QByteArray &key)
{
    if(key.length() != boxBeforeNMBytes)
    {
        qDebug()<< "PublicKeyCrypto::boxOpenAfterNM failed due to key length";
        return QByteArray();
    }
    if(nonce.length() != boxNonceBytes)
    {
        qDebug()<< "PublicKeyCrypto::boxOpenAfterNM failed due to nonce length";
        return QByteArray();
    }

    QByteArray ciphertext;
    ciphertext.resize(boxBoxZeroBytes);
    ciphertext.insert(boxBoxZeroBytes, cipherData);
    unsigned char * ctxt = toUnsignedChar(ciphertext.data());
    sodium_memzero(ctxt, boxBoxZeroBytes);

    QByteArray message;
    message.resize(ciphertext.length());
    if(message.length() != ciphertext.length())
    {
        qDebug()<< "PublicKeyCrypto::boxOpenAfterNM failed to allocate message buffer.";
        return QByteArray();
    }

    int result = crypto_box_open_afternm(
                toUnsignedChar(message.data()),
                ctxt, ciphertext.length(),
                toConstUnsignedChar(nonce.constData()),
                toConstUnsignedChar(key.constData())
                );
    if(result == TEARS_SODIUM_SUCCESS)
    {
        // Skip zero bytes
        return message.mid(boxZeroBytes);
    }
    else
    {
        qDebug()<< "PublicKeyCrypto::boxOpenAfterNM call to crypto_box_open_afternm() failed.";
        return QByteArray();
    }
}

bool PublicKeyCrypto::boxKeyPair(QByteArray &publicKey, QByteArray &secretKey, CryptoFlags flag)
{
    // Try to resize to sufficient size
    secretKey.resize(PublicKeyCrypto::boxSecretKeyBytes);
    publicKey.resize(PublicKeyCrypto::boxPublicKeyBytes);
    if(secretKey.length() != PublicKeyCrypto::boxSecretKeyBytes
            || PublicKeyCrypto::boxPublicKeyBytes != publicKey.length())
    {
        // Return if we failed
        return false;
    }

    int result = crypto_box_keypair(toUnsignedChar(publicKey.data()), toUnsignedChar(secretKey.data()));

    if (result != TEARS_SODIUM_SUCCESS)
    {
        return false;
    }

    return lockMemory(secretKey, flag);
}

QByteArray PublicKeyCrypto::boxNonce()
{
    return Crypto::getRandom(boxNonceBytes);
}


} // End of Tears NS

