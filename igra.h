#ifndef IGRA_H
#define IGRA_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "tabla.h"
#include "figura.h"
#include "polje.h"
#include <vector>

class Igra:public QGraphicsView
{
    Q_OBJECT
public:

    Igra(QWidget *parent=0);
    void odigrajPotez(int x1, int y1, int x2, int y2, bool &rokada);
    bool jesteIspravanPotez(int x1, int y1, int x2, int y2, bool &rokada);
    bool ispravnaPozicija(int x, int y) const;
    bool jesteSah(int igrac) const;
    void vratiPozicijuKralja(int igrac, int &x, int &y) const;
    bool igracImaRegularanPotez(int igrac);
    bool jesteRokada(int x1, int y1, int x2, int y2);
    bool pijunJeDosaoDoKraja(int x, int y) const;
    void pomeriFiguru(int x1, int y1, int x2, int y2);
    void vratiFiguru(int x1, int y1, int x2, int y2, Figura *pom);
    void setUnetoPolje(Polje *a);

    //graficki deo
    void grafikaDaLiKorisnikZeliDaIgraSah();
    void grafikaNacrtajPolja(int x, int y);
    void grafikaNacrtajBele(int x, int y);
    void grafikaNacrtajCrne(int x, int y);
    void grafikaKrajIgre(int pobednik);
    void grafikaMrtveBele();
    void grafikaMrtveCrne();
    void grafikaIspisPoteza();
    void grafikaNacrtajKraljicu(int x, int y, int boja);
    void grafikaUkloniFiguru(int x, int y);
    void grafikaDodajNaScenu(QGraphicsItem *item);

public slots:
    void unetaPozicija();
    void pocniIgru();
    void pocniOpetIgru();

private:
    int _naPotezu;
    Figura *_tabla[8][8];
    Polje *_polje1;
    Polje *_unetoPolje;

    //graficki deo
    QGraphicsScene *scena;
    int _brojPojedenihBelihFigura;
    int _brojPojedenihCrnihFigura;
};

#endif // IGRA_H
