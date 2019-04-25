#ifndef JATEKOS_H_INCLUDED
#define JATEKOS_H_INCLUDED
#include<string>
#include<vector>
#include<cstdlib>
class Ingatlan;
class Jatekos{
protected:
    std::string nev;
    int vagyon;
    std::vector<Ingatlan*> vasarolt;
    bool jatekbanvan;
    int pozicio;
public:
    Jatekos(const std::string& _nev):nev(_nev){vagyon=10000;jatekbanvan=true;pozicio=0;}
    std::string getnev() const{return nev;}
    virtual void kovlepes(){}
    virtual int toke() const {return vagyon;}
    virtual bool vasarolhat() const{return true;}
    void vasarol(Ingatlan* a){vasarolt.push_back(a);}
    void ujvagyon(int penz){vagyon+=penz;}
    void csodeljaras();
    void ingatlankiiras() const;
    bool jatszik() const {return jatekbanvan;}
    bool csodotmond() const {return vagyon<0;}
    int getpozicio() const{return pozicio;}
    int getvagyon() const {return vagyon;}
    void setpozicio(const int ujpozicio){pozicio=ujpozicio;}
    int ingatlanszam() const{return vasarolt.size();}//teszteles

};
class Moho:public Jatekos
{
public:
    Moho(std::string& _nev):Jatekos(_nev){}
};
class Ovatos:public Jatekos
{
public:
    Ovatos(const std::string& _nev):Jatekos(_nev){}
    int toke() const override{return vagyon/2;}

};
class Taktikus:public Jatekos
{
private:
int vasar;
public:
    Taktikus(const std::string& _nev):Jatekos(_nev){vasar=0;}
    void kovlepes(){vasar++;}
    bool vasarolhat() const override{return vasar%2==1;}

};
struct A
{
    bool operator()(Jatekos* jat){return jat->csodotmond();}
};


#endif // JATEKOS_H_INCLUDED
