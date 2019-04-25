#include <iostream>
#include "Mezo.h"
#include "Jatekos.h"
#include "Monopoly.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    srand(time(NULL));
    Monopoly mon("input.txt");
    mon.jatssz(8);
    mon.megoldas();
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("Letrehozas + jatekosok konstruktorai","input1.txt")
{
    Monopoly mon("input.txt");
    Jatekos* jat1=mon.jatekosadatai(0);
    Jatekos* jat2=mon.jatekosadatai(1);
    Jatekos* jat3=mon.jatekosadatai(2);
    CHECK(jat1->getnev()=="David");
    CHECK(jat2->getnev()=="John");
    CHECK(jat3->getnev()=="Fred");
    CHECK(jat1->getvagyon()==10000);
    CHECK(jat2->getvagyon()==10000);
    CHECK(jat3->getvagyon()==10000);
    CHECK(jat1->jatszik());
    CHECK(jat2->jatszik());
    CHECK(jat3->jatszik());
    CHECK(jat1->getpozicio()==0);
    CHECK(jat2->getpozicio()==0);
    CHECK(jat3->getpozicio()==0);
}
TEST_CASE("Mezok konstruktorai")
{
    Monopoly mon("input.txt");
    Mezo* mez1=mon.mezoadatai(0);
    Mezo* mez2=mon.mezoadatai(1);
    Mezo* mez3=mon.mezoadatai(3);
    CHECK(mez1->getClass()=="Ingatlan");
    CHECK(mez2->getClass()=="Szerencse");
    CHECK(mez3->getClass()=="Szolgaltatas");
}
TEST_CASE("Jatekosok viselkedese","input2.txt")
{
    Monopoly mon1("input2.txt");
    mon1.jatssz();
    Jatekos* jat1=mon1.jatekosadatai(0);
    Jatekos* jat2=mon1.jatekosadatai(1);
    Jatekos* jat3=mon1.jatekosadatai(2);
    CHECK(jat1->ingatlanszam()==1);
    CHECK(jat2->ingatlanszam()==0);
    CHECK(jat3->ingatlanszam()==1);

}
TEST_CASE("Jatekosok kiesese","input1.txt")
{
    Monopoly mon("input.txt");
    CHECK(mon.jatekosokszama()==3);
    mon.jatssz();
    CHECK(mon.jatekosokszama()==2);
}
#endif
