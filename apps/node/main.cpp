#include <iostream>

#include "datalink/version.hpp"
#include "net/version.hpp"

int main() {
  std::cout << "datalink " << datalink::version() << '\n'
            << "net " << net::version() << '\n';
  return 0;
}
