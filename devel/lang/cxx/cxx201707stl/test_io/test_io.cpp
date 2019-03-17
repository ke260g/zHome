#include<iostream>
#include<sstream>
#include<fstream>
#include<system_error>
#include<locale>
using namespace std;

void system_error_code(void) {
    std::system_error sec;
    cout << sec.code() << endl;
    cout << sec.what() << endl;
}

#if 1 /* members from ios */
void state_flags_manipu(void) {
    std::stringstream sstrm;
    // access
    bool gb = sstrm.good();     // goodbit
    bool eb = sstrm.eof();      // eofbit
    bool fb = sstrm.fail();     // failbit
    bool bb = sstrm.bad();      // badbit
    sstrm.setstate(
            ios::iostate::_S_eofbit |
            ios::iostate::_S_failbit |
            ios::iostate::_S_badbit);
    cout << sstrm.rdstate() << endl;

    // clear() then set badbit
    sstrm.clear();
    sstrm.setstate(ios::iostate::_S_badbit);
    cout << "iostate::badbit is " << sstrm.rdstate() << endl;

    // clear() then set end-of-file bit
    sstrm.clear();
    sstrm.setstate(ios::iostate::_S_eofbit);
    cout << "iostate::eofbit is " << sstrm.rdstate() << endl;

    // clear() then set fail bit
    sstrm.clear();
    sstrm.setstate(ios::iostate::_S_failbit);
    cout << "iostate::failbit is " << sstrm.rdstate() << endl;

    /* it's meaningless to setstate(ios::iostate::_S_goodbit)
     * as goodbit is `0', zero */
}

void copyfmt_fill(void) {
    stringstream old_cout_format;
    old_cout_format.copyfmt(cout);

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout.width(7);
    if(cout.fill('-') == '-')
        cout << "fill() return its passing parameter" << endl;
    cout << 100 << endl;

    cout.copyfmt(old_cout_format);
    cout << 100 << endl;
}

// imbue(), tie(), rdbuf()
// re-direct cout to file with rdbuf()
void others(void) {
    // imbue()
    std::locale mylocale("");   // get glocal locale
    cout.imbue(mylocale);       // imbue global locale
    cout << 3.14159 << endl;

    // tie(), by default, cin/cerr/clog are tied to cout
    fstream *fs = new fstream("test_tie.txt", ios::out); // ok
    // ostream cout_rese = *(cout.tie()); // error
    cin.tie(fs);
    *cin.tie(fs) << "inserted to file";
    cin.tie(&cout);
    fs->close(); delete fs; fs = nullptr;

    // rdbuf(), re-direct cout to a file
    streambuf *cout_buf;
    ofstream *ofs = new ofstream("test_rdbuf.txt", ios::out);
    cout_buf = cout.rdbuf();
    cout.rdbuf(ofs->rdbuf());
    cout << "This is written to the file" << endl;
    cout.rdbuf(cout_buf);
    cout << "This is written to console" << endl;
    ofs->close(); delete ofs; ofs = nullptr;
}
#endif

#if 1 /* members from ios_base */
void ios_flags(void) {
    ios::fmtflags prev_cout_flags = cout.flags();

#if 1 /* set flags atomically */
    /* ios::basefield must be one of three */
    cout.setf(ios::hex, ios::basefield);
    // cout.setf(ios::dec, ios::basefield);
    //cout.setf(ios::oct, ios::basefield);
    cout.setf(ios::showbase); // cout.unsetf(ios::showbase);

    /* ios::floatfield can be neither of two */
    cout.setf(ios::fixed, ios::floatfield);
    // cout.setf(ios::scientific, ios::floatfield);
    // cout.unsetf(ios::floatfield);
    cout.setf(ios::showpoint);

    /* ios::adjustfield must be one of three */
    cout.setf(ios::right, ios::adjustfield);
    // cout.setf(ios::internal, ios::adjustfield);
    // cout.setf(ios::left, ios::adjustfield);
#endif

    /* Daily set flags in a friendly way */
    cout.flags(ios::right |
            ios::hex |
            ios::showbase |
            ios::fixed);

    cout.precision(8);
    cout.width(20);

    cout << 100 << endl;
    cout << 3.14 << endl;

    cout.flags(prev_cout_flags);
    cout << "-------------" << endl;

    cout << 100 << endl;
    cout << 3.14 << endl;
}

