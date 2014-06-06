#include <QString>
#include <QtTest>
#include <tears.hpp>

class TearsPasswordHashTest : public QObject
{
    Q_OBJECT

public:
    TearsPasswordHashTest();

private Q_SLOTS:
    void singleTestVector();
    void rfcTestVectors();
    void rfcTestVectors_data();
};

TearsPasswordHashTest::TearsPasswordHashTest()
{
    Tears::initialize_tears();
}

void TearsPasswordHashTest::singleTestVector()
{
    QString password = "password";
    QByteArray salt = "salt";
    quint64 count = 1;
    quint64 dkLen = 32;
    QByteArray expected;
    static const unsigned char result[] = {
        0x12, 0x0f, 0xb6, 0xcf, 0xfc, 0xf8, 0xb3, 0x2c,
        0x43, 0xe7, 0x22, 0x52, 0x56, 0xc4, 0xf8, 0x37,
        0xa8, 0x65, 0x48, 0xc9, 0x2c, 0xcc, 0x35, 0x48,
        0x08, 0x05, 0x98, 0x7c, 0xb7, 0x0b, 0xe1, 0x7b
    };
    expected = expected.fromRawData(Tears::toConstChar(result), dkLen);

    QByteArray actual(dkLen, '\0');
    actual.resize(dkLen);
    QBENCHMARK{
        actual = Tears::Hashing::PBKDF2_SHA256(password, salt, count, dkLen);
    }
    QVERIFY2(actual.toBase64() == expected.toBase64(), "Binary comparison of result failed");
}

void TearsPasswordHashTest::rfcTestVectors()
{
    QFETCH(QString, password);
    QFETCH(QByteArray, salt);
    QFETCH(quint64, count);
    QFETCH(quint64, dkLen);
    QFETCH(QByteArray, expected);
    QByteArray actual;

    QBENCHMARK{
        actual = Tears::Hashing::PBKDF2_SHA256(password, salt, count, dkLen);
        QVERIFY2(actual == expected, "Failure");
    }
}

void TearsPasswordHashTest::rfcTestVectors_data()
{
    QTest::addColumn<QString>("password");
    QTest::addColumn<QByteArray>("salt");
    QTest::addColumn<quint64>("count");
    QTest::addColumn<quint64>("dkLen");
    QTest::addColumn<QByteArray>("expected");

    QByteArray expected;

    // From: https://stackoverflow.com/questions/5130513/pbkdf2-hmac-sha2-test-vectors
    static const unsigned char result0[] = {
        0x12, 0x0f, 0xb6, 0xcf, 0xfc, 0xf8, 0xb3, 0x2c,
        0x43, 0xe7, 0x22, 0x52, 0x56, 0xc4, 0xf8, 0x37,
        0xa8, 0x65, 0x48, 0xc9, 0x2c, 0xcc, 0x35, 0x48,
        0x08, 0x05, 0x98, 0x7c, 0xb7, 0x0b, 0xe1, 0x7b
    };
    expected = expected.fromRawData(Tears::toConstChar(result0), 32);
    QTest::newRow("0") << QString("password") << QByteArray("salt")
                       << (quint64)1 << (quint64)32
                       << expected;

    static const unsigned char result1[] = {
        0xae, 0x4d, 0x0c, 0x95, 0xaf, 0x6b, 0x46, 0xd3,
        0x2d, 0x0a, 0xdf, 0xf9, 0x28, 0xf0, 0x6d, 0xd0,
        0x2a, 0x30, 0x3f, 0x8e, 0xf3, 0xc2, 0x51, 0xdf,
        0xd6, 0xe2, 0xd8, 0x5a, 0x95, 0x47, 0x4c, 0x43
    };
    expected = expected.fromRawData(Tears::toConstChar(result1), 32);
    QTest::newRow("1") << QString("password") << QByteArray("salt")
                       << (quint64)2 << (quint64)32
                       << expected;

    static const unsigned char result2[] = {
        0xc5, 0xe4, 0x78, 0xd5, 0x92, 0x88, 0xc8, 0x41,
        0xaa, 0x53, 0x0d, 0xb6, 0x84, 0x5c, 0x4c, 0x8d,
        0x96, 0x28, 0x93, 0xa0, 0x01, 0xce, 0x4e, 0x11,
        0xa4, 0x96, 0x38, 0x73, 0xaa, 0x98, 0x13, 0x4a
    };
    expected = expected.fromRawData(Tears::toConstChar(result2), 32);
    QTest::newRow("2") << QString("password") << QByteArray("salt")
                       << (quint64)4096 << (quint64)32
                       << expected;

    static const unsigned char result3[] = {
        0xc5, 0xe4, 0x78, 0xd5, 0x92, 0x88, 0xc8, 0x41,
        0xaa, 0x53, 0x0d, 0xb6, 0x84, 0x5c, 0x4c, 0x8d,
        0x96, 0x28, 0x93, 0xa0, 0x01, 0xce, 0x4e, 0x11,
        0xa4, 0x96, 0x38, 0x73, 0xaa, 0x98, 0x13, 0x4a
    };
    expected = expected.fromRawData(Tears::toConstChar(result3), 32);
    QTest::newRow("3") << QString("password") << QByteArray("salt")
                       << (quint64)4096 << (quint64)32
                       << expected;

    static const unsigned char result4[] = {
        0x34, 0x8c, 0x89, 0xdb, 0xcb, 0xd3, 0x2b, 0x2f,
        0x32, 0xd8, 0x14, 0xb8, 0x11, 0x6e, 0x84, 0xcf,
        0x2b, 0x17, 0x34, 0x7e, 0xbc, 0x18, 0x00, 0x18,
        0x1c, 0x4e, 0x2a, 0x1f, 0xb8, 0xdd, 0x53, 0xe1,
        0xc6, 0x35, 0x51, 0x8c, 0x7d, 0xac, 0x47, 0xe9
    };
    expected = expected.fromRawData(Tears::toConstChar(result4), 40);
    QTest::newRow("4") << QString("passwordPASSWORDpassword") << QByteArray("saltSALTsaltSALTsaltSALTsaltSALTsalt")
                       << (quint64)4096 << (quint64)40
                       << expected;

    static const unsigned char result5[] = {
        0x89, 0xb6, 0x9d, 0x05, 0x16, 0xf8, 0x29, 0x89,
        0x3c, 0x69, 0x62, 0x26, 0x65, 0x0a, 0x86, 0x87
    };
    expected = expected.fromRawData(Tears::toConstChar(result5), 16);
    QTest::newRow("5") << QString::fromUtf8("pass\0word", 9) << QByteArray("sa\0lt", 5)
                       << (quint64)4096 << (quint64)16
                       << expected;

    // This one will take a long time...
///*
    static const unsigned char result6[] = {
        0xcf, 0x81, 0xc6, 0x6f, 0xe8, 0xcf, 0xc0, 0x4d,
        0x1f, 0x31, 0xec, 0xb6, 0x5d, 0xab, 0x40, 0x89,
        0xf7, 0xf1, 0x79, 0xe8, 0x9b, 0x3b, 0x0b, 0xcb,
        0x17, 0xad, 0x10, 0xe3, 0xac, 0x6e, 0xba, 0x46
    };
    expected = expected.fromRawData(Tears::toConstChar(result6), 32);
    QTest::newRow("6") << QString("password") << QByteArray("salt")
                       << (quint64)16777216 << (quint64)32
                       << expected;
    //*/
}

QTEST_APPLESS_MAIN(TearsPasswordHashTest)

#include "tst_pbkdf2hmacsha256.moc"
