#include <ustl.h>
using namespace ustl;

int main (void)
{
    const u_char magic_Char = 'c';
    const u_short magic_Short = 1234;
    const long magic_Int = -12345678;
    const u_long magic_UInt = 12345678;
    const float magic_Float = 123.45678;
    const double magic_Double = 123456789123456.789;
    const bool magic_Bool = true;

    char c = magic_Char;
    u_char uc = magic_Char;
    int i = magic_Int;
    short si = magic_Short;
    long li = magic_Int;
    u_int ui = magic_UInt;
    u_short usi = magic_Short;
    u_long uli = magic_UInt;
    float f = magic_Float;
    double d = magic_Double;
    bool bv = magic_Bool;

    string b;
    ostringstream os (b);

    os << c << endl;
    os << uc << endl;
    os << bv << endl;
    os << i << endl;
    os << ui << endl;
    os << li << endl;
    os << uli << endl;
    os << f << endl;
    os << d << endl;
    os << si << endl;
    os << usi << endl << ends; 
    b.resize (os.pos());
    cout << os.pos() << " bytes written" << endl;

    c = 0;
    uc = 0;
    bv = false;
    i = ui = li = uli = 0;
    f = 0; d = 0;
    si = usi = 0;

    istringstream is (b);
    is >> c;
    is >> uc;
    is >> bv;
    is >> i;
    is >> ui;
    is >> li;
    is >> uli;
    is >> f;
    is >> d;
    is >> si;
    is >> usi;

    cout << "Values:" << endl;
    cout.format ("char:    '%c'\n", static_cast<int>(c));
    cout.format ("u_char:  '%c'\n", static_cast<int>(uc));
    cout.format ("bool:    %d\n", static_cast<int>(bv));
    cout.format ("int:     %d\n", i);
    cout.format ("u_int:   %d\n", ui);
    cout.format ("long:    %ld\n", li);
    cout.format ("u_long:  %ld\n", uli);
    cout.format ("float:   %.2f\n", f);
    cout.format ("double:  %.2f\n", d);
    cout.format ("short:   %hd\n", static_cast<int>(si));
    cout.format ("u_short: %hd\n", static_cast<int>(usi));
    cout << endl;

    cout << "Dump:" << endl;
    cout << reinterpret_cast<const char*>(b.cdata()) << endl;
    cout << endl;

    return (0);
}

