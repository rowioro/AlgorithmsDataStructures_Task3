#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct SFilm
{
    string tytul;
    string gatunek;
    double czas_trwania;
    SFilm* next;
};

struct SGatunek
{
    string gatunek;
    int suma;
    SGatunek* next;
};

void utworz_wstecz(SFilm*& glowa)
{
    SFilm* aktualny;
    aktualny = NULL;

    ifstream we("film.txt");
    if (!we.good())
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        exit(0);
    }
    glowa = NULL;
    while (!we.eof())
    {
        aktualny = new SFilm;
        we >> aktualny->tytul;
        we >> aktualny->gatunek;
        we >> aktualny->czas_trwania;
        aktualny->next = glowa;
        glowa = aktualny;
    }
    we.close();

}

void drukuj(SFilm* adres)
{
    while (adres)
    {
        cout << setw(20) << adres->tytul << setw(5) << " ";
        cout << setw(20) << adres->gatunek << setw(5) << " ";
        cout << setw(20) << adres->czas_trwania << setw(5) << " ";
        adres = adres->next;
        cout << endl;
    }
    cout << endl;
}

void dopisz(SFilm*& glowa, SFilm*& ogon, SFilm*& nowosc)
{
    SFilm* tmp;

    tmp = glowa;
    glowa = nowosc;
    nowosc->next = tmp;
    /*tmp=ogon->next;
    ogon->next=nowosc;
    nowosc->next=tmp;
    ogon=nowosc;*/
}

void sortuj(SFilm*& glowa)
{
    SFilm* posortowana = NULL;
    SFilm* aktualny = glowa;

    while (aktualny)
    {
        SFilm* nastepny = aktualny->next;

        if (posortowana == NULL || posortowana->gatunek >= aktualny->gatunek)
        {
            aktualny->next = posortowana;
            posortowana = aktualny;
        }
        else
        {
            SFilm* temp = posortowana;
            //szukamy elementu mniejszego od aktualnej wartosci
            while (temp->next != NULL && temp->next->gatunek < aktualny->gatunek)
                temp = temp->next;
            //wstawienie elementu do listy
            aktualny->next = temp->next;
            temp->next = aktualny;
        }

        aktualny = nastepny;
    }
    glowa = posortowana;
}

SFilm* kopiuj(SFilm* glowa)
{
    SFilm* nowa = new SFilm;
    SFilm* akt, * poprzedni;

    nowa->tytul = glowa->tytul;
    nowa->gatunek = glowa->gatunek;
    nowa->czas_trwania = glowa->czas_trwania;
    nowa->next = NULL;
    poprzedni = nowa;

    while (glowa->next)
    {
        akt = new SFilm;
        akt->tytul = glowa->next->tytul;
        akt->gatunek = glowa->next->gatunek;
        akt->czas_trwania = glowa->next->czas_trwania;
        poprzedni->next = akt;
        akt->next = NULL;
        poprzedni = akt;
        glowa = glowa->next;
    }
    return nowa;
}

int ile_gatunkow(SFilm* glowa)
{
    if (glowa)
    {
        int licznik = 1;
        while (glowa->next)
        {
            if (glowa->gatunek != glowa->next->gatunek)
                licznik++;
            glowa = glowa->next;
        }
        return licznik;
    }
    return 0;
}

void usun(SFilm*& kopia)
{
    SFilm* kosz;

    while (kopia)
    {
        kosz = kopia;
        kopia = kopia->next;
        delete kosz;
    }
}

