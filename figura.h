#ifndef FIGURA_H
#define FIGURA_H

#include <QGraphicsPixmapItem>

class Figura:public QGraphicsPixmapItem
{
public:
  Figura(int x, int y, int boja, bool pomerio = false)
      : _x(x), _y(y), _boja(boja), _pomeraoSe(pomerio)
  {}

  virtual bool regularanPotez(int x, int y, Figura *const tabla[][8]) const = 0;
  virtual ~Figura()
  {}
  int getBoja() const;
  bool jesteSePomerao() const;
  void setPozicija(int x, int y);
  void setPomerioSe();

  //graficki deo
  int grafikaGetX() const;
  int grafikaGetY() const;
  void grafikaSetX(int gx);
  void grafikaSetY(int gy);
  void grafikaPomeriFiguru(int x, int y);
  virtual void grafikaPostaviSliku() = 0;

protected:

  int _x;
  int _y;
  int _boja;
  bool _pomeraoSe;

  //graficki deo
  int _grafikaX;
  int _grafikaY;
};

class Pesak : public Figura
{
public:
  Pesak(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};

class Lovac : public Figura
{
public:
  Lovac(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};

class Top : public Figura
{
public:
  Top(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};

class Konj : public Figura
{
public:
  Konj(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};

class Kralj : public Figura
{
public:
  Kralj(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};

class Kraljica : public Figura
{
public:
  Kraljica(int x, int y, int boja)
    : Figura(x, y, boja)
  {}

  bool regularanPotez(int x, int y, Figura *const tabla[][8]) const;

  //grafika
  void grafikaPostaviSliku();

private:
};
#endif // FIGURA_H
