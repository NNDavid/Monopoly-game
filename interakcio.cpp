#include "Mezo.h"
#include "Jatekos.h"
#include "Monopoly.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstdlib>
using namespace std;
void Jatekos::csodeljaras()
{
        for(unsigned int i=0;i<vasarolt.size();i++)
        vasarolt[i]->felszamol();
        jatekbanvan=false;
}
void Ingatlan::felszamol()
{
        tulajdonos=nullptr;
        vantulajdonosa=false;
        vanrajtahaz=false;
}
void Szolgaltatas::eljar(Jatekos* jat)
{
    jat->ujvagyon(-szolgaltatasar);
}
void Szerencse::eljar(Jatekos* jat)
{
    jat->ujvagyon(szerencsear);
}
void Ingatlan::eljar(Jatekos* jat)
{
    if(vantulajdonosa)
    {
        if(tulajdonos->getnev()==jat->getnev())
        {
            if(!vanrajtahaz)
            {
                if(jat->toke()>=hazar)
                {
                    if(jat->vasarolhat())
                    {
                        jat->ujvagyon(-hazar);
                        vanrajtahaz=true;
                    }
                    jat->kovlepes();
                }
            }
        }
        else
        {
            int fizetnivalo;
            if(vanrajtahaz) fizetnivalo=fizetahazar;
            else fizetnivalo=fizetalapar;
            jat->ujvagyon(-fizetnivalo);
            if(jat->csodotmond()) jat->csodeljaras();
            else tulajdonos->ujvagyon(fizetnivalo);
        }
    }
    else
    {
        if(jat->toke()>=alapar)
        {
            if(jat->vasarolhat())
            {
                jat->vasarol(this);
                jat->ujvagyon(-alapar);
                tulajdonos=jat;
                vantulajdonosa=true;
            }
            jat->kovlepes();

        }
    }
}
Monopoly::Monopoly(const string& fname)
{
    ifstream f;
    f.open(fname.c_str());
    if(f.fail()) {cout<<"Nincs ilyen file";exit(1);}
    else
    {
        dobasokszama=0;
        int nr;
        f>>nr;
        int szam=1;
        for(int i=0;i<nr;i++)
        {
            char tipus;
            f>>tipus;
            if(tipus=='P')
            {
                mezo.push_back(new Ingatlan(szam));
                szam++;
            }
            else if(tipus=='S')
            {
                int ar;
                f>>ar;
                mezo.push_back(new Szolgaltatas(ar));
            }
            else if(tipus=='L')
            {
                int ar;
                f>>ar;
                mezo.push_back(new Szerencse(ar));
            }
        }
        f>>nr;
        for(int i=0;i<nr;i++)
        {
            string nev;
            char tipus;
            f>>tipus;
            f>>nev;
            if(tipus=='G')
            {
                jatekos.push_back(new Moho(nev));
            }
            else if(tipus=='C')
            {
                jatekos.push_back(new Ovatos(nev));
            }
            else if(tipus=='T')
            {
                jatekos.push_back(new Taktikus(nev));
            }
        }
        f>>dobasokszama;
        dobasok=new int[dobasokszama];
        for(int i=0;i<dobasokszama;i++)
        {
            int c;
            f>>c;
            dobasok[i]=c;
        }
    }
}


void Monopoly::felszamoljatekosokat()
{
    vector<Jatekos*>::iterator it=remove_if(jatekos.begin(),jatekos.end(),A());
    jatekos.resize(std::distance(jatekos.begin(),it));
}
void Monopoly::jatssz(const int kor)
{
    if(dobasokszama>0)
    {
        jatekdobasokkal();
    }
    else
    {
        jatekdobasoknelkul(kor);
    }
}
void Monopoly::jatekdobasokkal()
{
   int mezokszama=mezo.size();
   int cdobas=0;
   while(cdobas<dobasokszama)
   {
        for(unsigned int i=0;i<jatekos.size();i++)
        {
            int cposition=jatekos[i]->getpozicio();
            cposition=(cposition+dobasok[cdobas])%mezokszama;
            jatekos[i]->setpozicio(cposition);
            mezo[cposition]->eljar(jatekos[i]);
            cdobas++;

        }
        felszamoljatekosokat();
    }
}

void Monopoly::jatekdobasoknelkul(int kor)
{
    int mezokszama=mezo.size();
    for(int i=0;i<kor;i++)
    {
        for(unsigned int j=0;j<jatekos.size();j++)
        {
            int cposition=jatekos[j]->getpozicio();
            int dobas=rand()%6+1;
            cposition=(cposition+dobas)%mezokszama;
            jatekos[j]->setpozicio(cposition);
            mezo[cposition]->eljar(jatekos[j]);
        }
        felszamoljatekosokat();
    }
}
Jatekos* Monopoly::jatekosadatai(int jat) const
{
    return jatekos[jat];
}
Mezo* Monopoly::mezoadatai(int mez) const
{
    return mezo[mez];
}
void Jatekos::ingatlankiiras() const
{
    for(unsigned int i=0;i<vasarolt.size();i++)
        cout<<" "<<vasarolt[i]->getszam();
    cout<<"\n";

}
void Monopoly::megoldas() const
{
    for(unsigned int i=0;i<jatekos.size();i++)
    {
        cout<<jatekos[i]->getnev()<<" ingatlanjai:";
        jatekos[i]->ingatlankiiras();
    }
}
