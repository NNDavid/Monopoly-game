#ifndef MONOPOLY_H_INCLUDED
#define MONOPOLY_H_INCLUDED
#include<vector>
class Jatekos;
class Mezo;
class Monopoly
{
private:
    std::vector<Jatekos*> jatekos;
    std::vector<Mezo*> mezo;
    int* dobasok;
    int dobasokszama;
public:
    Monopoly(const std::string& fname="");
    void felszamoljatekosokat();
    ~Monopoly(){delete[] dobasok;}
    void jatssz(const int kor=0);
    void jatekdobasokkal();
    void jatekdobasoknelkul(int kor);
    Jatekos* jatekosadatai(int jat) const;//teszteles
    Mezo* mezoadatai(int mez) const;//teszteles
    int jatekosokszama()const {return jatekos.size();} //teszteles
    void megoldas() const;



};


#endif // MONOPOLY_H_INCLUDED
