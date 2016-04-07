#ifndef LEXIC
#define LEXIC

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
        q10,// <
        q11,// >
        q12,// <=
        q13,// >=
        q14,// =
        q15,// ==
        q16,// !=
        q17,// (
        q18,// )
        q19,// :
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
        i10,// <
        i11,// >
        i12,// =
        i13,// !
        i14,// (
        i15,// )
        i16,// :
        inv,// INVALID
        NI
    };

    int stateMachine[NS][NI] = {
        //
        //
        {}
    }
public:
    Lexic ();
    virtual ~Lexic ();

};

#endif
