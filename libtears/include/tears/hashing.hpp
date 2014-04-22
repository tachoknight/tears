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
     *
     * @details This algorithm is fairly cheap to implement in hardware. For increased security choose scrypt instead.
     * However libtears is waiting for libsodium to release their implementation since it is a bit trickier to implement
     * than PBKDF2.
     *
     * The higher the count the more expensive it is to bruteforce since the amount of work needed to generate a key to
     * try in a bruteforce attack. Measure how many itterations it takes for a runtime of at least 0.2s on you lowest target
     * hardware (and no, don't target toasters...).
     *
     * @param password
     * @param salt More than 64 bits.
     * @param count The number of hashing itterations.
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
