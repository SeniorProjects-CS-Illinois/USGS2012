#include <QtTest/QtTest>

class ExampleTestClass : public QObject
{
    Q_OBJECT
    private slots:
    void testCase();
};

void ExampleTestClass::testCase()
{
    QVERIFY(1 == 1);
}

QTEST_MAIN(ExampleTestClass)
#include "exampleTestClass.moc"
