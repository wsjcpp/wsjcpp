#include "example_wsjcpp_package_https.h"

// ---------------------------------------------------------------------
// ExampleWsjcppPackageHttps

ExampleWsjcppPackageHttps::ExampleWsjcppPackageHttps() {
  // nothing          
}

// ---------------------------------------------------------------------

void ExampleWsjcppPackageHttps::setValue(const std::string &sValue) {
  m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string ExampleWsjcppPackageHttps::getValue() {
  return m_sValue;
}