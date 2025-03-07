
#ifndef __MY_PHOTOS_H__
#define __MY_PHOTOS_H__

#include "bitmap_typedefs.h"

const uint16_t testImageData[] = {
    // 'apple', 50x50px
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xefdb, 0xe7b9, 0xe7b9,
    0xdf98, 0xe7b9, 0xf7dd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xaf0c, 0xa70a, 0x9ee9, 0x9ec8, 0x8e66, 0x8624, 0xa70b, 0xa6cb, 0xefbc, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd796, 0x96a7, 0x8e66, 0x8e66,
    0x9687, 0x9ec8, 0x8e46, 0x7dc4, 0x8625, 0x9ec8, 0x8624, 0xcf35, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xd7b5, 0x9ee9, 0x96a7, 0x8e66, 0x8625, 0x7de3, 0x5440, 0x8e66, 0xb6cf, 0x6561, 0x75c2,
    0x8e67, 0x75c3, 0xef9b, 0xffff, 0xffff, 0xffff, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xcf33, 0x8624, 0x8645, 0x7e04,
    0x6d62, 0x6da2, 0x6d81, 0x6521, 0x5460, 0x6d81, 0x6561, 0x6560, 0x6502, 0x8625, 0x6da2, 0xffff, 0xffff, 0x9c0d,
    0x51c3, 0xe71b, 0xffff, 0xffff, 0xffff, 0xc752, 0x9eaa, 0x9ec8, 0x8e45, 0x96a8, 0x8e66, 0xbf10, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xdf97, 0x9687, 0x8645, 0x7e04, 0x6d82, 0x4c40, 0x5d00, 0x75c3, 0x6da1, 0x5ce0, 0x6561,
    0x5cc0, 0x5440, 0x5ce0, 0x4c40, 0x6da2, 0xffff, 0xffff, 0xa48f, 0x4100, 0xd679, 0xffff, 0xffff, 0xb6ef, 0x96a7,
    0x8645, 0x6d62, 0x7e04, 0x6541, 0x7e04, 0x8e66, 0x7de3, 0xd776, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8624, 0x96a8, 0x7dc4,
    0x7de4, 0x6d61, 0x5460, 0x8625, 0x8606, 0x75c3, 0x6522, 0x8645, 0x7de3, 0x6d81, 0x54a0, 0x5ce0, 0x4c40, 0xb632,
    0xffff, 0xffff, 0x4920, 0x6a65, 0xffff, 0xffff, 0x8624, 0x6da1, 0x64e1, 0x6540, 0x75c2, 0x8605, 0x75c2, 0x8e66,
    0x9687, 0x9ee9, 0xcf74, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xbf10, 0x8625, 0x75a2, 0x7564, 0x8625, 0x7de3, 0x96a7, 0x8645, 0x7de3, 0x7e04,
    0x9687, 0x8625, 0x75c2, 0x6da1, 0x8625, 0x75c3, 0x962a, 0xce96, 0x8d0c, 0xe75b, 0x8328, 0x4920, 0xffff, 0xffff,
    0x6541, 0x5d20, 0x75a4, 0x75a2, 0x8625, 0x8645, 0x9ec8, 0xaecc, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xa6ea, 0x8645,
    0x5481, 0x96a8, 0x8645, 0x9ee9, 0x96a7, 0x8645, 0x8625, 0x9ec8, 0x8e66, 0x7e04, 0x75a2, 0x9687, 0x7e04, 0x6d62,
    0xefbc, 0xffff, 0xffff, 0x94cd, 0xde99, 0x5140, 0xdeb9, 0xffff, 0x5d20, 0x6540, 0x9e6c, 0x7e04, 0x9687, 0x8e66,
    0xfffe, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9ee9, 0x9ee9, 0x9687, 0x9ee9, 0x8645, 0x9ee9, 0x9ee9, 0x96a7, 0x8645,
    0x85e6, 0x96a8, 0x8646, 0x7de3, 0x96a7, 0x8e46, 0xaeae, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8c6c, 0x5160,
    0x93cb, 0xa5b1, 0xd757, 0xb6d0, 0x8645, 0x8e28, 0xc733, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd775, 0xa70b,
    0xdf98, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x9e4c, 0xa70b, 0x7de5, 0x7dc4, 0xaf0b, 0x7564, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdefa, 0x59c1, 0x8baa, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe79b, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0x7328, 0x51c1, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe5f8, 0xe5f8,
    0xe5f8, 0xe5f8, 0xe5f8, 0xe5f8, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x5140, 0xf7be, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xeedb, 0xddf8, 0xddf8, 0xe6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xb166, 0xb146, 0xc9e9, 0xc9e8, 0xe535, 0xe4b3, 0xd34d, 0xc9c8, 0xa966, 0xd472,
    0xffff, 0xffff, 0xffff, 0xffff, 0x5160, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0x9a6a, 0x91c7, 0x9a29, 0x8966,
    0x78c3, 0x70a3, 0x7925, 0x8a08, 0x81a7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdcb3, 0xc229, 0xe431, 0xdaab,
    0xda4a, 0xed14, 0xecb3, 0xe452, 0xe3f0, 0xec72, 0xe3d0, 0xc1a8, 0xa8c4, 0xbaec, 0xd4b3, 0xd4b3, 0x69e2, 0xc492,
    0xccb3, 0xccb3, 0x9166, 0x8062, 0x9105, 0xa229, 0xb32d, 0xa2cc, 0x9a4a, 0x8986, 0x8145, 0x70c3, 0x68c3, 0x68a3,
    0x9b4d, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xd3f0, 0xb063, 0xf639, 0xf6ba, 0xdb0d, 0xd1e8, 0xb104, 0xc9c8, 0xda4a, 0xda2a, 0xda2a,
    0xda09, 0xdacc, 0xd1e8, 0xa8a4, 0x8801, 0x8801, 0x4880, 0x5000, 0x8001, 0x8001, 0x98c4, 0xa125, 0xbb8e, 0xbbaf,
    0xb34d, 0x88e4, 0x80e4, 0x78c4, 0x70c3, 0x70c3, 0x68a3, 0x68a3, 0x60a3, 0x8a6a, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffdf, 0xc0a4, 0xf5f8, 0xf67a,
    0xe3af, 0xda4a, 0xca4a, 0xe2ec, 0xe229, 0xd9e8, 0xe229, 0xe209, 0xda09, 0xd9e9, 0xd1e8, 0xc9c8, 0xb946, 0xa905,
    0x88e4, 0xa0c4, 0x98c4, 0xa946, 0xa146, 0xa125, 0xaa29, 0xa229, 0x88e4, 0x88e4, 0x80c4, 0x78c4, 0x70c3, 0x70a3,
    0x68a3, 0x68a3, 0x6082, 0x6082, 0x92eb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xff9e, 0xc0c4, 0xecb3, 0xf659, 0xe36e, 0xe24a, 0xe22a, 0xda09, 0xea2a, 0xea2a, 0xe2ab,
    0xd9c8, 0xe209, 0xe1e9, 0xd9e9, 0xd1c8, 0xd1c8, 0xca09, 0xc1e8, 0xb987, 0xb167, 0xb166, 0xa946, 0xa126, 0xa125,
    0x9905, 0x9105, 0x88e4, 0x88e4, 0x80c4, 0x78c4, 0x70a3, 0x70a3, 0x70a3, 0x68a3, 0x6882, 0x6082, 0x5801, 0xef5d,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xed35, 0xd24a, 0xf639,
    0xf5b7, 0xe24a, 0xe229, 0xea09, 0xea09, 0xea6a, 0xf32d, 0xc9a7, 0xe9c8, 0xe9e8, 0xe1e8, 0xe1e8, 0xd9c8, 0xd1c8,
    0xc9a8, 0xc1a7, 0xb987, 0xb967, 0xb146, 0xa946, 0xa925, 0xa125, 0x9905, 0x90e4, 0x88e4, 0x88c4, 0x80c4, 0x78c3,
    0x70a3, 0x70a3, 0x7083, 0x6882, 0x6882, 0x6082, 0x5801, 0x932c, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc946, 0xf5f8, 0xf576, 0xda2a, 0xd9e8, 0xd9c7, 0xe9e8, 0xe9e8, 0xc945,
    0xc925, 0xf1c8, 0xf1c8, 0xe9c8, 0xe9c8, 0xe1c8, 0xd9c8, 0xd1a8, 0xc9a7, 0xc187, 0xc167, 0xb966, 0xb146, 0xa945,
    0xa925, 0xa105, 0x9905, 0x90e4, 0x88c4, 0x88c4, 0x80c3, 0x78a3, 0x78a3, 0x70a3, 0x7083, 0x6882, 0x6882, 0x6062,
    0x5800, 0x5000, 0xffbe, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xda8b, 0xdb6e,
    0xf5d7, 0xebf0, 0xe229, 0xea6a, 0xeaec, 0xe9c8, 0xf1a7, 0xf1a7, 0xf1a7, 0xf187, 0xf1a7, 0xf1a7, 0xe9a7, 0xe9a7,
    0xe1a7, 0xd9a7, 0xd1a7, 0xc987, 0xc167, 0xb946, 0xb146, 0xa926, 0xa125, 0xa105, 0x98e4, 0x90e4, 0x90c4, 0x88c4,
    0x80a3, 0x78a3, 0x70a3, 0x7083, 0x6882, 0x6882, 0x6862, 0x6042, 0x5800, 0x5000, 0x60c4, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd9c8, 0xe493, 0xf5b6, 0xe22a, 0xe209, 0xe9e8, 0xe9c8, 0xf1a7,
    0xf187, 0xf166, 0xf945, 0xf905, 0xf0c4, 0xf0a3, 0xe8a3, 0xe083, 0xe125, 0xd925, 0xc905, 0xc966, 0xc167, 0xb946,
    0xb146, 0xa925, 0xa125, 0xa105, 0x98e4, 0x90e4, 0x88c4, 0x88c4, 0x80a3, 0x78a3, 0x70a3, 0x7083, 0x7082, 0x6862,
    0x6862, 0x5800, 0x5800, 0x5000, 0x5000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a,
    0xd1c8, 0xf596, 0xe28b, 0xe229, 0xea09, 0xe9c8, 0xf1a7, 0xf186, 0xf946, 0xf883, 0xf883, 0xf883, 0xf883, 0xf083,
    0xf083, 0xe883, 0xe083, 0xd083, 0xc863, 0xc063, 0xb863, 0xb083, 0xb126, 0xa925, 0xa105, 0xa105, 0x98e4, 0x90c4,
    0x88c4, 0x80a3, 0x80a3, 0x78a3, 0x7083, 0x7082, 0x7082, 0x6862, 0x6021, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a, 0xd1c8, 0xed76, 0xe26a, 0xe209, 0xe9e8, 0xe9a7,
    0xf187, 0xf166, 0xf0a3, 0xf882, 0xf883, 0xf883, 0xf883, 0xf883, 0xf083, 0xe883, 0xe083, 0xd883, 0xc863, 0xc063,
    0xb863, 0xb042, 0xa842, 0xa083, 0xa083, 0xa0e4, 0x98e4, 0x90c4, 0x88c4, 0x80a3, 0x80a3, 0x7883, 0x7083, 0x7082,
    0x6842, 0x6021, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xf67a, 0xe411, 0xe431, 0xda29, 0xe209, 0xe9c8, 0xe9a7, 0xf166, 0xf0a3, 0xf083, 0xf883, 0xf883, 0xf883,
    0xf883, 0xf883, 0xf083, 0xe883, 0xe083, 0xd883, 0xc863, 0xc063, 0xb863, 0xb042, 0xa842, 0xa022, 0x9821, 0x9021,
    0x8821, 0x90a3, 0x8883, 0x8083, 0x7862, 0x7862, 0x7062, 0x6801, 0x6000, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000,
    0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a, 0xe3f0, 0xe431, 0xda09, 0xe1e8,
    0xe9c8, 0xe987, 0xf125, 0xf083, 0xf082, 0xf883, 0xf883, 0xf883, 0xf883, 0xf883, 0xf083, 0xe883, 0xe083, 0xd863,
    0xc863, 0xc063, 0xb862, 0xb042, 0xa842, 0xa022, 0x9821, 0x9001, 0x8801, 0x8801, 0x8001, 0x7801, 0x7000, 0x7000,
    0x6800, 0x6800, 0x6000, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xf67a, 0xe3f0, 0xe410, 0xe26a, 0xeaec, 0xe9c8, 0xe987, 0xe883, 0xf083, 0xf062, 0xf082,
    0xf883, 0xf883, 0xf882, 0xf083, 0xf083, 0xe883, 0xe063, 0xd863, 0xc863, 0xc063, 0xb062, 0xa842, 0xa022, 0x9822,
    0x9821, 0x9001, 0x8801, 0x8001, 0x8001, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x6000, 0x5800,
    0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a, 0xe3cf, 0xe3f0,
    0xe2cc, 0xe2cc, 0xe1c8, 0xe8e5, 0xe883, 0xe883, 0xf062, 0xf082, 0xf062, 0xf062, 0xf082, 0xf062, 0xe883, 0xe883,
    0xd863, 0xd063, 0xc863, 0xc063, 0xb042, 0xa842, 0xa022, 0x9821, 0x9021, 0x9001, 0x8801, 0x8001, 0x8000, 0x7800,
    0x7000, 0x7000, 0x6800, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a, 0xe3af, 0xe3d0, 0xdacc, 0xe2cc, 0xe1c8, 0xe0e5, 0xe883, 0xe883,
    0xf083, 0xf082, 0xf082, 0xf082, 0xf063, 0xe883, 0xe883, 0xe083, 0xd883, 0xd063, 0xc063, 0xb842, 0xb042, 0xa842,
    0xa021, 0x9821, 0x9021, 0x8801, 0x8801, 0x8001, 0x8000, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6800, 0x6000,
    0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a,
    0xdb4e, 0xdbaf, 0xdaab, 0xe2ab, 0xe1c8, 0xe0e5, 0xe083, 0xe883, 0xe883, 0xe883, 0xe883, 0xf083, 0xe883, 0xe883,
    0xe083, 0xd883, 0xd063, 0xc863, 0xc063, 0xb842, 0xa842, 0xa042, 0x9821, 0x9821, 0x9001, 0x8801, 0x8801, 0x8000,
    0x8000, 0x7800, 0x7000, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf67a, 0xc9a7, 0xdb8f, 0xda8b, 0xda4a, 0xd9e8, 0xd905,
    0xd883, 0xe083, 0xe083, 0xe883, 0xe883, 0xe883, 0xe883, 0xe083, 0xd883, 0xd083, 0xd063, 0xc063, 0xb862, 0xb042,
    0xa842, 0xa022, 0x9821, 0x9021, 0x9001, 0x8800, 0x8000, 0x8000, 0x7800, 0x7800, 0x7000, 0x7000, 0x7000, 0x6800,
    0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xf6db, 0xc987, 0xdb6e, 0xd26b, 0xd22a, 0xd9c8, 0xd083, 0xd883, 0xd883, 0xe083, 0xe083, 0xe083, 0xe083,
    0xe083, 0xd883, 0xd883, 0xd083, 0xc863, 0xc063, 0xb842, 0xb042, 0xa842, 0xa021, 0x9821, 0x9021, 0x8801, 0x8800,
    0x8000, 0x8000, 0x7800, 0x7800, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000,
    0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc9c8, 0xdb4e, 0xd209, 0xd229,
    0xd1c8, 0xc883, 0xd083, 0xd083, 0xd883, 0xd883, 0xd883, 0xd883, 0xd883, 0xd083, 0xd083, 0xc863, 0xc063, 0xb863,
    0xb042, 0xa842, 0xa022, 0x9821, 0x9021, 0x9001, 0x8800, 0x8000, 0x8000, 0x8000, 0x7800, 0x7800, 0x7800, 0x7000,
    0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5000, 0x5000, 0x5000, 0xb471, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xc9c8, 0xd2ab, 0xca09, 0xd209, 0xd1c8, 0xc883, 0xc883, 0xc883, 0xd0a3, 0xd083,
    0xd083, 0xd083, 0xd083, 0xd083, 0xc883, 0xc063, 0xb863, 0xb863, 0xb042, 0xa842, 0xa021, 0x9821, 0x9021, 0x9001,
    0x8800, 0x8000, 0x8000, 0x8000, 0x7800, 0x7800, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800,
    0x5000, 0x5000, 0x5000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc146,
    0xca09, 0xca29, 0xc9c8, 0xc083, 0xc083, 0xc883, 0xc883, 0xc884, 0xc884, 0xc884, 0xc883, 0xc083, 0xc063, 0xb863,
    0xb863, 0xb042, 0xb042, 0xa842, 0xa021, 0x9821, 0x9021, 0x9001, 0x8800, 0x8000, 0x8000, 0x8000, 0x7800, 0x7800,
    0x7000, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0x4800, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb8a4, 0xd2cc, 0xc9e8, 0xc9c8, 0xc0e5, 0xc083, 0xc083,
    0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xb863, 0xb863, 0xb063, 0xb042, 0xa842, 0xa022, 0x9821, 0x9821,
    0x9001, 0x8801, 0x8800, 0x8000, 0x8000, 0x7800, 0x7800, 0x7800, 0x7000, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000,
    0x5800, 0x5800, 0x5000, 0x5000, 0xb492, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xe535, 0xd2ec, 0xc9c8, 0xc9c8, 0xc0e5, 0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xb863,
    0xb863, 0xb862, 0xb042, 0xb042, 0xa842, 0xa022, 0x9821, 0x9821, 0x9001, 0x8801, 0x8800, 0x8000, 0x8000, 0x7800,
    0x7800, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xffbe, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf75d, 0xb0c4, 0xca4a, 0xc1a8, 0xc0e5,
    0xb883, 0xc083, 0xc083, 0xc083, 0xc083, 0xc083, 0xb863, 0xb863, 0xb863, 0xb063, 0xb042, 0xa842, 0xa842, 0xa022,
    0x9821, 0x9021, 0x9001, 0x8801, 0x8000, 0x8000, 0x8000, 0x7800, 0x7800, 0x7000, 0x7000, 0x7000, 0x6800, 0x6800,
    0x6000, 0x6000, 0x5800, 0x5000, 0x5000, 0x8249, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xa083, 0xc1a7, 0xc1a8, 0xb8e4, 0xb863, 0xb883, 0xb883, 0xb883, 0xb883, 0xb863,
    0xb863, 0xb863, 0xb062, 0xb042, 0xa842, 0xa842, 0xa022, 0xa022, 0x9821, 0x9021, 0x9021, 0x8801, 0x8000, 0x8000,
    0x7800, 0x7800, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0xb4b3,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf75d, 0xb0e4,
    0xc1a7, 0xb8e5, 0xb863, 0xb863, 0xb863, 0xb863, 0xb863, 0xb863, 0xb863, 0xb062, 0xb043, 0xb042, 0xa842, 0xa842,
    0xa022, 0xa022, 0x9821, 0x9021, 0x8801, 0x8801, 0x8001, 0x8000, 0x7800, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800,
    0x6800, 0x6000, 0x6000, 0x5800, 0x5000, 0x5000, 0x5000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb1e8, 0xc187, 0xc187, 0xb863, 0xb863, 0xb863, 0xb863,
    0xb863, 0xb863, 0xb063, 0xb062, 0xb042, 0xa842, 0xa842, 0xa042, 0xa042, 0x9821, 0x9821, 0x9021, 0x8801, 0x8801,
    0x8001, 0x8000, 0x7800, 0x7000, 0x7000, 0x6800, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000,
    0xde79, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xcc31, 0x9021, 0xc187, 0xb063, 0xb863, 0xb863, 0xb863, 0xb863, 0xb063, 0xb043, 0xb042, 0xa842, 0xa842,
    0xa042, 0xa022, 0xa022, 0x9822, 0x9021, 0x9001, 0x8801, 0x8001, 0x8001, 0x7800, 0x7800, 0x7000, 0x7000, 0x6800,
    0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5000, 0x5000, 0x79c7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd4b3, 0xb125, 0xb8e4, 0xb063,
    0xb063, 0xb063, 0xb063, 0xb063, 0xb042, 0xa842, 0xa842, 0xa842, 0xa042, 0xa042, 0x9822, 0x9821, 0x9021, 0x8801,
    0x8801, 0x8001, 0x8001, 0x7801, 0x7000, 0x7000, 0x6800, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5800, 0x5000,
    0x5000, 0xcdd7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xf77d, 0xa946, 0xb905, 0xb062, 0xb062, 0xb062, 0xb062, 0xb062, 0xa842, 0xa842,
    0xa842, 0xa042, 0xa022, 0x9822, 0x9822, 0x9021, 0x9021, 0x8821, 0x8801, 0x8001, 0x7801, 0x7801, 0x7000, 0x6800,
    0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5800, 0x5000, 0x5021, 0xd5d7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xf6fb,
    0x9863, 0xb083, 0xb063, 0xb063, 0xb042, 0xa842, 0xa842, 0xa842, 0xa042, 0xa042, 0x9842, 0x9822, 0x9821, 0x9021,
    0x8821, 0x8801, 0x8001, 0x8001, 0x7801, 0x7001, 0x7000, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5800, 0x5800,
    0x5000, 0xde9a, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xaaec, 0x9822, 0xa842, 0xa862, 0xa842, 0xa842,
    0xa842, 0xa042, 0xa042, 0xa022, 0x9822, 0x9822, 0x9021, 0x9021, 0x8821, 0x8801, 0x8001, 0x7801, 0x7801, 0x7001,
    0x6801, 0x6800, 0x6000, 0x6000, 0x5800, 0x5800, 0x5800, 0x5000, 0xcd76, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0x9146, 0x9021, 0xa842, 0xa842, 0xa842, 0xa042, 0xa042, 0xa042, 0x9822, 0x9822, 0x9021,
    0x9021, 0x8821, 0x8801, 0x8001, 0x7801, 0x7801, 0x7001, 0x7001, 0x6801, 0x6000, 0x6000, 0x5800, 0x5800, 0x5800,
    0x5000, 0xef1c, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe69a, 0x9021,
    0x9822, 0xa042, 0xa042, 0xa022, 0x9822, 0x9822, 0x9021, 0x9021, 0x8821, 0x7801, 0x7801, 0x7001, 0x7001, 0x7801,
    0x7001, 0x6801, 0x6800, 0x6000, 0x5800, 0x5800, 0x5800, 0x9b4d, 0xcd96, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xbc10, 0x88e4, 0x9822, 0x9822, 0x9021, 0x9021,
    0x9021, 0x80a3, 0x8104, 0x8104, 0x7904, 0x7904, 0x7904, 0x78e4, 0x6821, 0x6800, 0x6000, 0x5800, 0x5800, 0x6904,
    0x8249, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffbe, 0xd5b6, 0xd5b6, 0xd5b6, 0xd5b6, 0xd5b6, 0xf73c, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffdf, 0xde18, 0xd5b6, 0xd5b6, 0xd5b6, 0xd5b7, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};

const tImage16bit testImage[] = {{testImageData, 50, 50, 2500}};

#endif // __MY_PHOTOS_H__

/* EOF */

