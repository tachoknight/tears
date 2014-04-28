#include <QString>
#include <QtTest>
#include <tears.hpp>

class BoxTest : public QObject
{
    Q_OBJECT

public:
    BoxTest();

private Q_SLOTS:
    void box();
};

BoxTest::BoxTest()
{
}

void BoxTest::box()
{
    QByteArray original = Tears::Crypto::getRandom(131);
    QByteArray nonce = Tears::PublicKeyCrypto::boxNonce();
    QByteArray cipherText, actual;
    QByteArray receiverPublic, receiverSecret, senderPublic, senderSecret;

    // Create keypairs
    QVERIFY2(Tears::PublicKeyCrypto::boxKeyPair(receiverPublic, receiverSecret), "Failed to generate receiver keypair");
    QVERIFY2(Tears::PublicKeyCrypto::boxKeyPair(senderPublic, senderSecret), "Failed to generate sender keypair");

    // Secure exchange of public keys omitted...

    cipherText = Tears::PublicKeyCrypto::box(original, nonce, receiverPublic, senderSecret);
    QVERIFY2(cipherText.length() != 0, "The result from box() was of length 0.");

    // Test decrypting
    actual = Tears::PublicKeyCrypto::boxOpen(cipherText, nonce, senderPublic, receiverSecret);
    QVERIFY2(actual.length() != 0, "The result from boxOpen() was of length 0");
    QVERIFY2(actual == original, "Comparison of plaintext and decrypted ciphertext was not equal");
}

QTEST_APPLESS_MAIN(BoxTest)

#include "tst_boxtest.moc"