SFilm* jedna_funkcja(SFilm*& glowa, double& sr_czas, char zn, SFilm* nowy, int jakas)
{
    SFilm* adres, * ogon, * poprzedni, * kosz, * przed, * nowosc;
    adres = ogon = poprzedni = kosz = przed = nowosc = NULL;
    double suma = 0;
    int ilosc = 0;

    adres = glowa;
    while (adres)
    {
        if (adres->gatunek[0] == zn)
        {
            ilosc++;
            suma += adres->czas_trwania;
        }
        adres = adres->next;
    }
    sr_czas = suma / ilosc;
    cout << "Sredni czas trwania filmow z podanego gatunku = " << sr_czas << endl;
    cout << endl;

    adres = glowa;
    if (glowa == NULL)
        exit(0);
    int ile_el = 1;
    while (adres->next)
    {
        ile_el++;
        adres = adres->next;
    }
    ogon = adres;
    ogon->next = NULL;

    cout << "Wszystkich filmow na liscie jest: " << ile_el << endl;
    cout << "Ostatni film trwa " << ogon->czas_trwania << " min." << endl;

    if (ile_el >= 2)
    {
        poprzedni = glowa;
        for (int i = 0; i < ile_el - 2; i++)
            poprzedni = poprzedni->next;
        cout << "Przedostatni film trwa " << poprzedni->czas_trwania << " min." << endl;
    }

    if (ogon->czas_trwania > poprzedni->czas_trwania)
    {
        kosz = poprzedni->next;
        poprzedni->next = NULL;
        delete kosz;
        ogon = poprzedni;
    }
    else
    {
        if (poprzedni == glowa)
        {
            kosz = glowa;
            glowa = glowa->next;
            delete kosz;
        }
        else
        {
            przed = glowa;
            for (int i = 0; i < ile_el - 3; i++)
                przed = przed->next;
            kosz = przed->next;
            przed->next = poprzedni->next;
            delete kosz;
        }
    }
    cout << endl;
    cout << "Lista po usunieciu dluzszego filmu sposrod dwoch ostatnich: " << endl;
    cout << endl;
    drukuj(glowa);

    /*SGatunek *lista, *g_lista, *ogon_lista;
    ifstream we("gatunki.txt");
    if (!we.good())
    {
        cout<<"Nie udalo sie otworzyc pliku!"<<endl;
        exit(0);
    }
    g_lista=NULL;
    while (!we.eof())
    {
        lista=new SGatunek;
        we>>lista->gatunek;
        we>>lista->suma;
        lista->next=g_lista;
        g_lista=lista;
    }
    we.close();

    lista=g_lista;
    if (g_lista==NULL)
        exit(0);
    int ile_gat=1;
    while (lista->next)
    {
        ile_gat++;
        lista=lista->next;
    }
    ogon_lista=lista;

    adres=glowa;
    while (adres)
    {
        lista=g_lista;
        for (int i=0; i<ile_gat; i++)
        {
            if (adres->gatunek==lista->gatunek)
                lista->suma++;
            lista=lista->next;
        }
        adres=adres->next;
    }
    int licz_gat=0;
    lista=g_lista;
    for (int i=0; i<ile_gat; i++)
    {
        if (lista->suma>0)
            licz_gat++;
        lista=lista->next;
    }*/

    SFilm* kopia = kopiuj(glowa);
    sortuj(kopia);
    cout << endl;
    cout << "Posortowana lista wg gatunkow: " << endl;
    cout << endl;
    drukuj(kopia);
    int licz_gat = ile_gatunkow(kopia);
    usun(kopia);

    cout << "Liczba gatunkow na liscie = " << licz_gat << endl;
    cout << endl;

    nowosc = new SFilm;
    nowosc->tytul = "Potop";
    nowosc->gatunek = "Historyczny";
    nowosc->czas_trwania = 120;

    if (licz_gat <= jakas)
        dopisz(glowa, ogon, nowosc);
    /*{
        //cout<<"Dopisuje film o podanych danych:"<<endl;
        //cout<<endl;
        SFilm *tmp;
        tmp=ogon->next;
        ogon->next=nowy;
        nowy->next=tmp;
        ogon=nowy;
    }*/
    else
        nowy = NULL;
    //drukuj(nowy);
    cout << "Dopisuje film o podanych danych:" << endl;
    cout << endl;
    drukuj(nowosc);

    return nowy;
}