void xalloc_iword_pword(void) {
    int index = cout.xalloc();
    cout << ++cout.iword(index) << " #>> 1st line" <<  endl;
    cout << ++cout.iword(index) << " #>> 2nd line" <<  endl;
    cout << ++cout.iword(index) << " #>> 3th line" <<  endl;
    cout << "-------------" << endl;

    cout.pword(0) = const_cast<char *>("0 pword in cout");
    cout.pword(1) = const_cast<char *>("1 pword in cout");
    cout << static_cast<const char *>(cout.pword(0)) << endl;
    cout << static_cast<const char *>(cout.pword(1)) << endl;
}
#endif

void io_fstream(void) {
#if 0 /* ostream, ofstream */
    ofstream ofs("ostream_test.txt", ios::out);
    if(ofs.is_open())
        cout << "ostream_test.txt" << " is opened" << endl;
    else {
        cout << "ostream_test.txt" << " can't be opened" << endl;
        cout << "exit!" << endl;
        return;
    }

    // this is a dangerous operation, just for teaching
    ostream *ostrm = static_cast<ostream *>(&ofs);

    ostrm->put('@');
    //ostrm->write("adcd", 4);
    ostrm->write("adcd", 10);
    /* a bug here will be appearred,
     * what if stream-length is shorter than position pointer? */

    //ostrm->flush(); // discard any un-write chars
    //ostrm->seekp(5);
    ostrm->write("xyz", 3);
    cout << ostrm->tellp() << endl;
    ofs.close();
#endif

#if 1 /* istream, ifstream */
    /* istream::unget(), cancel the previous get-operation
     * means decrease pos_ptr buffer restores the last data */
    ifstream ifs("package.use", ios::in);
    if(ifs.is_open())
        cout << "package.use" << " is opened" << endl;
    else {
        cout << "package.use" << " can't be opened" << endl;
        cout << "exit!" << endl;
        return;
    }

    // read file into a string class
    stringstream sstrm;
    sstrm << ifs.rdbuf(); // ::rdbuf() will make pos to the end
    string fileString = sstrm.str();
    cout << "file has " << fileString.size() << " chars" << endl;
    ifs.seekg(0); // set back
    stringbuf sbuf;

    // this is a dangerous operation, just for teaching
    istream * istrm = static_cast<istream *>(&ifs);

    cout << istrm->gcount() << endl; // returns number of last get*
    char c;
    c = istrm->get(); c = istrm->get(); c = istrm->get();
    char line[1024];
    istrm->getline(line, 1024, '\n');
    cout << "previously get " << istrm->gcount() << " chars" << endl;

    // cout << "position: " << istrm->tellg() << endl;
    // istrm->seekg(10);
    // cout << "set position 10" << endl;
    // istream::peek(), return next char but not extract
    cout << static_cast<const char>(istrm->peek()) << endl;
    cout << static_cast<const char>(istrm->peek()) << endl;
    // istrm->ignore(); // extract and discard
    // istrm->sync(); // remove any unread chars in the stream

    // example for www.cplusplus.com
    // putback usage
    cout << "Please enter a number or a word: ";
    c = cin.get();
    if ( (c >= '0') && (c <= '9') ) {
        int n;
        std::cin.putback (c);
        std::cin >> n;
        std::cout << "You entered a number: " << n << endl;
    } else {
        std::string str;
        std::cin.putback (c);
        getline (std::cin,str);
        std::cout << "You entered a word: " << str << endl;
    }
#endif
}

void sstream(void) {
    int a = 10;
    float b = 3.14;
    stringstream fmtstr;
    fmtstr << a << " " << b;
    cout << fmtstr.str();
}

int main(int argc, char **argv) {
    // system_error_code();

    /*****/
    // state_flags_manipu();
    // copyfmt_fill();
    // others();
    ///////

    /*****/
    // ios_flags();
    // xalloc_iword_pword();
    //////

    /*****/
    //io_fstream();
    sstream();
    //////
    return 0;
}
