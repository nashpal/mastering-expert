//
//  VectorScope.cpp
//  MasteringExpert
//
//  Created by Anthony Nash on 18/09/2015.
//
//

#include "VectorScope.h"

static const unsigned char pathData[] = { 110,109,143,226,119,67,72,65,197,67,108,199,235,119,67,0,128,197,67,108,74,172,119,67,0,128,197,67,98,172,188,119,67,111,114,197,67,45,178,119,67,231,123,197,67,174,199,119,67,111,98,197,67,108,143,226,119,67,72,65,197,67,99,109,8,108,19,67,35,219,121,
    63,108,225,58,23,67,139,108,183,63,98,248,83,25,67,139,108,215,63,2,11,29,67,63,53,14,64,231,123,31,67,57,180,40,64,108,20,238,35,67,176,114,88,64,108,16,24,41,67,135,22,149,64,108,6,65,46,67,182,243,189,64,108,6,129,51,67,213,120,245,64,98,27,79,60,
    67,100,59,41,65,14,173,67,67,205,204,90,65,236,209,76,67,129,149,146,65,108,233,38,82,67,113,61,168,65,108,6,193,88,67,53,94,203,65,108,254,148,93,67,217,206,235,65,108,18,163,96,67,225,122,2,66,108,229,176,99,67,68,11,15,66,108,20,142,101,67,51,179,
    24,66,98,4,54,106,67,143,194,48,66,10,119,109,67,135,150,72,66,236,145,111,67,68,11,98,66,108,254,116,112,67,119,190,108,66,108,0,0,113,67,201,118,119,66,108,252,137,113,67,141,23,129,66,108,25,4,114,67,154,153,140,66,108,227,5,114,67,63,117,206,66,108,
    236,49,115,67,178,157,210,66,108,238,92,116,67,150,195,214,66,108,33,208,118,67,121,233,217,66,98,246,40,120,67,84,163,219,66,10,119,122,67,100,251,222,66,20,238,123,67,129,85,225,66,108,23,153,126,67,166,155,229,66,108,242,242,128,67,133,107,236,66,
    108,252,153,130,67,88,57,243,66,108,10,135,131,67,96,37,248,66,98,135,22,135,67,205,140,5,67,133,43,137,67,174,199,15,67,252,249,137,67,209,194,27,67,108,6,49,138,67,158,239,30,67,108,6,49,138,67,207,215,40,67,108,252,249,137,67,215,3,44,67,98,8,44,137,
    67,201,246,55,67,6,33,135,67,205,12,66,67,125,159,131,67,203,97,75,67,108,252,121,130,67,211,109,78,67,108,117,243,128,67,176,146,81,67,108,29,218,126,67,201,182,84,67,108,27,47,124,67,178,221,86,67,98,16,184,122,67,205,12,88,67,252,73,120,67,188,212,
    89,67,252,201,118,67,170,209,90,67,108,33,16,116,67,190,159,92,67,108,250,30,114,67,164,240,95,67,98,23,249,108,67,219,185,104,67,18,35,103,67,213,88,112,67,252,9,96,67,186,137,119,67,98,248,19,86,67,236,209,128,67,29,58,76,67,233,102,132,67,16,184,63,
    67,227,133,135,67,108,244,189,58,67,215,195,136,67,108,248,211,54,67,213,136,137,67,98,240,167,44,67,213,136,139,67,242,146,34,67,238,204,140,67,238,188,23,67,229,112,141,67,108,27,47,20,67,233,166,141,67,108,20,206,11,67,236,177,141,67,108,8,108,3,67,
    80,189,141,67,108,33,176,255,66,236,145,141,67,98,195,53,223,66,231,203,140,67,12,66,193,66,104,145,138,67,20,238,164,66,229,208,134,67,98,0,192,146,66,82,104,132,67,203,97,132,66,209,226,129,67,0,0,104,66,188,116,124,67,108,8,172,89,66,203,65,121,67,
    108,207,247,78,66,203,97,118,67,98,158,239,50,66,178,221,110,67,49,136,27,66,193,10,103,67,166,27,10,66,172,92,95,67,108,131,192,4,66,184,254,92,67,108,66,96,250,65,217,206,91,67,98,197,32,184,65,207,151,86,67,49,8,129,65,172,220,79,67,20,174,45,65,182,
    211,71,67,108,119,190,13,65,168,198,68,67,108,12,2,235,64,211,205,65,67,98,131,192,174,64,172,28,62,67,225,122,116,64,182,243,57,67,174,71,41,64,190,223,53,67,108,219,249,222,63,184,190,50,67,108,18,131,144,63,221,36,47,67,108,111,18,3,63,186,137,43,
    67,108,147,24,132,62,201,182,39,67,108,0,0,0,0,215,227,35,67,108,147,24,132,62,164,16,32,67,108,111,18,3,63,172,60,28,67,108,18,131,144,63,209,162,24,67,108,219,249,222,63,174,7,21,67,108,174,71,41,64,174,231,17,67,98,244,253,116,64,217,206,13,67,131,
    192,174,64,186,169,9,67,59,223,235,64,186,233,5,67,108,33,176,14,65,203,225,2,67,108,53,94,86,65,186,73,248,66,108,141,151,139,65,84,163,238,66,108,10,215,185,65,182,115,227,66,108,125,63,210,65,59,223,222,66,98,240,167,223,65,166,91,220,66,147,24,241,
    65,80,77,217,66,49,8,249,65,129,21,216,66,108,82,184,3,66,178,221,213,66,108,8,44,7,66,137,193,210,66,108,215,163,10,66,109,167,207,66,108,174,199,11,66,133,235,128,66,108,98,16,14,66,27,175,119,66,98,248,83,15,66,135,22,114,66,106,60,18,66,242,210,103,
    66,74,140,20,66,59,223,96,66,108,106,188,24,66,76,55,84,66,108,66,96,39,66,2,171,54,66,108,141,151,48,66,176,242,40,66,108,199,203,57,66,100,59,27,66,108,41,220,74,66,127,234,6,66,108,190,31,99,66,184,30,223,65,108,74,140,109,66,233,38,207,65,98,98,16,
    124,66,145,237,184,65,4,22,132,66,184,30,170,65,215,99,143,66,96,229,146,65,98,61,138,160,66,139,108,95,65,37,134,176,66,238,124,41,65,25,4,194,66,63,53,246,64,108,20,110,204,66,219,249,190,64,108,16,216,214,66,94,186,149,64,108,12,66,225,66,57,180,88,
    64,108,227,37,234,66,57,180,40,64,98,49,8,239,66,63,53,14,64,195,117,246,66,139,108,215,63,240,167,250,66,139,108,183,63,108,18,35,1,67,227,165,123,63,108,240,71,10,67,190,159,122,63,108,8,108,19,67,35,219,121,63,99,109,31,165,1,67,2,43,86,66,108,20,
    46,252,66,225,250,87,66,98,215,227,206,66,43,135,99,66,49,200,168,66,174,71,130,66,4,86,134,66,80,13,159,66,108,25,196,129,66,59,223,162,66,108,106,60,113,66,92,15,172,66,108,158,239,94,66,113,61,181,66,108,57,180,84,66,129,149,187,66,98,16,216,41,66,
    158,47,214,66,248,83,14,66,109,103,241,66,49,8,252,65,193,170,8,67,108,92,143,243,65,158,207,12,67,108,82,184,237,65,205,44,17,67,98,6,129,234,65,182,147,19,67,240,167,230,65,186,233,22,67,27,47,229,65,201,150,24,67,108,6,129,226,65,209,162,27,67,108,
    190,159,226,65,162,101,44,67,108,125,63,230,65,188,20,48,67,98,27,47,240,65,221,36,58,67,231,251,0,66,203,1,67,67,90,100,15,66,188,52,76,67,108,158,111,21,66,176,18,80,67,108,133,107,30,66,195,149,84,67,108,90,100,39,66,213,24,89,67,108,57,180,47,66,
    162,133,92,67,98,0,0,96,66,201,118,112,67,49,8,148,66,221,20,128,67,195,117,190,66,211,157,132,67,108,248,211,197,66,207,103,133,67,108,219,121,207,66,90,52,134,67,108,203,33,217,66,229,0,135,67,108,244,125,224,66,90,116,135,67,98,45,50,236,66,231,43,
    136,67,0,64,249,66,223,175,136,67,252,233,2,67,211,237,136,67,108,254,180,5,67,219,9,137,67,108,27,47,12,67,238,252,136,67,108,246,168,18,67,92,239,136,67,108,10,23,22,67,211,189,136,67,98,27,175,32,67,215,35,136,67,231,219,41,67,92,255,134,67,8,108,
    51,67,233,22,133,67,108,225,58,55,67,215,83,132,67,108,8,76,59,67,223,79,131,67,98,236,81,67,67,86,78,129,67,225,218,73,67,215,99,126,67,6,193,80,67,190,191,120,67,108,8,108,83,67,170,145,118,67,108,248,115,87,67,190,159,114,67,108,231,123,91,67,217,
    174,110,67,108,227,229,93,67,215,227,107,67,98,4,246,98,67,168,6,102,67,227,101,103,67,168,166,95,67,250,62,107,67,201,182,88,67,108,20,110,109,67,168,198,84,67,108,23,57,111,67,197,192,80,67,98,242,82,114,67,180,200,73,67,250,158,116,67,215,227,66,67,
    4,54,118,67,209,194,59,67,108,4,22,119,67,182,211,55,67,108,23,185,119,67,203,97,51,67,108,225,90,120,67,158,239,46,67,108,242,242,120,67,199,11,38,67,108,2,203,120,67,207,215,32,67,108,12,162,120,67,209,162,27,67,108,0,64,120,67,188,52,24,67,98,4,118,
    119,67,211,45,17,67,4,86,118,67,217,142,11,67,20,78,116,67,184,126,4,67,108,20,14,115,67,168,38,0,67,108,250,126,113,67,100,123,248,66,98,20,110,109,67,104,17,228,66,27,175,104,67,80,77,211,66,25,196,97,67,133,235,192,66,108,31,133,94,67,186,73,184,66,
    108,238,92,91,67,145,109,177,66,98,20,238,78,67,121,105,150,66,10,183,62,67,162,133,129,66,248,51,45,67,152,238,107,66,108,6,193,40,67,92,15,102,66,108,229,144,36,67,176,242,97,66,98,229,208,31,67,217,78,93,66,8,44,28,67,2,171,90,66,23,217,22,67,18,3,
    88,66,108,2,43,19,67,27,47,86,66,108,240,103,10,67,27,47,86,66,108,31,165,1,67,2,43,86,66,99,109,190,255,24,67,182,147,84,67,108,0,0,25,67,0,0,85,67,108,59,255,24,67,186,105,85,67,108,51,211,24,67,186,105,85,67,108,190,255,24,67,182,147,84,67,99,109,
    2,43,3,67,37,6,150,65,108,0,96,0,67,178,157,152,65,98,53,158,231,66,211,77,164,65,244,253,206,66,80,141,190,65,37,70,178,66,4,86,236,65,108,41,220,167,66,145,237,252,65,108,49,8,163,66,117,147,3,66,98,195,117,157,66,225,122,9,66,8,236,149,66,117,147,
    19,66,231,187,143,66,152,110,29,66,108,252,105,139,66,217,78,36,66,108,199,203,132,66,68,139,49,66,108,41,92,124,66,193,202,62,66,108,106,188,114,66,27,175,75,66,108,190,31,105,66,117,147,88,66,108,33,48,100,66,119,62,97,66,98,231,123,97,66,18,3,102,
    66,33,176,93,66,92,143,109,66,150,195,91,66,18,3,114,66,108,150,67,88,66,135,22,122,66,108,150,195,85,66,88,249,129,66,108,174,71,83,66,96,229,134,66,108,174,71,83,66,186,201,159,66,108,57,180,94,66,137,65,154,66,98,231,251,100,66,76,55,151,66,90,100,
    111,66,186,137,146,66,223,207,117,66,178,221,143,66,98,211,13,159,66,117,147,99,66,211,13,201,66,100,187,62,66,16,152,246,66,100,59,51,66,108,207,183,254,66,2,43,49,66,108,33,112,4,67,250,254,47,66,108,25,132,9,67,217,206,46,66,108,4,214,13,67,225,122,
    47,66,98,233,166,21,67,27,175,48,66,254,212,27,67,117,147,51,66,238,220,34,67,193,74,57,66,108,250,158,38,67,35,91,60,66,108,6,1,43,67,242,82,65,66,98,23,249,50,67,35,91,74,66,2,235,57,67,35,91,85,66,240,103,65,67,168,198,100,66,108,244,189,69,67,76,
    183,109,66,108,246,136,73,67,76,55,119,66,98,27,79,81,67,141,87,133,66,12,194,87,67,96,101,143,66,14,45,94,67,68,203,155,66,108,252,9,96,67,96,101,159,66,108,8,236,95,67,182,243,146,66,108,14,205,95,67,137,129,134,66,108,12,66,95,67,170,113,130,66,98,
    240,135,94,67,68,11,122,66,229,240,93,67,127,234,115,66,10,151,92,67,209,34,105,66,108,254,116,91,67,184,30,96,66,108,27,175,89,67,92,143,85,66,98,252,41,83,67,209,162,46,66,250,222,72,67,168,70,12,66,18,163,62,67,238,124,246,65,98,248,147,47,67,102,
    102,196,65,16,56,34,67,102,102,166,65,242,82,21,67,70,182,153,65,108,31,165,17,67,184,30,150,65,108,240,103,10,67,86,14,150,65,108,2,43,3,67,37,6,150,65,99,109,143,226,119,67,72,65,197,67,108,199,235,119,67,0,128,197,67,108,74,172,119,67,0,128,197,67,
    98,172,188,119,67,111,114,197,67,45,178,119,67,231,123,197,67,174,199,119,67,111,98,197,67,108,143,226,119,67,72,65,197,67,99,109,8,108,19,67,35,219,121,63,108,225,58,23,67,139,108,183,63,98,248,83,25,67,139,108,215,63,2,11,29,67,63,53,14,64,231,123,
    31,67,57,180,40,64,108,20,238,35,67,176,114,88,64,108,16,24,41,67,135,22,149,64,108,6,65,46,67,182,243,189,64,108,6,129,51,67,213,120,245,64,98,27,79,60,67,100,59,41,65,14,173,67,67,205,204,90,65,236,209,76,67,129,149,146,65,108,233,38,82,67,113,61,168,
    65,108,6,193,88,67,53,94,203,65,108,254,148,93,67,217,206,235,65,108,18,163,96,67,225,122,2,66,108,229,176,99,67,68,11,15,66,108,20,142,101,67,51,179,24,66,98,4,54,106,67,143,194,48,66,10,119,109,67,135,150,72,66,236,145,111,67,68,11,98,66,108,254,116,
    112,67,119,190,108,66,108,0,0,113,67,201,118,119,66,108,252,137,113,67,141,23,129,66,108,25,4,114,67,154,153,140,66,108,227,5,114,67,63,117,206,66,108,236,49,115,67,178,157,210,66,108,238,92,116,67,150,195,214,66,108,33,208,118,67,121,233,217,66,98,246,
    40,120,67,84,163,219,66,10,119,122,67,100,251,222,66,20,238,123,67,129,85,225,66,108,23,153,126,67,166,155,229,66,108,242,242,128,67,133,107,236,66,108,252,153,130,67,88,57,243,66,108,10,135,131,67,96,37,248,66,98,135,22,135,67,205,140,5,67,133,43,137,
    67,174,199,15,67,252,249,137,67,209,194,27,67,108,6,49,138,67,158,239,30,67,108,6,49,138,67,207,215,40,67,108,252,249,137,67,215,3,44,67,98,8,44,137,67,201,246,55,67,6,33,135,67,205,12,66,67,125,159,131,67,203,97,75,67,108,252,121,130,67,211,109,78,67,
    108,117,243,128,67,176,146,81,67,108,29,218,126,67,201,182,84,67,108,27,47,124,67,178,221,86,67,98,16,184,122,67,205,12,88,67,252,73,120,67,188,212,89,67,252,201,118,67,170,209,90,67,108,33,16,116,67,190,159,92,67,108,250,30,114,67,164,240,95,67,98,23,
    249,108,67,219,185,104,67,18,35,103,67,213,88,112,67,252,9,96,67,186,137,119,67,98,248,19,86,67,236,209,128,67,29,58,76,67,233,102,132,67,16,184,63,67,227,133,135,67,108,244,189,58,67,215,195,136,67,108,248,211,54,67,213,136,137,67,98,240,167,44,67,213,
    136,139,67,242,146,34,67,238,204,140,67,238,188,23,67,229,112,141,67,108,27,47,20,67,233,166,141,67,108,20,206,11,67,236,177,141,67,108,8,108,3,67,80,189,141,67,108,33,176,255,66,236,145,141,67,98,195,53,223,66,231,203,140,67,12,66,193,66,104,145,138,
    67,20,238,164,66,229,208,134,67,98,0,192,146,66,82,104,132,67,203,97,132,66,209,226,129,67,0,0,104,66,188,116,124,67,108,8,172,89,66,203,65,121,67,108,207,247,78,66,203,97,118,67,98,158,239,50,66,178,221,110,67,49,136,27,66,193,10,103,67,166,27,10,66,
    172,92,95,67,108,131,192,4,66,184,254,92,67,108,66,96,250,65,217,206,91,67,98,197,32,184,65,207,151,86,67,49,8,129,65,172,220,79,67,20,174,45,65,182,211,71,67,108,119,190,13,65,168,198,68,67,108,12,2,235,64,211,205,65,67,98,131,192,174,64,172,28,62,67,
    225,122,116,64,182,243,57,67,174,71,41,64,190,223,53,67,108,219,249,222,63,184,190,50,67,108,18,131,144,63,221,36,47,67,108,111,18,3,63,186,137,43,67,108,147,24,132,62,201,182,39,67,108,0,0,0,0,215,227,35,67,108,147,24,132,62,164,16,32,67,108,111,18,
    3,63,172,60,28,67,108,18,131,144,63,209,162,24,67,108,219,249,222,63,174,7,21,67,108,174,71,41,64,174,231,17,67,98,244,253,116,64,217,206,13,67,131,192,174,64,186,169,9,67,59,223,235,64,186,233,5,67,108,33,176,14,65,203,225,2,67,108,53,94,86,65,186,73,
    248,66,108,141,151,139,65,84,163,238,66,108,10,215,185,65,182,115,227,66,108,125,63,210,65,59,223,222,66,98,240,167,223,65,166,91,220,66,147,24,241,65,80,77,217,66,49,8,249,65,129,21,216,66,108,82,184,3,66,178,221,213,66,108,8,44,7,66,137,193,210,66,
    108,215,163,10,66,109,167,207,66,108,174,199,11,66,133,235,128,66,108,98,16,14,66,27,175,119,66,98,248,83,15,66,135,22,114,66,106,60,18,66,242,210,103,66,74,140,20,66,59,223,96,66,108,106,188,24,66,76,55,84,66,108,66,96,39,66,2,171,54,66,108,141,151,
    48,66,176,242,40,66,108,199,203,57,66,100,59,27,66,108,41,220,74,66,127,234,6,66,108,190,31,99,66,184,30,223,65,108,74,140,109,66,233,38,207,65,98,98,16,124,66,145,237,184,65,4,22,132,66,184,30,170,65,215,99,143,66,96,229,146,65,98,61,138,160,66,139,
    108,95,65,37,134,176,66,238,124,41,65,25,4,194,66,63,53,246,64,108,20,110,204,66,219,249,190,64,108,16,216,214,66,94,186,149,64,108,12,66,225,66,57,180,88,64,108,227,37,234,66,57,180,40,64,98,49,8,239,66,63,53,14,64,195,117,246,66,139,108,215,63,240,
    167,250,66,139,108,183,63,108,18,35,1,67,227,165,123,63,108,240,71,10,67,190,159,122,63,108,8,108,19,67,35,219,121,63,99,109,31,165,1,67,2,43,86,66,108,20,46,252,66,225,250,87,66,98,215,227,206,66,43,135,99,66,49,200,168,66,174,71,130,66,4,86,134,66,
    80,13,159,66,108,25,196,129,66,59,223,162,66,108,106,60,113,66,92,15,172,66,108,158,239,94,66,113,61,181,66,108,57,180,84,66,129,149,187,66,98,16,216,41,66,158,47,214,66,248,83,14,66,109,103,241,66,49,8,252,65,193,170,8,67,108,92,143,243,65,158,207,12,
    67,108,82,184,237,65,205,44,17,67,98,6,129,234,65,182,147,19,67,240,167,230,65,186,233,22,67,27,47,229,65,201,150,24,67,108,6,129,226,65,209,162,27,67,108,190,159,226,65,162,101,44,67,108,125,63,230,65,188,20,48,67,98,27,47,240,65,221,36,58,67,231,251,
    0,66,203,1,67,67,90,100,15,66,188,52,76,67,108,158,111,21,66,176,18,80,67,108,133,107,30,66,195,149,84,67,108,90,100,39,66,213,24,89,67,108,57,180,47,66,162,133,92,67,98,0,0,96,66,201,118,112,67,49,8,148,66,221,20,128,67,195,117,190,66,211,157,132,67,
    108,248,211,197,66,207,103,133,67,108,219,121,207,66,90,52,134,67,108,203,33,217,66,229,0,135,67,108,244,125,224,66,90,116,135,67,98,45,50,236,66,231,43,136,67,0,64,249,66,223,175,136,67,252,233,2,67,211,237,136,67,108,254,180,5,67,219,9,137,67,108,27,
    47,12,67,238,252,136,67,108,246,168,18,67,92,239,136,67,108,10,23,22,67,211,189,136,67,98,27,175,32,67,215,35,136,67,231,219,41,67,92,255,134,67,8,108,51,67,233,22,133,67,108,225,58,55,67,215,83,132,67,108,8,76,59,67,223,79,131,67,98,236,81,67,67,86,
    78,129,67,225,218,73,67,215,99,126,67,6,193,80,67,190,191,120,67,108,8,108,83,67,170,145,118,67,108,248,115,87,67,190,159,114,67,108,231,123,91,67,217,174,110,67,108,227,229,93,67,215,227,107,67,98,4,246,98,67,168,6,102,67,227,101,103,67,168,166,95,67,
    250,62,107,67,201,182,88,67,108,20,110,109,67,168,198,84,67,108,23,57,111,67,197,192,80,67,98,242,82,114,67,180,200,73,67,250,158,116,67,215,227,66,67,4,54,118,67,209,194,59,67,108,4,22,119,67,182,211,55,67,108,23,185,119,67,203,97,51,67,108,225,90,120,
    67,158,239,46,67,108,242,242,120,67,199,11,38,67,108,2,203,120,67,207,215,32,67,108,12,162,120,67,209,162,27,67,108,0,64,120,67,188,52,24,67,98,4,118,119,67,211,45,17,67,4,86,118,67,217,142,11,67,20,78,116,67,184,126,4,67,108,20,14,115,67,168,38,0,67,
    108,250,126,113,67,100,123,248,66,98,20,110,109,67,104,17,228,66,27,175,104,67,80,77,211,66,25,196,97,67,133,235,192,66,108,31,133,94,67,186,73,184,66,108,238,92,91,67,145,109,177,66,98,20,238,78,67,121,105,150,66,10,183,62,67,162,133,129,66,248,51,45,
    67,152,238,107,66,108,6,193,40,67,92,15,102,66,108,229,144,36,67,176,242,97,66,98,229,208,31,67,217,78,93,66,8,44,28,67,2,171,90,66,23,217,22,67,18,3,88,66,108,2,43,19,67,27,47,86,66,108,240,103,10,67,27,47,86,66,108,31,165,1,67,2,43,86,66,99,109,190,
    255,24,67,182,147,84,67,108,0,0,25,67,0,0,85,67,108,59,255,24,67,186,105,85,67,108,51,211,24,67,186,105,85,67,108,190,255,24,67,182,147,84,67,99,109,2,43,3,67,37,6,150,65,108,0,96,0,67,178,157,152,65,98,53,158,231,66,211,77,164,65,244,253,206,66,80,141,
    190,65,37,70,178,66,4,86,236,65,108,41,220,167,66,145,237,252,65,108,49,8,163,66,117,147,3,66,98,195,117,157,66,225,122,9,66,8,236,149,66,117,147,19,66,231,187,143,66,152,110,29,66,108,252,105,139,66,217,78,36,66,108,199,203,132,66,68,139,49,66,108,41,
    92,124,66,193,202,62,66,108,106,188,114,66,27,175,75,66,108,190,31,105,66,117,147,88,66,108,33,48,100,66,119,62,97,66,98,231,123,97,66,18,3,102,66,33,176,93,66,92,143,109,66,150,195,91,66,18,3,114,66,108,150,67,88,66,135,22,122,66,108,150,195,85,66,88,
    249,129,66,108,174,71,83,66,96,229,134,66,108,174,71,83,66,186,201,159,66,108,57,180,94,66,137,65,154,66,98,231,251,100,66,76,55,151,66,90,100,111,66,186,137,146,66,223,207,117,66,178,221,143,66,98,211,13,159,66,117,147,99,66,211,13,201,66,100,187,62,
    66,16,152,246,66,100,59,51,66,108,207,183,254,66,2,43,49,66,108,33,112,4,67,250,254,47,66,108,25,132,9,67,217,206,46,66,108,4,214,13,67,225,122,47,66,98,233,166,21,67,27,175,48,66,254,212,27,67,117,147,51,66,238,220,34,67,193,74,57,66,108,250,158,38,
    67,35,91,60,66,108,6,1,43,67,242,82,65,66,98,23,249,50,67,35,91,74,66,2,235,57,67,35,91,85,66,240,103,65,67,168,198,100,66,108,244,189,69,67,76,183,109,66,108,246,136,73,67,76,55,119,66,98,27,79,81,67,141,87,133,66,12,194,87,67,96,101,143,66,14,45,94,
    67,68,203,155,66,108,252,9,96,67,96,101,159,66,108,8,236,95,67,182,243,146,66,108,14,205,95,67,137,129,134,66,108,12,66,95,67,170,113,130,66,98,240,135,94,67,68,11,122,66,229,240,93,67,127,234,115,66,10,151,92,67,209,34,105,66,108,254,116,91,67,184,30,
    96,66,108,27,175,89,67,92,143,85,66,98,252,41,83,67,209,162,46,66,250,222,72,67,168,70,12,66,18,163,62,67,238,124,246,65,98,248,147,47,67,102,102,196,65,16,56,34,67,102,102,166,65,242,82,21,67,70,182,153,65,108,31,165,17,67,184,30,150,65,108,240,103,
    10,67,86,14,150,65,108,2,43,3,67,37,6,150,65,99,109,143,226,119,67,72,65,197,67,108,199,235,119,67,0,128,197,67,108,74,172,119,67,0,128,197,67,98,172,188,119,67,111,114,197,67,45,178,119,67,231,123,197,67,174,199,119,67,111,98,197,67,108,143,226,119,
    67,72,65,197,67,99,109,225,186,19,67,35,219,121,63,108,186,137,23,67,139,108,183,63,98,18,163,25,67,139,108,215,63,29,90,29,67,63,53,14,64,2,203,31,67,57,180,40,64,108,238,60,36,67,176,114,88,64,108,233,102,41,67,135,22,149,64,108,223,143,46,67,182,243,
    189,64,108,223,207,51,67,213,120,245,64,98,53,158,60,67,100,59,41,65,41,252,67,67,205,204,90,65,6,33,77,67,129,149,146,65,108,195,117,82,67,113,61,168,65,108,223,15,89,67,53,94,203,65,108,215,227,93,67,217,206,235,65,108,236,241,96,67,225,122,2,66,108,
    190,255,99,67,68,11,15,66,108,238,220,101,67,51,179,24,66,98,31,133,106,67,143,194,48,66,37,198,109,67,135,150,72,66,6,225,111,67,68,11,98,66,108,215,195,112,67,119,190,108,66,108,217,78,113,67,201,118,119,66,108,213,216,113,67,141,23,129,66,108,242,
    82,114,67,154,153,140,66,108,188,84,114,67,63,117,206,66,108,197,128,115,67,178,157,210,66,108,199,171,116,67,150,195,214,66,108,250,30,119,67,121,233,217,66,98,16,120,120,67,84,163,219,66,37,198,122,67,100,251,222,66,47,61,124,67,129,85,225,66,108,240,
    231,126,67,166,155,229,66,108,94,26,129,67,133,107,236,66,108,104,193,130,67,88,57,243,66,108,119,174,131,67,96,37,248,66,98,20,62,135,67,205,140,5,67,18,83,137,67,174,199,15,67,137,33,138,67,209,194,27,67,108,115,88,138,67,158,239,30,67,108,115,88,138,
    67,207,215,40,67,108,104,33,138,67,215,3,44,67,98,150,83,137,67,201,246,55,67,147,72,135,67,205,12,66,67,10,199,131,67,203,97,75,67,108,104,161,130,67,211,109,78,67,108,225,26,129,67,176,146,81,67,108,246,40,127,67,201,182,84,67,108,244,125,124,67,178,
    221,86,67,98,43,7,123,67,205,12,88,67,23,153,120,67,188,212,89,67,23,25,119,67,170,209,90,67,108,250,94,116,67,190,159,92,67,108,211,109,114,67,164,240,95,67,98,49,72,109,67,219,185,104,67,45,114,103,67,213,88,112,67,23,89,96,67,186,137,119,67,98,18,
    99,86,67,236,209,128,67,55,137,76,67,233,102,132,67,43,7,64,67,227,133,135,67,108,205,12,59,67,215,195,136,67,108,209,34,55,67,213,136,137,67,98,10,247,44,67,213,136,139,67,12,226,34,67,238,204,140,67,8,12,24,67,229,112,141,67,108,244,125,20,67,233,166,
    141,67,108,238,28,12,67,236,177,141,67,108,225,186,3,67,80,189,141,67,108,233,38,0,67,236,145,141,67,98,248,211,223,66,231,203,140,67,66,224,193,66,104,145,138,67,74,140,165,66,229,208,134,67,98,53,94,147,66,82,104,132,67,0,0,133,66,209,226,129,67,106,
    60,105,66,188,116,124,67,108,109,231,90,66,203,65,121,67,108,51,51,80,66,203,97,118,67,98,8,44,52,66,178,221,110,67,156,196,28,66,193,10,103,67,16,88,11,66,172,92,95,67,108,231,251,5,66,184,254,92,67,108,10,215,252,65,217,206,91,67,98,154,153,186,65,
    207,151,86,67,6,129,131,65,172,220,79,67,190,159,50,65,182,211,71,67,108,8,172,18,65,168,198,68,67,108,47,221,244,64,211,205,65,67,98,215,163,184,64,172,28,62,67,197,32,132,64,182,243,57,67,86,14,61,64,190,223,53,67,108,51,51,3,64,184,190,50,67,108,158,
    239,183,63,221,36,47,67,108,133,235,81,63,186,137,43,67,108,96,229,16,63,201,182,39,67,108,45,178,157,62,215,227,35,67,108,96,229,16,63,164,16,32,67,108,133,235,81,63,172,60,28,67,108,158,239,183,63,209,162,24,67,108,51,51,3,64,174,7,21,67,108,244,253,
    60,64,174,231,17,67,98,78,98,132,64,217,206,13,67,215,163,184,64,186,169,9,67,143,194,245,64,186,233,5,67,108,178,157,19,65,203,225,2,67,108,199,75,91,65,186,73,248,66,108,86,14,142,65,84,163,238,66,108,211,77,188,65,182,115,227,66,108,70,182,212,65,
    59,223,222,66,98,197,32,226,65,166,91,220,66,104,145,243,65,80,77,217,66,6,129,251,65,129,21,216,66,108,182,243,4,66,178,221,213,66,108,109,103,8,66,137,193,210,66,108,59,223,11,66,109,167,207,66,108,18,3,13,66,133,235,128,66,108,199,75,15,66,27,175,
    119,66,98,98,144,16,66,135,22,114,66,213,120,19,66,242,210,103,66,180,200,21,66,59,223,96,66,108,207,247,25,66,76,55,84,66,108,166,155,40,66,2,171,54,66,108,242,210,49,66,176,242,40,66,108,43,7,59,66,100,59,27,66,108,141,23,76,66,127,234,6,66,108,35,
    91,100,66,184,30,223,65,108,174,199,110,66,233,38,207,65,98,205,76,125,66,145,237,184,65,57,180,132,66,184,30,170,65,12,2,144,66,96,229,146,65,98,115,40,161,66,139,108,95,65,90,36,177,66,238,124,41,65,78,162,194,66,63,53,246,64,108,199,11,205,66,219,
    249,190,64,108,195,117,215,66,94,186,149,64,108,190,223,225,66,57,180,88,64,108,150,195,234,66,57,180,40,64,98,102,166,239,66,63,53,14,64,248,19,247,66,139,108,215,63,37,70,251,66,139,108,183,63,108,236,113,1,67,227,165,123,63,108,201,150,10,67,190,159,
    122,63,108,225,186,19,67,35,219,121,63,99,109,248,243,1,67,2,43,86,66,108,199,203,252,66,225,250,87,66,98,12,130,207,66,43,135,99,66,102,102,169,66,174,71,130,66,57,244,134,66,80,13,159,66,108,203,97,130,66,59,223,162,66,108,207,119,114,66,92,15,172,
    66,108,2,43,96,66,113,61,181,66,108,158,239,85,66,129,149,187,66,98,123,20,43,66,158,47,214,66,98,144,15,66,109,103,241,66,6,129,254,65,193,170,8,67,108,37,6,246,65,158,207,12,67,108,27,47,240,65,205,44,17,67,98,219,249,236,65,182,147,19,67,197,32,233,
    65,186,233,22,67,240,167,231,65,201,150,24,67,108,207,247,228,65,209,162,27,67,108,135,22,229,65,162,101,44,67,108,70,182,232,65,188,20,48,67,98,240,167,242,65,221,36,58,67,82,56,2,66,203,1,67,67,197,160,16,66,188,52,76,67,108,2,171,22,66,176,18,80,67,
    108,233,166,31,66,195,149,84,67,108,190,159,40,66,213,24,89,67,108,158,239,48,66,162,133,92,67,98,106,60,97,66,201,118,112,67,102,166,148,66,221,20,128,67,248,19,191,66,211,157,132,67,108,170,113,198,66,207,103,133,67,108,141,23,208,66,90,52,134,67,108,
    125,191,217,66,229,0,135,67,108,166,27,225,66,90,116,135,67,98,98,208,236,66,231,43,136,67,53,222,249,66,223,175,136,67,23,57,3,67,211,237,136,67,108,215,3,6,67,219,9,137,67,108,244,125,12,67,238,252,136,67,108,207,247,18,67,92,239,136,67,108,227,101,
    22,67,211,189,136,67,98,53,254,32,67,215,35,136,67,2,43,42,67,92,255,134,67,35,187,51,67,233,22,133,67,108,186,137,55,67,215,83,132,67,108,225,154,59,67,223,79,131,67,98,6,161,67,67,86,78,129,67,252,41,74,67,215,99,126,67,33,16,81,67,190,191,120,67,108,
    225,186,83,67,170,145,118,67,108,209,194,87,67,190,159,114,67,108,193,202,91,67,217,174,110,67,108,188,52,94,67,215,227,107,67,98,31,69,99,67,168,6,102,67,254,180,103,67,168,166,95,67,20,142,107,67,201,182,88,67,108,238,188,109,67,168,198,84,67,108,240,
    135,111,67,197,192,80,67,98,12,162,114,67,180,200,73,67,20,238,116,67,215,227,66,67,31,133,118,67,209,194,59,67,108,221,100,119,67,182,211,55,67,108,240,7,120,67,203,97,51,67,108,186,169,120,67,158,239,46,67,108,203,65,121,67,199,11,38,67,108,219,25,
    121,67,207,215,32,67,108,229,240,120,67,209,162,27,67,108,217,142,120,67,188,52,24,67,98,31,197,119,67,211,45,17,67,31,165,118,67,217,142,11,67,47,157,116,67,184,126,4,67,108,238,92,115,67,168,38,0,67,108,211,205,113,67,100,123,248,66,98,47,189,109,67,
    104,17,228,66,53,254,104,67,80,77,211,66,51,19,98,67,133,235,192,66,108,248,211,94,67,186,73,184,66,108,199,171,91,67,145,109,177,66,98,47,61,79,67,121,105,150,66,37,6,63,67,162,133,129,66,18,131,45,67,152,238,107,66,108,223,15,41,67,92,15,102,66,108,
    190,223,36,67,176,242,97,66,98,0,32,32,67,217,78,93,66,35,123,28,67,2,171,90,66,49,40,23,67,18,3,88,66,108,219,121,19,67,27,47,86,66,108,201,182,10,67,27,47,86,66,108,248,243,1,67,2,43,86,66,99,109,190,255,24,67,182,147,84,67,108,0,0,25,67,0,0,85,67,
    108,59,255,24,67,186,105,85,67,108,51,211,24,67,186,105,85,67,108,190,255,24,67,182,147,84,67,99,109,219,121,3,67,37,6,150,65,108,217,174,0,67,178,157,152,65,98,106,60,232,66,211,77,164,65,41,156,207,66,80,141,190,65,90,228,178,66,4,86,236,65,108,219,
    121,168,66,145,237,252,65,108,227,165,163,66,117,147,3,66,98,248,19,158,66,225,122,9,66,61,138,150,66,117,147,19,66,29,90,144,66,152,110,29,66,108,174,7,140,66,217,78,36,66,108,121,105,133,66,68,139,49,66,108,141,151,125,66,193,202,62,66,108,207,247,
    115,66,27,175,75,66,108,35,91,106,66,117,147,88,66,108,133,107,101,66,119,62,97,66,98,82,184,98,66,18,3,102,66,139,236,94,66,92,143,109,66,0,0,93,66,18,3,114,66,108,250,126,89,66,135,22,122,66,108,250,254,86,66,88,249,129,66,108,18,131,84,66,96,229,134,
    66,108,18,131,84,66,186,201,159,66,108,158,239,95,66,137,65,154,66,98,82,56,102,66,76,55,151,66,197,160,112,66,186,137,146,66,74,12,119,66,178,221,143,66,98,8,172,159,66,117,147,99,66,8,172,201,66,100,187,62,66,70,54,247,66,100,59,51,66,108,129,85,255,
    66,2,43,49,66,108,250,190,4,67,250,254,47,66,108,242,210,9,67,217,206,46,66,108,221,36,14,67,225,122,47,66,98,4,246,21,67,27,175,48,66,25,36,28,67,117,147,51,66,8,44,35,67,193,74,57,66,108,211,237,38,67,35,91,60,66,108,223,79,43,67,242,82,65,66,98,49,
    72,51,67,35,91,74,66,29,58,58,67,35,91,85,66,10,183,65,67,168,198,100,66,108,205,12,70,67,76,183,109,66,108,207,215,73,67,76,55,119,66,98,53,158,81,67,141,87,133,66,39,17,88,67,96,101,143,66,41,124,94,67,68,203,155,66,108,213,88,96,67,96,101,159,66,108,
    225,58,96,67,182,243,146,66,108,231,27,96,67,137,129,134,66,108,229,144,95,67,170,113,130,66,98,10,215,94,67,68,11,122,66,0,64,94,67,127,234,115,66,37,230,92,67,209,34,105,66,108,215,195,91,67,184,30,96,66,108,244,253,89,67,92,143,85,66,98,23,121,83,
    67,209,162,46,66,20,46,73,67,168,70,12,66,45,242,62,67,238,124,246,65,98,18,227,47,67,102,102,196,65,43,135,34,67,102,102,166,65,12,162,21,67,70,182,153,65,108,248,243,17,67,184,30,150,65,108,201,182,10,67,86,14,150,65,108,219,121,3,67,37,6,150,65,99,
    101,0,0 };

