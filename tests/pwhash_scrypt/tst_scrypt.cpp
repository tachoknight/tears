#include <QString>
#include <QtTest>
#include <tears.hpp>
extern "C" {
#include <sodium.h>

}
class ScryptTest : public QObject
{
    Q_OBJECT

public:
    ScryptTest();

private Q_SLOTS:
    void scrypt();

    /**
     * @brief sodiumScrypt
     * @see https://www.tarsnap.com/scrypt/scrypt.pdf
     */
    void sodiumScrypt();

    void scrypt_data();
    void sodiumScrypt_data();
};

ScryptTest::ScryptTest()
{
}

void ScryptTest::scrypt()
{
    QByteArray salt = QByteArray::fromBase64("r3NwF6eie3/DBcDpmP/iLPfil+y+Ve500OGcpxZBhOw=");
    QFETCH(QByteArray, expected);
    QString password = "-=30\\X&x.OA}nrcw}Q1^Wq% ,r+:A_&2m)>18k5O";
    QFETCH(size_t, memLimit);
    QFETCH(size_t, opsLimit);
    QFETCH(size_t, outLen);

    QByteArray actual;
    QBENCHMARK {
        actual = Tears::Hashing::pwhash_scrypt(outLen, password, salt, memLimit, opsLimit);
    }

    // Uncomment next line if adding more data to this test (and you're interested in reproducibility)
    //qDebug()<<actual.toBase64();
    QVERIFY2(actual.isEmpty() == false, "pwhash_scrypt failed.");
    QVERIFY2((size_t)actual.length() == outLen, "pwhash_scrypt output is not of expected length");

    // Comment the next line if only interested in benchmarking
    QVERIFY(expected == actual);
}

void ScryptTest::sodiumScrypt()
{
    /*QFETCH(QByteArray, password);
    QFETCH(QByteArray, salt);
    QFETCH(QByteArray, expected);
    QFETCH(size_t, N);
    QFETCH(size_t, r);
    QFETCH(size_t, p);
    QFETCH(size_t, outLen);
    QByteArray buffer;
    buffer.resize(outLen);
    QVERIFY((size_t)buffer.length() == outLen);
    int ret = 0;

    ret = crypto_pwhash_scrypt_ll(
                reinterpret_cast<const uint8_t*>(password.constData()), (size_t)password.length(),
                reinterpret_cast<const uint8_t*>(salt.constData()), (size_t)salt.length(),
                (uint64_t)N, (uint32_t)r, (uint32_t)p,
                reinterpret_cast<uint8_t*>(buffer.data()), (size_t)buffer.length());

    QVERIFY(ret == 0);
    QVERIFY(expected == buffer);//*/
}

void ScryptTest::scrypt_data()
{
    QSKIP("We don't really need to benchmark everything every time (Will makes Travis builds take too long eventually)");
    size_t MiB = 1024*1024;
    size_t baseOps = 32768ul / 8ul;
    size_t baseMem = 16ul * MiB;
    size_t baseOut = Tears::Crypto::secretBoxKeyBytes;

    QTest::addColumn<QByteArray>("expected");
    QTest::addColumn<size_t>("memLimit");
    QTest::addColumn<size_t>("opsLimit");
    QTest::addColumn<size_t>("outLen");

    QTest::newRow("baseline")
            << QByteArray::fromBase64("BBW4MMuLDYv4Lqv16dfsDonB+agJ1aLpqMyMJGuAO6o=")
            << baseMem
            << baseOps
            << baseOut;

    QTest::newRow("double memory")
            << QByteArray::fromBase64("sBYidutpxjqVXqHMDyb4J+5GYL++wDChPXIlsrWgNIo=")
            << 2 * baseMem
            << baseOps
            << baseOut;

    QTest::newRow("double ops")
            << QByteArray::fromBase64("fYjdkW7m7u84hjypcun/3PySBWqlpsPp+Vl5ylwF/OY=")
            << baseMem
            << 2*baseOps
            << baseOut;

    QTest::newRow("double ops & mem")
            << QByteArray::fromBase64("q7IRVnZX7Q4vnAsqKUHoYCPtQzPc/Roy2vcyOvuW6FI=")
            << 2*baseMem
            << 2*baseOps
            << baseOut;

    QTest::newRow("quad ops & double mem")
            << QByteArray::fromBase64("5I3bQCNvfRI10pcqWI0dF7GvVoI+T6s0EhKxUDC16XM=")
            << 2*baseMem
            << 4*baseOps
            << baseOut;

    QTest::newRow("dual output, quad ops & double mem")
            << QByteArray::fromBase64("5I3bQCNvfRI10pcqWI0dF7GvVoI+T6s0EhKxUDC16XO5kLmvC8X3eTXX9Dt0WQrCySO3pAbneoQ1wgNDRpIhnA==")
            << 2*baseMem
            << 4*baseOps
            << 2*baseOut;

    QTest::newRow("8x ops & double mem")
            << QByteArray::fromBase64("b5AYAvEbhoAwAYkqArdOdHEOXu5cOCWQLM1v+sItO/U=")
            << 2*baseMem
            << 8*baseOps
            << baseOut;
}


