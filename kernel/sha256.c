#include "types.h"
#include "param.h"  // Add this
#include "riscv.h"  // Add this
#include "defs.h"
#include "sha256.h"

// SHA-256 constants array
static const uint32 k[64] = {
   0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
   0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
   0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
   0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
   0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
   0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
   0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
   0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

void sha256_transform(uint32* state, const unsigned char* data) {
   uint32 a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

   for (i = 0, j = 0; i < 16; ++i, j += 4)
       m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
  
   for (; i < 64; ++i)
       m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

   a = state[0];
   b = state[1];
   c = state[2];
   d = state[3];
   e = state[4];
   f = state[5];
   g = state[6];
   h = state[7];

   for (i = 0; i < 64; ++i) {
       t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
       t2 = EP0(a) + MAJ(a,b,c);
       h = g;
       g = f;
       f = e;
       e = d + t1;
       d = c;
       c = b;
       b = a;
       a = t1 + t2;
   }

   state[0] += a;
   state[1] += b;
   state[2] += c;
   state[3] += d;
   state[4] += e;
   state[5] += f;
   state[6] += g;
   state[7] += h;
}

void sha256(const unsigned char* data, uint len, unsigned char* hash) {
   uint32 state[8] = {
       0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
   };
  
   uint32 datalen = 0;
   uint32 bitlen = 0;
   unsigned char buf[64];

   // Process each byte
   for (uint i = 0; i < len; ++i) {
       buf[datalen] = data[i];
       datalen++;
       if (datalen == 64) {
           sha256_transform(state, buf);
           bitlen += 512;
           datalen = 0;
       }
   }

   // Pad remaining data
   uint32 i = datalen;
   if (datalen < 56) {
       buf[i++] = 0x80;
       while (i < 56)
           buf[i++] = 0x00;
   } else {
       buf[i++] = 0x80;
       while (i < 64)
           buf[i++] = 0x00;
       sha256_transform(state, buf);
       for (i = 0; i < 56; i++)
           buf[i] = 0x00;
   }

   // Append length (in bits) - 32 bit version
   bitlen += datalen * 8;
   buf[63] = bitlen;
   buf[62] = bitlen >> 8;
   buf[61] = bitlen >> 16;
   buf[60] = bitlen >> 24;
   buf[59] = 0;
   buf[58] = 0;
   buf[57] = 0;
   buf[56] = 0;
   sha256_transform(state, buf);

   // Output hash
   for (i = 0; i < 8; i++) {
       hash[i*4] = (state[i] >> 24) & 0xFF;
       hash[i*4 + 1] = (state[i] >> 16) & 0xFF;
       hash[i*4 + 2] = (state[i] >> 8) & 0xFF;
       hash[i*4 + 3] = state[i] & 0xFF;
   }
}