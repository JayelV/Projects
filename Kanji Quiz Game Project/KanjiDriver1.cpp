#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;

#include "Kanji.h"

int main () {
    /* main() for driver */

    cerr << "*** Driver program for Kanji class ***" << endl;

    /*Section 1*/
    cerr << endl << "1. Tests of typical constructor:" << endl;

    cerr << "Kanji kan1(36);" << endl;
    Kanji kan1(36);
    cerr << "  kan1.display_kstats():  "; kan1.display_kstats();   cerr << endl;

    cerr << "Kanji kan4(14, \"文\", \"sentence\", \"ぶん,もん\", \"ふみ\");" << endl;
    Kanji kan4(14, "文", "sentence", "ぶん,もん", "ふみ");
    cerr << "  kan4.display_kstats():  "; kan4.display_kstats();   cerr << endl;

    cerr << "Kanji kan5(\"曜\");" << endl;
    Kanji kan5("曜");
    cerr << "  kan5.display_kstats():  "; kan5.display_kstats();   cerr << endl;

    /*Section 2*/
    cerr << endl << "2. Test of default constructor:" << endl;
    cerr << "Kanji kan2;" << endl;
    Kanji kan2;
    cerr << "  kan2.display_kstats():  "; kan2.display_kstats();   cerr << endl;

    /*Section 3*/
    cerr << endl << "3. Test of copy constructor:" << endl;
    cerr << "Kanji kan3(kan1);" << endl;
    Kanji kan3(kan1);
    cerr <<"  kan3.display_kstats():  "; kan3.display_kstats();   cerr << endl;

    /*Section 4*/
    cerr << endl << "4. Initial display() of all variables:" << endl
        << "  kan1.display_kstats():  "; kan1.display_kstats(); cerr << endl
        << "  kan2.display_kstats():  "; kan2.display_kstats(); cerr << endl
        << "  kan3.display_kstats():  "; kan3.display_kstats(); cerr << endl
        << "  kan4.display_kstats():  "; kan4.display_kstats(); cerr << endl
        << "  kan5.display_kstats():  "; kan5.display_kstats(); cerr << endl;

    /*Section 5*/
    cerr << endl << "5. Tests of assignment operator:" << endl;
    cerr << "  kan5.display_kstats():  "; kan5.display_kstats();   cerr << endl;
    cerr << "  kan1.display_kstats():  "; kan1.display_kstats();   cerr << endl;
    cerr << "(kan5 = kan1).display_kstats():  "; 
    (kan5 = kan1).display_kstats();   cerr << endl;
    cerr << "  kan1.display_kstats():  "; kan5.display_kstats();   cerr << endl;

    /*Section 6*/
    cerr << endl << "6. Test of get_methods:" << endl;
    cerr <<"  kan1.display_kstats():  "; kan1.display_kstats();   cerr << endl;
    cerr << "kan1.get_meaning() returns "
        << kan1.get_meaning() << endl;
    cerr << "kan1.get_onyomi(0) returns "
        << kan1.get_onyomi(0) << endl;
    cerr << "kan1.get_kunyomi(3) returns "
        << kan1.get_kunyomi(3) << endl;
    cerr << "kan1.get_kunyomi() returns "
        << kan1.get_kunyomi() << endl;
    cerr << "kan5.make_kstring() returns "
        << kan5.make_kstring() << endl;
    cerr << "kan2.find_kanji_line(\"金\") returns "
        << kan2.find_kanji_line("金") << endl;

    /*Section 7*/
    cerr << endl << "7. Test of methods with state changes:" << endl;
    cerr <<"  kan1.make_kstring():  "; kan1.make_kstring();   cerr << endl;

    cerr << "kan1.make_kstring(100) returns "
        << kan1.make_kstring(100) << endl;
    cerr <<"  kan1.display_kstats():  "; kan1.display_kstats();   cerr << endl;


    /*Section 8*/
    cerr << endl << "8. Further test of assignment operator" << endl;
    cerr << "  kan2.display_kstats():  "; kan2.display_kstats();   cerr << endl;
    cerr << "  kan4.display_kstats():  "; kan4.display_kstats();   cerr << endl;
    cerr << "(kan2 = kan4).build_kstats(125);" << endl;
    (kan2 = kan4).build_kstats(82);
    cerr << "  kan2.display_kstats():  "; kan2.display_kstats();   cerr << endl;

    /*Section 9*/
    cerr << endl << "9. final display_kstats() of all variables:" << endl
        << "  kan1.display_kstats():  "; kan1.display_kstats(); cerr << endl
        << "  kan2.display_kstats():  "; kan2.display_kstats(); cerr << endl
        << "  kan3.display_kstats():  "; kan3.display_kstats(); cerr << endl
        << "  kan4.display_kstats():  "; kan4.display_kstats(); cerr << endl
        << "  kan5.display_kstats():  "; kan5.display_kstats(); cerr << endl;

    return 0;

}