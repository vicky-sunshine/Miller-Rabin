#include <stdio.h>
#include "Rabin.hpp"

// key generate
BigNumber generate_prime_number();
BigNumber generate_number();
bool is_prime(BigNumber input);

// encrypt
BigNumber padding(BigNumber input);
BigNumber encrypt(BigNumber plaintext);

// decrypt
BigNumber find_root(BigNumber input);
BigNumber decrypt(BigNumber cipher);
