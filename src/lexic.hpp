#ifndef LEXIC
#define LEXIC

#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include "token.hpp"

#define inFileName "input.txt"
#define outFileName "output.txt"

class Lexic {
private:
    enum {
        q0, // \s
        q1, // \n
        q2, // \t
        q3, // a-z A-Z
        q4, // 0-9
        q5, // +
        q6, // -
        q7, // *
        q8, // /
        q9, // :
        q10,// <
        q11,// >
        q12,// <=
        q13,// >=
        q14,// =
        q15,// ==
        q16,// !
        q17,// !=
        q18,// (
        q19,// )
        q20,// 0-9.
        q21,// 0-9.0-9
        q22,// CR
        qer,// ERROR
        NS
    };

    enum {
        i0, // \s
        i1, // \n
        i2, // \t
        i3, // a-z, A-Z
        i4, // 0-9
        i5, // +
        i6, // -
        i7, // *
        i8, // /
        i9, // :
        i10,// <
        i11,// >
        i12,// =
        i13,// !
        i14,// (
        i15,// )
        i16,// _
        i17,// .
        i18,// CR
        inv,// INVALID
        NI
    };

    int stateMachine[NS][NI] = {
    //	  \s , \n , \t ,azAZ, 0-9,  + ,  - ,  * ,  / ,  : ,  < ,  > ,  = ,  ! ,  ( ,  )    _	.    CR
    //	  i0 , i1 , i2 , i3 , i4 , i5 , i6 , i7 , i8 , i9 , i10, i11, i12, i13, i14, i15, i16, i17, i18, inv
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q0 \s
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q1 \n
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q2 \t
        { q0 , q1 , q2 , q3 , q3 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q3 azAZ
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, q20, q22, qer},// q4 0-9
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q5 +
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q6 -
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q7 *
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q8 /
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},// q9 :
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q12, q16, q17, q18,  q3, qer, q22, qer},//q10 <
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q13, q16, q17, q18,  q3, qer, q22, qer},//q11 >
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q12 <=
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q13 >=
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q15, q16, q17, q18,  q3, qer, q22, qer},//q14 =
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q15 ==
        { qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, q17, qer, qer, qer, qer, qer, qer, qer},//q16 !
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q17 !=
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q18 (
        { q0 , q1 , q2 , q3 , q4 , q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q19 )
        { qer, qer, qer, qer, q21, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer},//q20 0-9.
        { q0 , q1 , q2 , q3 , q21, q5 , q6 , q7 , q8 , q9 , q10, q11, q14, q16, q17, q18,  q3, qer, q22, qer},//q21 0-9.0-9
        { qer, q1 , qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer},//q22 CR
        { qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer, qer} //qer ERROR
    };

    int tokenMachine[NS][NI] = {
    //	  \s , \n , \t ,azAZ, 0-9,  + ,  - ,  * ,  / ,  : ,  < ,  > ,  = ,  ! ,  ( ,  )    _	.
    //	  i0 , i1 , i2 , i3 , i4 , i5 , i6 , i7 , i8 , i9 , i10, i11, i12, i13, i14, i15, i16, i17, inv
    	{ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 },// q0 \s
    	{  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },// q1 \n
    	{  1 ,  1 , -1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 },// q2 \t
    	{  2 ,  2 ,  2 , -1 , -1 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 , -1 ,  2 ,  2 },// q3 azAZ
    	{  3 ,  3 ,  3 ,  3 , -1 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 ,  3 , -1 ,  3 },// q4 0-9
    	{  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 },// q5 +
    	{  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 },// q6 -
    	{  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 ,  7 },// q7 *
    	{  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 ,  8 },// q8 /
    	{  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 ,  9 },// q9 :
    	{ 10 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , -1 , 10 , 10 , 10 , 10 , 10 , 10 },//q10 <
    	{ 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 , 11 , -1 , 11 , 11 , 11 , 11 , 11 , 11 },//q11 >
    	{ 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 , 12 },//q12 <=
    	{ 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 , 13 },//q13 >=
    	{ 14 , 14 , 14 , 14 , 14 , 14 , 14 , 14 , 14 , 14 , 14 , 14 , -1 , 14 , 14 , 14 , 14 , 14 , 14 },//q14 =
    	{ 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 , 15 },//q15 ==
    	{ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 },//q16 !
    	{ 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 , 16 },//q17 !=
    	{ 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 , 17 },//q18 (
    	{ 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 , 18 },//q19 )
    	{ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 },//q20 0-9.
    	{  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 ,  4 },//q21 0-9.0-9
        { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 },//q22 CR
    	{ 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666, 666},//qer ERROR
    };

    std::vector < std::pair < std::string, int > > lexTokens;
    std::map< std::string, int > reserved;
    int tokenPosition;

    void Analyze(char *);
    int getValue(char c);
    void init();
    void Error();

public:
    int type;
    std::string symbol;

    Lexic (char *);
    virtual ~Lexic () {};

};

#endif