void ScryptTest::sodiumScrypt_data()
{
    QSKIP("Low level scrypt access not implemented in 0.5");
    QTest::addColumn<QByteArray>("password");
    QTest::addColumn<QByteArray>("salt");
    QTest::addColumn<QByteArray>("expected");
    QTest::addColumn<size_t>("N");
    QTest::addColumn<size_t>("r");
    QTest::addColumn<size_t>("p");
    QTest::addColumn<size_t>("outLen");

    unsigned char expected1[] = {
        0x77, 0xd6, 0x57, 0x62, 0x38, 0x65, 0x7b, 0x20, 0x3b, 0x19, 0xca, 0x42, 0xc1, 0x8a, 0x04, 0x97,
        0xf1, 0x6b, 0x48, 0x44, 0xe3, 0x07, 0x4a, 0xe8, 0xdf, 0xdf, 0xfa, 0x3f, 0xed, 0xe2, 0x14, 0x42,
        0xfc, 0xd0, 0x06, 0x9d, 0xed, 0x09, 0x48, 0xf8, 0x32, 0x6a, 0x75, 0x3a, 0x0f, 0xc8, 0x1f, 0x17,
        0xe8, 0xd3, 0xe0, 0xfb, 0x2e, 0x0d, 0x36, 0x28, 0xcf, 0x35, 0xe2, 0x0c, 0x38, 0xd1, 0x89, 0x06
    };
    QByteArray expected = QByteArray( reinterpret_cast<char*>(expected1), 64);
    QTest::newRow("#1")
            << QByteArray("")
            << QByteArray("")
            << expected
            << 16ul << 1ul << 1ul << 64ul;

    unsigned char expected2[] = {
        0xfd, 0xba, 0xbe, 0x1c, 0x9d, 0x34, 0x72, 0x00, 0x78, 0x56, 0xe7, 0x19, 0x0d, 0x01, 0xe9, 0xfe,
        0x7c, 0x6a, 0xd7, 0xcb, 0xc8, 0x23, 0x78, 0x30, 0xe7, 0x73, 0x76, 0x63, 0x4b, 0x37, 0x31, 0x62,
        0x2e, 0xaf, 0x30, 0xd9, 0x2e, 0x22, 0xa3, 0x88, 0x6f, 0xf1, 0x09, 0x27, 0x9d, 0x98, 0x30, 0xda,
        0xc7, 0x27, 0xaf, 0xb9, 0x4a, 0x83, 0xee, 0x6d, 0x83, 0x60, 0xcb, 0xdf, 0xa2, 0xcc, 0x06, 0x40
    };
    expected = QByteArray( reinterpret_cast<char*>(expected2), 64);
    QTest::newRow("#2")
            << QByteArray("password")
            << QByteArray("NaCl")
            << expected
            << 1024ul << 8ul << 16ul << 64ul;

    unsigned char expected3[] = {
        0x70, 0x23, 0xbd, 0xcb, 0x3a, 0xfd, 0x73, 0x48, 0x46, 0x1c, 0x06, 0xcd, 0x81, 0xfd, 0x38, 0xeb,
        0xfd, 0xa8, 0xfb, 0xba, 0x90, 0x4f, 0x8e, 0x3e, 0xa9, 0xb5, 0x43, 0xf6, 0x54, 0x5d, 0xa1, 0xf2,
        0xd5, 0x43, 0x29, 0x55, 0x61, 0x3f, 0x0f, 0xcf, 0x62, 0xd4, 0x97, 0x05, 0x24, 0x2a, 0x9a, 0xf9,
        0xe6, 0x1e, 0x85, 0xdc, 0x0d, 0x65, 0x1e, 0x40, 0xdf, 0xcf, 0x01, 0x7b, 0x45, 0x57, 0x58, 0x87
    };
    expected = QByteArray( reinterpret_cast<char*>(expected3), 64);
    QTest::newRow("#3")
            << QByteArray("pleaseletmein")
            << QByteArray("SodiumChloride")
            << expected
            << 16384ul << 8ul << 1ul << 64ul;

    unsigned char expected4[] = {
        0x21, 0x01, 0xcb, 0x9b, 0x6a, 0x51, 0x1a, 0xae, 0xad, 0xdb, 0xbe, 0x09, 0xcf, 0x70, 0xf8, 0x81,
        0xec, 0x56, 0x8d, 0x57, 0x4a, 0x2f, 0xfd, 0x4d, 0xab, 0xe5, 0xee, 0x98, 0x20, 0xad, 0xaa, 0x47,
        0x8e, 0x56, 0xfd, 0x8f, 0x4b, 0xa5, 0xd0, 0x9f, 0xfa, 0x1c, 0x6d, 0x92, 0x7c, 0x40, 0xf4, 0xc3,
        0x37, 0x30, 0x40, 0x49, 0xe8, 0xa9, 0x52, 0xfb, 0xcb, 0xf4, 0x5c, 0x6f, 0xa7, 0x7a, 0x41, 0xa4
    };
    expected = QByteArray( reinterpret_cast<char*>(expected4), 64);
    QTest::newRow("#4")
            << QByteArray("pleaseletmein")
            << QByteArray("SodiumChloride")
            << expected
            << 1048576ul << 8ul << 1ul << 64ul;
}
QTEST_APPLESS_MAIN(ScryptTest)

#include "tst_scrypt.moc"
