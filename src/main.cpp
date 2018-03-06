#include "Timer.h"
//#include <iostream>


/*
int main() {
    Address addr(Ipv4::any(), Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(std::make_shared<HelloHandler>());
  server.serve();
}
*/

int main()
{

  Timer time;
  std::array<char, 4> arr = { 'a','b','c','d' };

  //time.debugSetToDisplay(arr);
 /* time.start();
  std::cin.get();
  time.stop();
  std::cin.get();
  time.start();
  std::cin.get();
  time.stop();*/
  std::cin.get();
  return 0;
}


