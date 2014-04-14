#ifndef TEARSCRYPTO_HPP
#define TEARSCRYPTO_HPP

//#include <QByteArray>
#include <tears.hpp>

namespace Tears
{
class Crypto
{
 public:
    Crypto();

    /**
     * @brief secretBox
     * @param data
     * @param nonce Length must be crypto_stream_KEYBYTES.
     * @param key Length must be crypto_stream_KEYBYTES.
     * @return Empty array on failure. Failure conditions include: wrong length of key or nonce, failure of underlying sodium function.
     */
    static QByteArray secretBox(const QByteArray &data, const QByteArray &nonce, const QByteArray &key);

    /**
     * @brief secretBoxOpen Decrypts the data put in to
     * @param data
     * @param nonce
     * @param key
     * @return Empty array on failure. Failure conditions include: wrong length of key or nonce, failure of underlying sodium function, message tampering.
     */
    static QByteArray secretBoxOpen(const QByteArray &data, const QByteArray &nonce, const QByteArray &key);

    /**
     * @brief secretBoxNonce
     * @return A random nonce that can be used in secretBox(). NaCl documentation considered the length sufficient for it not to risk being non-unique.
     */
    static const QByteArray secretBoxNonce();

    /**
     * @brief secretBoxKey
     * @return Generates a random key that can be used in secretBox().
     */
    static const QByteArray secretBoxKey();

    /**
     * @brief getRandom
     * @param size
     * @return A byte array of size containing cryptographically secure random bytes.
     */
    static const QByteArray getRandom(size_t size);

    /**
     * @brief wipe Securely wipes the data of the input.
     * @param data
     */
    static void wipe(QByteArray &data);

private:
    /**
     * @brief printBinary Internal debugging function that prints a binary buffer.
     * @param bin
     * @param binLength
     */
    static void printBinary(const unsigned char *bin, const size_t binLength);
};

}
#endif // TEARSCRYPTO_HPP
