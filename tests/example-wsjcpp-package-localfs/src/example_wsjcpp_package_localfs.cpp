#include "example_wsjcpp_package_localfs.h"

// ---------------------------------------------------------------------
// ExampleWsjcppPackageLocalFs

ExampleWsjcppPackageLocalFs::ExampleWsjcppPackageLocalFs() {
  // nothing          
}

// ---------------------------------------------------------------------

void ExampleWsjcppPackageLocalFs::setValue(const std::string &sValue) {
  m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string ExampleWsjcppPackageLocalFs::getValue() {
  return m_sValue;
}