bool druga_funkcja(SFilm*& glowa, int ile, int nr_el)
{
    SFilm* adres, * tmp, * ogon, * tmp2, * kosz, * poprzedni;
    adres = tmp = ogon = tmp2 = kosz = poprzedni = NULL;

    adres = glowa;
    if (glowa == NULL)
        exit(0);
    int ile_el = 1;
    while (adres->next)
    {
        ile_el++;
        adres = adres->next;
    }
    ogon = adres;

    //cout<<endl;
    cout << "Aktualna lista filmow: " << endl;
    cout << endl;
    drukuj(glowa);

    if (ile_el >= ile)
    {
        //adres=glowa;
        for (int i = 0; i < ile; i++)
        {
            tmp = glowa;
            glowa = glowa->next;
            tmp2 = ogon->next;
            ogon->next = tmp;
            tmp->next = tmp2;
            ogon = tmp;
            adres = adres->next;
        }
    }
    cout << endl;
    cout << "Lista po przeniesieniu podanej liczby filmow: " << endl;
    cout << endl;
    drukuj(glowa);

    double suma = 0, sr_czas = 0;
    adres = glowa;
    while (adres)
    {
        suma += adres->czas_trwania;
        adres = adres->next;
    }
    sr_czas = suma / ile_el;
    cout << "Sredni czas trwania filmow = " << sr_czas << endl;
    cout << endl;

    adres = glowa;
    poprzedni = NULL;
    while (adres)
    {
        if (adres->czas_trwania > sr_czas)
        {
            if (adres == glowa)
                glowa = glowa->next;
            else
                poprzedni->next = adres->next;
            kosz = adres;
            adres = adres->next;
            delete kosz;
        }
        else
        {
            poprzedni = adres;
            adres = adres->next;
        }
    }
    cout << endl;
    cout << "Lista po usunieciu dluzszych filmow niz srednia: " << endl;
    cout << endl;
    drukuj(glowa);

    double czas_max = 0;
    SFilm* dlugi, * zamiana, * przed, * kolejny;
    poprzedni = NULL;

    adres = glowa;
    zamiana = glowa;
    if (glowa == NULL)
        exit(0);
    ile_el = 1;
    while (adres->next)
    {
        ile_el++;
        adres = adres->next;
    }
    ogon = adres;

    adres = glowa;
    zamiana = glowa;
    czas_max = adres->czas_trwania;
    dlugi = adres;
    while (adres->next)
    {
        poprzedni = adres;
        adres = adres->next;
        if (adres->czas_trwania > czas_max)
        {
            czas_max = adres->czas_trwania;
            dlugi = adres;
        }
    }
    cout << "Najdluzszy film to " << dlugi->tytul << "." << endl;
    if (dlugi != glowa)
        cout << "Poprzedni to " << poprzedni->tytul << "." << endl;
    cout << endl;

    if (nr_el > ile_el)
        exit(0);
    else
    {
        przed = NULL;
        kolejny = glowa;
        for (int i = 0; i < nr_el - 1; i++)
        {
            przed = kolejny;
            kolejny = kolejny->next;
        }
    }
    cout << "Jakis kolejny film to " << kolejny->tytul << "." << endl;
    if (kolejny != glowa)
        cout << "Poprzedni przed jakims kolejnym to " << przed->tytul << "." << endl;
    cout << endl;

    bool info_log;

    if (kolejny == glowa && kolejny != dlugi)
    {
        tmp = kolejny;
        glowa = poprzedni->next;
        poprzedni->next = tmp;
        tmp = dlugi->next;
        dlugi->next = kolejny->next;
        kolejny->next = tmp;
        info_log = true;
    }
    else if (dlugi == glowa && kolejny != dlugi)
    {
        tmp = dlugi;
        glowa = przed->next;
        przed->next = tmp;
        tmp = kolejny->next;
        kolejny->next = dlugi->next;
        dlugi->next = tmp;
        info_log = true;
    }
    else if (kolejny == dlugi)
    {
        cout << "Lista nie ulegla zamianie, poniewaz kolejny numer pokrywa sie z najdluzszym filmem." << endl;
        info_log = false;
    }
    else
    {
        tmp = poprzedni->next;
        poprzedni->next = przed->next;
        przed->next = tmp;
        tmp2 = dlugi->next;
        dlugi->next = kolejny->next;
        kolejny->next = tmp2;
        info_log = true;
    }
    cout << endl;
    cout << "Lista po zamianie miejscami: " << endl;
    cout << endl;
    drukuj(glowa);

    return info_log;
}

void kasuj(SFilm*& glowa)
{
    SFilm* tmp;
    while (glowa)
    {
        tmp = glowa;
        glowa = glowa->next;
        delete tmp;
    }
    glowa = NULL;
}

int main()
{
    SFilm* glowa, * nowy, * nowosc;
    glowa = nowy = nowosc = NULL;

    /*nowy=new SFilm;
    nowy->tytul="Potop";
    nowy->gatunek="Historyczny";
    nowy->czas_trwania=120;*/

    double sr_czas = 0;
    char K, D, G;

    utworz_wstecz(glowa);
    cout << "Lista wczytanych filmow: " << endl;
    cout << endl;
    drukuj(glowa);

    nowy = jedna_funkcja(glowa, sr_czas, 'D', nowy, 6);
    //cout<<"Dopisuje film o podanych danych:"<<endl;
    //cout<<endl;
    //drukuj(nowosc);

    bool info_log;

    info_log = druga_funkcja(glowa, 3, 4);
    if (info_log)
        cout << "Dokonano zamiany filmow." << endl;
    else
        cout << "Nie dokonano zamiany filmow." << endl;
    kasuj(glowa);
    cout << endl;
    cout << "Ponownie drukuje skasowana glowe: " << endl;
    drukuj(glowa);

    return 0;
}
