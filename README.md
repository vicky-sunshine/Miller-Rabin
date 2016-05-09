# Rabin Crypto system

### Usage Example
```cpp
// Demo of generate prime number
// to save time, i have generated 2 results
// ex: 9b8793a5 444db5d0 eca12de3 a27edcab aaaabebd b6223d00 37928325 2a1b02b7
// ex: d43777d6 e6889b92 18ac0e3e 5b49dc9c 7a239937 bb47cdcd aea15bb5 52ad5c57
BigNumber prime_number = generate_prime_number(64); // 256 bits --> 64 digit hex number
std::cout << "256 bits prime number: " << prime_number << std::endl;

// Demo of Rabin crypto system
BigNumber plain("be000badbebadbadbad00debdeadfacedeafbeefadd00addbed00bed");
std::cout << "plaintext: " << plain << std::endl;

BigNumber p = BigNumber("daaefe652cad1614f17e87f2cd80973f");
std::cout << "private p: " << p << std::endl;

BigNumber q = BigNumber("f99988626723eef2a54ed484dfa735c7");
std::cout << "private q: " << q << std::endl;

BigNumber n = p * q;
std::cout << "public n: " << n << std::endl;

// Encryption
BigNumber cipher = encrypt(n, plain, 4);
std::cout << "cipher: " << cipher << std::endl;

// Decryption
BigNumber back = decrypt(p, q, cipher, 4);
std::cout << "plaintext: "<< back << std::endl;

```
