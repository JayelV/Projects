/* driver program for Chapter. */

#include <iostream>
using namespace std;

#include "Chapter.h"
#include "Kanji.h"

/* main() for driver */

int main()
{

/*
     cerr << "*** Driver program for Chapter class ***" << endl;*/

     /*Section 1*/
     cerr << endl << "1. Tests of typical constructor:" << endl;

     cerr << "Chapter chap1(1);" << endl;
     Chapter chap1(1);
     cerr << "  chap1.display():  "; chap1.display();   cerr << endl;

     cerr << "Chapter chap2(2);" << endl;
     Chapter chap2(2);
     cerr << "  chap2.display():  "; chap2.display();   cerr << endl;

     cerr << "Chapter chap3(3);" << endl;
     Chapter chap3(3);
     cerr << "  chap3.display():  "; chap3.display();   cerr << endl;

     cerr << "Chapter chap4(4);" << endl;
     Chapter chap4(4);
     cerr << "  chap4.display():  "; chap4.display();   cerr << endl;

     cerr << "Chapter chap5(5);" << endl;
     Chapter chap5(5);
     cerr << "  chap5.display():  "; chap5.display();   cerr << endl;

     /*Section 2
     cerr << endl << "2. Test of default constructor:" << endl;
     cerr << "Chapter chap3;" << endl;
     Chapter chap3;
     cerr << "  chap3.display():  "; chap3.display();   cerr << endl;*/

     /*Section 3
     cerr << endl << "3. Test of copy constructor:" << endl;
     cerr << "Chapter chap4(chap1);" << endl;
     Chapter chap4(chap1);
     cerr <<"  chap4.display():  "; chap4.display();   cerr << endl;*/

     /*Section 4*/ 
     cerr << endl << "4. Initial display() of all variables:" << endl
          << "  chap1.display():  "; chap1.display(); cerr << endl
          << "  chap2.display():  "; chap2.display(); cerr << endl
          << "  chap3.display():  "; chap3.display(); cerr << endl
          << "  chap4.display():  "; chap4.display(); cerr << endl
          << "  chap5.display():  "; chap5.display(); cerr << endl;

     /*Section 5
     cerr << endl << "5. Tests of assignment operator:" << endl;
     cerr << "  chap1.display():  "; chap1.display();   cerr << endl;
     cerr << "  chap2.display():  "; chap2.display();   cerr << endl;
     cerr << "(chap1 = chap2).display():  "; 
     (chap1 = chap2).display();   cerr << endl;
     cerr << "  chap2.display():  "; chap2.display();   cerr << endl;*/

     /*Section 6*/ 
     cerr << endl << "6. Test of get_ methods:" << endl;
     cerr << "  chap4.get_character(1):  " << chap4.get_character(1) << endl;
     cerr << "  chap2.display_kstats(12):  " << chap2.display_kstats(1) << endl;
     cerr << "  chap5.display_kstats(\"待\"):  " << chap5.display_kstats("待") << endl;
     cerr << "  chap4.display_kstats(\"食\"):  " << chap4.display_kstats("食") << endl;
     cerr << "  chap3.make_chstring():  " << chap3.make_chstring() << endl;

     /*Section 7
     cerr << endl << "7. Test of methods with state changes:" << endl;
     cerr <<"  chap1.display():  "; chap1.display();   cerr << endl;*/

     /*Section 8
     cerr << endl << "8. Further test of assignment operator" << endl;
     //cerr << "  chap3.display():  "; chap3.display();   cerr << endl;
     cerr << "  chap4.display():  "; chap4.display();   cerr << endl;
     cerr << "  chap4.display():  "; chap4.display();   cerr << endl;*/

     /*Section 9*/
     cerr << endl << "9. final display() of all variables:" << endl
          << "  chap1.display():  "; chap1.display(); cerr << endl
          << "  chap2.display():  "; chap2.display(); cerr << endl
          << "  chap3.display():  "; chap3.display(); cerr << endl
          << "  chap4.display():  "; chap4.display(); cerr << endl
          << "  chap5.display():  "; chap5.display(); cerr << endl;

     cerr << endl;
     Chapter chap(0);
     cerr << "display all chapters" << endl;
     chap.display_all_chapters();
       
  return 0;
}