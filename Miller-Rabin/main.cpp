#include "Rabin.hpp"
#include "BigNumber.hpp"

int main(int argc, char** argv){

  // demo
  BigNumber p("daaefe652cad1614f17e87f2cd80973f");
  BigNumber q("f99988626723eef2a54ed484dfa735c7");
  BigNumber plain("be000badbebadbadbad00debdeadfacedeafbeefadd00addbed00bed0bed");
  BigNumber n = p * q;
  BigNumber plain2 = plain * plain;
  BigNumber cipher = plain2 % n;
  
  // BigNumber d = c % b;
  std::cout << "a * b = "<< n << std::endl;
  std::cout << "plain * plain = "<< plain2 << std::endl;
  std::cout << "plain * plain = "<< cipher << std::endl;

  
  return 0;
}
