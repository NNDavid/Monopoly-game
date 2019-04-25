#ifndef MEZO_H_INCLUDED
#define MEZO_H_INCLUDED
#include<string>
class Jatekos;
class Mezo
{
   public:
       virtual void eljar (Jatekos* jat)=0;
       virtual std::string getClass() const=0;
};
class Ingatlan:public Mezo
{
private:
    int szam;
    const int alapar=1000;
    const int hazar=4000;
    const int fizetalapar=500;
    const int fizetahazar=2000;
    Jatekos* tulajdonos;
    bool vantulajdonosa;
    bool vanrajtahaz;

public:
    Ingatlan(int _szam):szam(_szam){tulajdonos=nullptr;vantulajdonosa=false;vanrajtahaz=false;}
    void eljar(Jatekos* jat) override;
    void felszamol();
    std::string getClass() const override {return "Ingatlan";}
    int getszam() const {return szam;}

};
class Szolgaltatas:public Mezo
{
private:
    int szolgaltatasar;
public:
    Szolgaltatas(int _szolgaltatasar):szolgaltatasar(_szolgaltatasar){}
    void eljar(Jatekos* jat) override;
    std::string getClass() const override {return "Szolgaltatas";}
};

class Szerencse:public Mezo
{
private:
    int szerencsear;
public:
    Szerencse(int _szerencsear):szerencsear(_szerencsear){}
    void eljar(Jatekos* jat) override;
    std::string getClass() const override {return "Szerencse";}

};


#endif // MEZO_H_INCLUDED
