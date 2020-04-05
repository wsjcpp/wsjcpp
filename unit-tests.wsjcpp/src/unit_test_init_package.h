#ifndef UNIT_TEST_INIT_PACKAGE_H
#define UNIT_TEST_INIT_PACKAGE_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestInitPackage : public WsjcppUnitTestBase {
    public:
        UnitTestInitPackage();
        virtual void init();
        virtual bool run();
};

#endif // UNIT_TEST_INIT_PACKAGE_H

