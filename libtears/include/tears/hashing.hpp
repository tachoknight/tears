#ifndef PASSWORDHASHING_HPP
#define PASSWORDHASHING_HPP

#include <QObject>
#include <sodium.h>

/** @defgroup keygen Key Generation
 * @brief Methods that are used to generate keys for cryptographic functions.
 *
 */
namespace Tears
{
class Hashing : public QObject
{
    Q_OBJECT
public:
    explicit Hashing(QObject *parent = 0);

    /**
     * @brief A Password Based Key Derivation Function using HMAC-SHA256.
     * @ingroup keygen
     * @details This algorithm is fairly cheap to implement in hardware. For increased security in new applications choose
     * scrypt instead.
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
    static QByteArray PBKDF2_SHA256(const QString &password, const QByteArray &salt, const size_t &count, const size_t &dkLen);

    /**
     * @brief Used by the convenience wrapper PBKDF2_SHA256().
     * @details Also useful if you want to use arbitrary binary data as a password.
     * @ingroup keygen
     * @param key
     * @param salt
     * @param count
     * @param dkLen
     * @param buffer of size dkLen
     * @return
     */
    static QByteArray PBKDF2_SHA256_hard(const QByteArray &key, const QByteArray &salt, const quint64 &count, const quint64 &dkLen, QByteArray &buffer);

    /**
     * @brief A key derivation function using scrypt to generate a secret key.
     * @details We supply a benchmark test in the pwhash_scrypt test that you can use to test out different values for memLimit and opsLimit. Read the Scrypt PDF on the Tarsnap website for details.
     * @see https://www.tarsnap.com/scrypt.html
     * @param outLen The length of the resulting key.
     * @param password Will be converted to a Utf-8 bytearray
     * @param salt A salt of length Tears::Hashing::pwhash_scrypt_saltbytes
     * @param memLimit A doubling in memory limit roughly doubles the time (and also the memory) the key derivatinon takes. This should lead to increased cost to bruteforce passwords.
     * @param opsLimit A higher value decreases the the time the key derivation takes to run. A higher value makes more CPU bound requiring attackers to have more processing power.
     * @return A ByteArray of outLen or an empty array on failure
     **/
    static QByteArray pwhash_scrypt(size_t outLen, const QString &password, const QByteArray &salt, size_t memLimit, size_t opsLimit);

    /**********************
     *     CONSTANTS      *
     **********************/
    /**
     * @brief The required length of the salt
     */
    static const size_t pwhash_scrypt_saltbytes = crypto_pwhash_scryptsalsa208sha256_SALTBYTES;
private:
signals:

public slots:

};


} // End of Tears NS
#endif // PASSWORDHASHING_HPP
