#ifndef TEARSCRYPTO_HPP
#define TEARSCRYPTO_HPP

#include <tears.hpp>

/** @defgroup asymenc Authenticated Symmetric Key Encryption
 * @brief Methods used for Authenticated Symmetric Key Encryption
 * @details Authenticated Symmetric Key Encryption is a
 * form of [Symmetric Key](https://en.wikipedia.org/wiki/Symmetric-key_algorithm)
 * encryption that has the benefits of
 * [Authenticated Encryption](https://en.wikipedia.org/wiki/Authenticated_encryption).
 * Which means that it provides:
 * - confidentiality
 * - integrity
 * - authentication
 * of the encrypted data.
 *
 **/
namespace Tears
{
class TEARS_EXPORT Crypto
{
 public:
    Crypto();

    /**
     * @brief Encrypts and authenticates the data.
     * @details The length of nonce and key must be of correct size. Tears provide secretBoxKey() and
     * secretBoxNonce() to generate these. The required lengths can be a accessed using
     * Tears::Crypto::secretBoxKeyBytes and \a Tears::Crypto::secretBoxNonceBytes.
     *
     * Failure conditions include:
     * - wrong length of key or nonce
     * - failure of underlying sodium function.
     *
     * @ingroup asymenc
     * @param data Data to be encrypted and authenticated
     * @param nonce The nonce used to authenticate the data
     * @param key The key used to encrypt the data
     * @return Empty array on failure.
     */
    static QByteArray secretBox(const QByteArray &data, const QByteArray &nonce, const QByteArray &key);

    /**
     * @brief Decrypts the output from secretbox.
     * @details This function may fail for the following reasons:
     * - message tampering (failed authentication)
     * - wrong length of key or nonce
     * - failure of underlying sodium function
     *
     * @ingroup asymenc
     * @param data The encrypted data from secretbox
     * @param nonce The nounce used to encrypt the data
     * @param key The key used to encrypt the data
     * @return Empty array on failure.
     */
    static QByteArray secretBoxOpen(const QByteArray &data, const QByteArray &nonce, const QByteArray &key);

    /**
     * @brief Gets a nonce for use in secretbox()
     * @details NaCl documentation considered the length of the returned nounce
     * sufficient for it not to risk being non-unique. You could also implement
     * a counter of length \a Tears::Crypto::secretBoxNonceBytes. If you do use a count you
     * need to ensure that the nonce is unique for all encryptions with the
     * same key.
     *
     * @ingroup asymenc
     * @return A random nonce with a size of \a Tears::Crypto::secretBoxNonceBytes.
     */
    static const QByteArray secretBoxNonce();

    /**
     * @brief Generates a random key that can be used in secretBox().
     * @details The key is of length Tears::Crypto::secretBoxKeyBytes.
     * @ingroup asymenc
     * @return An empty array on failure.
     */
    static const QByteArray secretBoxKey();

    /**
     * @brief Gets size amount of random bytes
     * @param size
     * @return A byte array of size containing cryptographically secure random bytes.
     */
    static const QByteArray getRandom(size_t size);

    /**
     * @brief Securely wipes the data of the input.
     * @param data
     */
    static void wipe(QByteArray &data);

    /****************************************************
     *
     *      CONSTANTS
     *
     ****************************************************/

    /**
     * @brief The number of bytes for a secretBox nonce
     * @ingroup asymenc
     */
    static const quint32 secretBoxNonceBytes = crypto_secretbox_NONCEBYTES;

    /**
     * @brief The number of bytes for a secretBox key
     * @ingroup asymenc
     */
    static const quint32 secretBoxKeyBytes = crypto_secretbox_KEYBYTES;

private:
    /**
     * @brief Internal debugging function that prints a binary buffer.
     * @param bin
     * @param binLength
     */
    static void printBinary(const unsigned char *bin, const size_t binLength);
};

}
#endif // TEARSCRYPTO_HPP
