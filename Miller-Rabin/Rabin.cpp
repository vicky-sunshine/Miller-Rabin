#include "Rabin.hpp"

/*
 caculate (base ^ power) % modulo
*/
BigNumber pow_mod(BigNumber base, BigNumber power, BigNumber modulo) {
  BigNumber sum = base;
  if  (power ==0) return 1;

  BigNumber odd(1);
  while (base!=1 && power>1){
    if (power % 2 != 0){ // odd
      odd = odd * base % modulo;
    }
    power = power / 2;
    base = base * base % modulo;
  }
  return base * odd % modulo;
}


/*
 key generation phase
 Generate 128-bits number
*/
BigNumber generate_number(int len) {
  std::string alphanum = "0123456789abcdef";
  std::string n;
  for (int i = 0; i < len; ++i) {
    n.push_back(alphanum[rand() % (alphanum.size() - 1)]);
  }

  return BigNumber(n);
}

/*
 key generation phase
 generate private key which is 128-bit prime number
*/
BigNumber generate_prime_number(int len) {

  BigNumber n = generate_number(len);
  while (!is_prime(n)) {
    n = generate_number(len);
  }
  return n;
}

/*
 key generation phase
 Check if the number generated is prime
*/
bool is_prime(BigNumber n){
    if (n < 2) return false;

    if (n != 2 && n % 2==0){
      return false;
    }
    BigNumber u = n - 1;
    BigNumber t = 0;
    while (u % 2 == 0) {
      u = u / 2;
      t = t + 1;
    }

    BigNumber a = rand() % (n - 1) + 1;
    BigNumber x = pow_mod(a, u, n);   // x = a ^ u % n;
    if (x == 1 || x == n - 1) return true;

    for (int i=0; i<t-1; i++)
    {
        x = x * x % n;   // x = x * x % n;
        if (x == 1) return false;
        if (x == n-1) return true;
    }
    return false;
}

/*
 encryptytion
 padding duplicate bit with plainttext
*/
BigNumber padding(BigNumber input, int padding_len) {

  std::string str = input.to_string();

  // padding tail of input
  // ex: 1234bd --> 1234bdbd (if padding 2 digit)
  str.append(str.end()-padding_len,str.end());

  return BigNumber(str);
}

/*
 encryptytion
 use public key to encrypt plaintext with Rabin cryptosystem
*/
BigNumber encrypt(BigNumber public_key, BigNumber plaintext, int padding_len) {
  // padding plaintext 16 bits ( 4 digit since it's hex0
  plaintext = padding(plaintext, padding_len);
  BigNumber cipher = plaintext * plaintext % public_key;

  return cipher;
}

/*
 decryption
 use extend eculidean algorithm to find a, b s.t ap + bq = gcd(p,q)
*/
std::vector<BigNumber> extend_eculidean(BigNumber a, BigNumber b) {
  BigNumber q,x,lastx,y,lasty,temp1,temp2,temp3;
  x=0;
  y=1;
  lastx=1;
  lasty=0;
  while (b!=0) {
    q= a/b;
    temp1= a%b;
    a=b;
    b=temp1;

    temp2 = x;
    x=lastx-q*x;
    lastx = temp2;

    temp3 = y;
    y = lasty-q*y;
    lasty=temp3;

  }
  std::vector<BigNumber> result{lastx, lasty};
  return result;
}

/*
 decryption
 find 4 square roots of input
*/
std::vector<BigNumber> find_root(BigNumber p, BigNumber q, BigNumber input) {
  BigNumber n = p*q;

  // 1. Use the extended Euclidean algorithm
  //    to find integers a and b satisfying ap + bq = 1
  std::vector<BigNumber> result = extend_eculidean(p, q);

  // 2. Compute r = c(p+1)/4 mod p.
  // 3. Compute s = c(q+1)/4 mod q.
  BigNumber r = pow_mod(input,(p+1)/4, p);
  BigNumber s = pow_mod(input,(q+1)/4, q);

  // 4. Compute m1 = (aps + bqr) mod n.
  // 5. Compute m2 = (aps − bqr) mod n.
  // Four root will be m1, m2, -m1, -m2. (in Zn field)
  BigNumber m1 = (result[0]*p*s + result[1]*q*r) % n;
  if (m1 < 0) {
    m1 = (m1 + n) %n;
  }
  BigNumber m2 = (result[0]*p*s - result[1]*q*r) % n;
  if (m2 < 0) {
    m2 = (m2 + n) %n;
  }
  BigNumber m3 = (n - m1) % n;
  BigNumber m4 = (n - m2) % n;

  std::vector<BigNumber> root{m1, m2, m3, m4};
  return root;

}

/*
 decryption
 find which square root have been padded with duplicate digit
 ex: 1234ab34ab <- 1234ab + 34ab
*/
bool check_padding(BigNumber input, int padding_len) {
  std::string str = input.to_string();

  std::string pad = str.substr(str.size()-padding_len);
  if (str.compare(str.size()- padding_len * 2, 4, pad) == 0) {
    return true;
  }

  return false;
}

/*
 decryption
 discard duplicate digit with known padding length
 ex: 1234ab34ab -> 1234ab
*/
BigNumber drop_padding(BigNumber input, int padding_len) {
  std::string str = input.to_string();
  str = str.substr(0, str.size() - padding_len);

  return BigNumber(str);
}

/*
 decryption
 use two private key to decrypt ciphertext
*/
BigNumber decrypt(BigNumber p, BigNumber q, BigNumber cipher, int padding_len) {
  std::vector<BigNumber> root = find_root(p, q, cipher);
  BigNumber plaintext;
  
  for (int i=0; i < 4; i++) {
    if (check_padding(root[i], padding_len)) {
      plaintext = root[i];
      break;
    }
  }

  return drop_padding(plaintext, padding_len);
}
