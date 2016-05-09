#ifndef Rabin_h
#define Rabin_h
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "BigNumber.hpp"

/*
 caculate (base ^ power) % modulo
 */
BigNumber pow_mod(BigNumber base, BigNumber power, BigNumber modulo);

/*
 key generation phase
 Generate 128-bits number
*/
BigNumber generate_number(int len);

/*
 key generation phase
 Check if the number generated is prime
*/
bool is_prime(BigNumber input);

/*
 key generation phase
 generate private key which is 128-bit prime number
*/
BigNumber generate_prime_number(int len);

/*
 encryptytion
 padding duplicate bit with plainttext
*/
BigNumber padding(BigNumber input, int padding_len);

/*
 encryptytion
 use public key to encrypt plaintext with Rabin cryptosystem
*/
BigNumber encrypt(BigNumber public_key, BigNumber plaintext, int padding_len);

/*
 decryption
 use extend eculidean algorithm to find a, b s.t ap + bq = gcd(p,q)
*/
std::vector<BigNumber> extend_eculidean(BigNumber p, BigNumber q);

/*
 decryption
 find 4 square roots of input
*/
std::vector<BigNumber> find_root(BigNumber p, BigNumber q, BigNumber input);

/*
 decryption
 find which square root have been padded with duplicate digit
 ex: 1234ab34ab <- 1234ab + 34ab
 */
bool check_padding(BigNumber input, int padding_len);

/*
 decryption
 discard duplicate digit with known padding length
 ex: 1234ab34ab -> 1234ab
*/
BigNumber drop_padding(BigNumber input, int padding_len);

/*
 decryption
 use two private key to decrypt ciphertext
*/
BigNumber decrypt(BigNumber cipher, BigNumber p, BigNumber q, int padding_len);

#endif /* Rabin_h */
