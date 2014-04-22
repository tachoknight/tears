#include <QObject>
#include <QTest>

#include "tears.hpp"
class TearstestCrypto : public QObject
{
    Q_OBJECT

public:
    TearstestCrypto();

private Q_SLOTS:
    void testEncryptDecryptQString();
    void testBigArray();
};


TearstestCrypto::TearstestCrypto()
{
    Tears::initialize_tears();
}

/**
 * @brief TearstestCrypto::testEncryptDecryptQString Initial test to show how the api works.
 */
void TearstestCrypto::testEncryptDecryptQString()
{
    // Test string is an excerpt from Hemsöborna by August Strindberg. Courtesy of project Gutenberg
    static const QString teststring = QString::fromUtf8("- Det är präktiga djur det här sa Carlsson och klämde dem över bröstet för att känna, om de voro feta. Han är en snäll skytt kan jag se, för skotten sitter på rätta stället.");
    QTest::addColumn<QString>("message");
    QTest::addColumn<QByteArray>("nonce");
    QTest::addColumn<QByteArray>("key");
    for(int i = 1; i < teststring.size(); ++i)
    {
        QString message = teststring.left(i);
        QByteArray nonce = Tears::Crypto::secretBoxNonce();
        QByteArray key = Tears::Crypto::secretBoxKey();

        QByteArray messageBytes = message.toUtf8();
        QByteArray afterBoxing = Tears::Crypto::secretBox(messageBytes, nonce, key);
        QVERIFY2(afterBoxing.length() != 0, "Null result returned on encryption using Crypto::secretBox()");

        QByteArray afterOpening = Tears::Crypto::secretBoxOpen(afterBoxing, nonce, key);

        QVERIFY2(afterOpening.length() != 0, "Null result returned on encryption using Crypto::secretBoxOpen()");
        QString actual(afterOpening);
        QVERIFY2(actual == message, "Error comparing before and after encryption");

        Tears::unlockMemory(key);
        Tears::Crypto::wipe(key);
    }
}

void TearstestCrypto::testBigArray()
{
    // 64 MB
    const QByteArray buffer = Tears::Crypto::getRandom(15);
    QByteArray nonce = Tears::Crypto::secretBoxNonce();
    QByteArray key = Tears::Crypto::secretBoxKey();
    QByteArray encrypted = Tears::Crypto::secretBox(buffer, nonce, key);
    QVERIFY2(encrypted.length() != 0, "Null result returned on encryption using Crypto::secretBox()");

    // Here encrypted changes to unencrypted...
    QByteArray decrypted = Tears::Crypto::secretBoxOpen(encrypted, nonce, key);
    QVERIFY2(decrypted.length() != 0, "Null result returned on encryption using Crypto::secretBox()");
    QVERIFY2(buffer == decrypted, "Comparison of large buffer failed after Crypto::secretBoxOpen()");

    Tears::unlockMemory(key);
    Tears::Crypto::wipe(key);
}

QTEST_APPLESS_MAIN(TearstestCrypto)

#include "tst_secretbox.moc"
