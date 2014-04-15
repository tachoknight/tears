#ifndef PASSWORDHASHING_HPP
#define PASSWORDHASHING_HPP

#include <QObject>
#include <sodium/crypto_auth_hmacsha256.h>
namespace Tears
{
class Hashing : public QObject
{
    Q_OBJECT
public:
    explicit Hashing(QObject *parent = 0);

    /**
     * @brief PBKDF2_SHA256 A Password Based Key Derivation Function using HMAC-SHA256.
     * @details { This is fairly cheap to implement in hardware. For increased security choose scrypt instead. }
     * @param password
     * @param salt More than 64 bits.
     * @param Count the number of hashing itterations. More secure the more rounds since the amount of work needed to brute-force a hash increases. NIST recommends at least a 1000.... so better make it 10 000 or more!
     * @param dkLen The size of the derived key. Max 32 * (2^32 - 1).
     * @return An array of length dkLen or 0 if something failed.
     */
    static QByteArray PBKDF2_SHA256_easy(const QString &password, const QByteArray &salt, const size_t &count, const size_t &dkLen);

    static QByteArray PBKDF2_SHA256(const QByteArray &key, const QByteArray &salt, const quint64 &count, const quint64 &dkLen, QByteArray &buffer);

private:
signals:

public slots:

};


} // End of Tears NS
#endif // PASSWORDHASHING_HPP
