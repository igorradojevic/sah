#include "figura.h"
#include <cmath>
#include <iostream>

using namespace std;

bool Pesak::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(1 == _boja && _x == x-1 && _y == y && tabla[x][y] == NULL)
    return true;
  if(1 == _boja &&  !_pomeraoSe && _x == x-2 && _y == y && tabla[x][y] == NULL && tabla[x-1][y] == NULL)
      return true;
  if(1 == _boja && _x == x-1 && abs(_y-y) == 1 && tabla[x][y]!=NULL && tabla[x][y]->getBoja() == 0)
    return true;
  if(0 == _boja && _x == x+1 && _y == y && tabla[x][y] == NULL)
    return true;
  if(0 == _boja &&  !_pomeraoSe && _x == x+2 && _y == y && tabla[x][y] == NULL && tabla[x+1][y] == NULL)
      return true;
  else if(0 == _boja && _x == x+1 && abs(_y-y) == 1 && tabla[x][y]!=NULL && tabla[x][y]->getBoja() == 1)
    return true;

  return false;
}

bool Lovac::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(_x == x && _y == y)
    return false;
  if(abs(_x-x) != abs(_y-y))
    return false;

  int korakX;
  int korakY;
  if(_x > x)
    korakX = -1;
  else
    korakX = 1;

  if(_y > y)
    korakY = -1;
  else
    korakY = 1;

  for(int i=_x+korakX, j=_y+korakY; i != x; i+=korakX, j+=korakY)
    if(tabla[i][j] != NULL)
      return false;

  if(tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja())
    return true;

  return false;
}

bool Top::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(_x == x && _y == y)
    return false;
  if(_x != x && _y != y)
    return false;

  int korakX = 0;
  int korakY = 0;

  if(_x > x)
    korakX = -1;
  else if(_x < x)
    korakX = 1;

  if(_y > y)
    korakY = -1;
  else if(_y < y)
    korakY = 1;

  for(int i=_x+korakX, j=_y+korakY; i != x || j != y; i+=korakX, j+=korakY)
    if(tabla[i][j] != NULL)
      return false;

  if(tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja())
    return true;

  return false;
}

bool Konj::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(abs(_x-x) == 2 && abs(_y-y) == 1 && (tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja()))
    return true;
  if(abs(_x-x) == 1 && abs(_y-y) == 2 && (tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja()))
    return true;

  return false;
}

bool Kralj::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(_x == x+1 && abs(_y-y) <= 1 && (tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja()))
    return true;
  else if(_x == x-1 && abs(_y-y) <= 1 && (tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja()))
    return true;
  else if(_x == x && abs(_y-y) == 1 && (tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja()))
    return true;

  return false;
}

bool Kraljica::regularanPotez(int x, int y, Figura *const tabla[][8]) const
{
  if(_x == x && _y == y)
    return false;
  if(!(_x == x || _y == y) && !(abs(_x-x) == abs(_y-y)))
    return false;

  int korakX = 0;
  int korakY = 0;

  if(_x > x)
    korakX = -1;
  else if(_x < x)
    korakX = 1;

  if(_y > y)
    korakY = -1;
  else if(_y < y)
    korakY = 1;

  for(int i=_x+korakX, j=_y+korakY; i != x || j != y; i+=korakX, j+=korakY)
    if(tabla[i][j] != NULL)
      return false;

  if(tabla[x][y] == NULL || tabla[x][y]->getBoja() != tabla[_x][_y]->getBoja())
    return true;

  return false;
}

int Figura::getBoja() const
{
  return _boja;
}

void Figura::setPozicija(int x, int y)
{
  _x = x;
  _y = y;
}

bool Figura::jesteSePomerao() const
{
  return _pomeraoSe;
}

void Figura::setPomerioSe()
{
  _pomeraoSe = true;
}

//grafika deo

void Figura::grafikaPomeriFiguru(int gx, int gy)
{
    int POMERAJ = 50;

    _grafikaX = _grafikaX + (_y-gy)*POMERAJ;
    _grafikaY = _grafikaY + (_x-gx)*POMERAJ;
    setPos(_grafikaX, _grafikaY);
}

int Figura::grafikaGetX() const
{
    return _grafikaX;
}

int Figura::grafikaGetY() const
{
    return _grafikaY;
}

void Figura::grafikaSetX(int gx)
{
   _grafikaX = gx;
}

void Figura::grafikaSetY(int gy)
{
   _grafikaY = gy;
}


void Pesak::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/pawn.png"));
    else
        setPixmap(QPixmap(":/slike/pawn1.png"));
}

void Lovac::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/bishop.png"));
    else
        setPixmap(QPixmap(":/slike/bishop1.png"));
}

void Top::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/rook.png"));
    else
        setPixmap(QPixmap(":/slike/rook1.png"));
}

void Konj::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/horse.png"));
    else
        setPixmap(QPixmap(":/slike/horse1.png"));
}

void Kralj::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/king.png"));
    else
        setPixmap(QPixmap(":/slike/king1.png"));
}

void Kraljica::grafikaPostaviSliku()
{
    if(_boja== 1)
        setPixmap(QPixmap(":/slike/queen.png"));
    else
        setPixmap(QPixmap(":/slike/queen1.png"));
}