//==============================================================================
VectorScope::VectorScope ()
{
    
    logoPath.loadPathFromData (pathData, sizeof (pathData));
//    setSize (277, 394);
    
}

VectorScope::~VectorScope()
{
    
}

//==============================================================================
void VectorScope::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);
    
    Path path;
    
    float xOffset = 15.f;
    float yOffset = 38.f;
   
    Rectangle<float> rect = logoPath.getBounds();
    Rectangle<int> rect2 = getLocalBounds();
    
    g.setColour (Colours::black);
    g.fillPath (logoPath, RectanglePlacement (RectanglePlacement::stretchToFit)
                .getTransformToFit (logoPath.getBounds(),
                                    getLocalBounds().toFloat()));
    
    float lineLength = 160;
    g.addTransform(AffineTransform::rotation(-M_PI / 4, lineLength / 2. + xOffset, lineLength / 2. + yOffset));

    
    // Vertical line
    path.addLineSegment(Line<float> (lineLength / 2. + xOffset, 0 + yOffset, lineLength / 2. + xOffset, lineLength + yOffset), 1.);
    
    // Horizontal line
    path.addLineSegment(Line<float> (xOffset, lineLength / 2. + yOffset, lineLength + xOffset, lineLength / 2.  + yOffset), 1.);
    
    g.setColour (Colours::black);
    g.fillPath (path);

    Path vectorScopePath;

    // Now iterate over points.
    int count = 0;
    float alpha = 0;
    for (auto& points : allPoints)
    {
        if ((currentPointsIndex - count + numberVectorBuffers) % numberVectorBuffers == 0)
        {
            // Current array is 'brightest'
            alpha = 1;
        } else
        {
            // Set older immediately to less than 0.5 alpha.
            alpha = 0.5 - ((currentPointsIndex - count + numberVectorBuffers) % numberVectorBuffers) * 0.02;
        }
        
        g.setColour(Colour::fromFloatRGBA(0, 0 , 0, alpha)) ;
        
        for (auto& point : points)
        {
            float temp = point.x;
            jassert(temp < 1.5);
            g.setPixel(lineLength / 2. + xOffset + point.x * lineLength / 4., lineLength / 2. + yOffset - point.y * lineLength / 4. );
//            vectorScopePath.addEllipse(200 + point.x * 100, 200 - point.y * 100, 5, 5);
        }
        count++;
//        g.fillPath(vectorScopePath, AffineTransform::rotation(-M_PI / 4, 200, 200));
    }
    

    
}

void VectorScope::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
    
    //    image->setBounds (0, 50, 450, 159);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void VectorScope::setCurrentPointArray(std::array<juce::Point<float>, numberVectorPoints> currentPoints)
{
    currentPointsIndex = (currentPointsIndex + 1) % numberVectorBuffers;
    allPoints[currentPointsIndex] = currentPoints;
    
}


