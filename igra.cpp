#include "igra.h"
#include "figura.h"
#include "dugme.h"
#include <QGraphicsPixmapItem>

extern Igra *igra;

Igra::Igra(QWidget *parent):QGraphicsView(parent)
{
    //pravljenje scene
    scena=new QGraphicsScene();
    scena->setSceneRect(0,0,800,600);

    _brojPojedenihBelihFigura = 0;
    _brojPojedenihCrnihFigura = 0;
    _polje1 = NULL;
   _naPotezu = 0;

   for(int i=0; i<8; i++)
     for(int j=0; j<8; j++)
      _tabla[i][j] = NULL;

    //pravljenje pogleda
    setFixedSize(800,600);
    setScene(scena);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Igra::pocniIgru()
{
  scena->clear();
  igra->grafikaNacrtajCrne(200, igra->height()/2-200);
  igra->grafikaNacrtajBele(200, igra->height()/2-200);
  igra->grafikaNacrtajPolja(200, height()/2-200);
  igra->grafikaMrtveBele();
  igra->grafikaMrtveCrne();
}

void Igra::unetaPozicija()
{
    int x = _unetoPolje->getX();
    int y = _unetoPolje->getY();
    bool rokada = false;

    if (_polje1 == NULL)
    {
        if(NULL != _tabla[x][y] && _tabla[x][y]->getBoja() == _naPotezu) //ako je kliknuto na polje na kom jeste njegova figura
        {
            _polje1 = _unetoPolje;
            _polje1->grafikaZasijajPolje();
        }

    }
    else if(true == jesteIspravanPotez(_polje1->getX() , _polje1->getY(), x, y, rokada))
    {
            odigrajPotez(_polje1->getX() , _polje1->getY(), x, y, rokada);

            if(pijunJeDosaoDoKraja(x, y))
            {
                grafikaUkloniFiguru(x,y);
                grafikaNacrtajKraljicu(x, y, _naPotezu); //ova fju postavlja pravi kraljicu i postavlja moju tablu
             }
            _naPotezu = _naPotezu == 1 ? 0:1;

            bool imaRegularanPotez = igracImaRegularanPotez(_naPotezu);
            if(jesteSah(_naPotezu) && !imaRegularanPotez) // ako je sah mat
            {
                _naPotezu == 0 ? grafikaKrajIgre(1) : grafikaKrajIgre(0);
            }
            else if(!jesteSah(_naPotezu) && !imaRegularanPotez)
            {
                    grafikaKrajIgre(2);
            }

            _polje1->grafikaOdsijajPolje();
            _polje1 = NULL;
    }
    else if(NULL != _tabla[x][y] && _tabla[x][y]->getBoja() == _naPotezu) //ako je kliknuo na figuru koja je njegova
    {
            _polje1->grafikaOdsijajPolje();
            _polje1 = _unetoPolje;
            _polje1->grafikaPostaviBoju(Qt::red);
    }
    else
    {
            _polje1->grafikaOdsijajPolje();
            _polje1 = NULL;
    }
}

void Igra::odigrajPotez(int x1, int y1, int x2, int y2, bool &rokada)
{
  if(rokada == true)
  {
    int novoYKralju = y2>y1 ? y1+2 : y1-2;
    int novoYTopu = y2>y1 ? novoYKralju-1 : novoYKralju+1;

    _tabla[x1][y1]->setPomerioSe();
    _tabla[x2][y2]->setPomerioSe();

    pomeriFiguru(x1, y1, x1, novoYKralju);
    pomeriFiguru(x2, y2, x1, novoYTopu);
  }
  else
  {
    _tabla[x1][y1]->setPomerioSe();

    if(_tabla[x2][y2] != NULL) //ako se jede figura
    {
       grafikaUkloniFiguru(x2,y2);
    }
    pomeriFiguru(x1, y1, x2, y2);
  }
}

bool Igra::jesteIspravanPotez(int x1, int y1, int x2, int y2, bool &rokada)
{
  if(false == ispravnaPozicija(x1, y1))
  {
    return false;
  }
  if(false == ispravnaPozicija(x2, y2))
  {
    return false;
  }
  if(NULL == _tabla[x1][y1] || _tabla[x1][y1]->getBoja() != _naPotezu)
  {
    return false;
  }
  if(true == jesteRokada(x1, y1, x2, y2))
  {
    rokada = true;
    return true;
  }
  if(false == _tabla[x1][y1]->regularanPotez(x2, y2, _tabla))
  {
    return false;
  }

  Figura *pom = _tabla[x2][y2];
  pomeriFiguru(x1, y1, x2, y2);

  if(jesteSah(_naPotezu))
  {
    vratiFiguru(x2, y2, x1, y1, pom);
    return false;
  }

  vratiFiguru(x2, y2, x1, y1, pom);

  return true;
}

bool Igra::ispravnaPozicija(int x, int y) const
{
  if(x >= 0 && x <= 7 && y >= 0 && y <= 7)
    return true;
  else
    return false;
}

bool Igra::jesteSah(int igrac) const
{
  int x, y;
  vratiPozicijuKralja(igrac, x, y);

  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      //ako je na (i,j) protivnicka figura i napada kralja onda jeste sah
      if(_tabla[i][j] != NULL && _tabla[i][j]->getBoja() != igrac && _tabla[i][j]->regularanPotez(x, y, _tabla))
        return true;
    }
  }
  return false;
}

void Igra::vratiPozicijuKralja(int igrac, int &x, int &y) const
{
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      //Ukoliko je figura (i, j) od tog igraca postavi poziciju i izadji
      Kralj *kr = dynamic_cast<Kralj *>(_tabla[i][j]);
      if(kr != NULL && kr->getBoja() == igrac)
      {
        x = i;
        y = j;
        return;
      }
    }
  }
}

bool Igra::igracImaRegularanPotez(int igrac)
{
  bool nebitno;
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<8; j++)
    {
      if(_tabla[i][j] != NULL && _tabla[i][j]->getBoja() == igrac)
      {
        for(int x=0; x<8; x++)
        {
          for(int y=0; y<8; y++)
          {
            if(jesteIspravanPotez(i, j, x, y, nebitno))
            {
              return true;
            }
          }
        }
      }
    }
  }

  return false;
}

bool Igra::jesteRokada(int x1, int y1, int x2, int y2)
{
  if(_tabla[x1][y1] == NULL || _tabla[x2][y2] == NULL || _tabla[x1][y1]->getBoja() != _naPotezu || _tabla[x2][y2]->getBoja() != _naPotezu)
  {
    return false;
  }
  if(dynamic_cast<Kralj *>(_tabla[x1][y1]) == NULL || dynamic_cast<Top *>(_tabla[x2][y2]) == NULL)
  {
    return false;
  }
  if(_tabla[x1][y1]->jesteSePomerao() || _tabla[x2][y2]->jesteSePomerao())
  {
    return false;
  }

  int manja = y1 < y2? y1:y2;
  int veca = y1 > y2? y1:y2;

  for(int i=manja+1, j=veca; i<j; i++)
  {
    if(_tabla[x1][i] != NULL)
    {
      return false;
    }
  }

  for(int k = manja; k <= veca; k++)
  {
    for(int i=0; i<8; i++)
      for(int j=0; j<8; j++)
        if(_tabla[i][j] != NULL && _tabla[i][j]->getBoja() != _naPotezu && _tabla[i][j]->regularanPotez(x1, k, _tabla))
        {
            return false;
        }
  }

  return true;
}

void Igra::pocniOpetIgru()
{
    scena->clear();
    delete igra;

    igra = new Igra();
    show();
    pocniIgru();
}

bool Igra::pijunJeDosaoDoKraja(int x, int y) const
{
    if(dynamic_cast<Pesak*>(_tabla[x][y]) != NULL && _tabla[x][y]->getBoja() == 0 && x == 0)
            return true;
    else if(dynamic_cast<Pesak*>(_tabla[x][y]) != NULL && _tabla[x][y]->getBoja() == 1 && x == 7)
        return true;

    return false;
}

void Igra::pomeriFiguru(int x1, int y1, int x2, int y2)
{
    _tabla[x2][y2] = _tabla[x1][y1];
    _tabla[x1][y1] = NULL;
    _tabla[x2][y2]->setPozicija(x2, y2);
    _tabla[x2][y2]->grafikaPomeriFiguru(x1, y1);
}

void Igra::vratiFiguru(int x1, int y1, int x2, int y2, Figura *pom)
{
    pomeriFiguru(x1, y1, x2, y2);
    _tabla[x1][y1] = pom;
}

void Igra::grafikaDaLiKorisnikZeliDaIgraSah()
{
    QGraphicsPixmapItem *pozadina=new QGraphicsPixmapItem();
    pozadina->setPixmap(QPixmap(":/slike/pozadina.png"));
    pozadina->setZValue(-1);
    pozadina->setScale(1.67);
    pozadina->scale();
    grafikaDodajNaScenu(pozadina);

    Dugme * igrajDugme = new Dugme("ZAPOCNI IGRU");
    int ixPoz = width()/2 - igrajDugme->boundingRect().width()/2;
    int iyPoz = 50;
    igrajDugme->setPos(ixPoz,iyPoz);
    connect(igrajDugme,SIGNAL(clicked()) , this , SLOT(pocniIgru()));
    grafikaDodajNaScenu(igrajDugme);

    //Create Quit Button
    Dugme * izadjiDugme = new Dugme("IZADJI");
    int izxPoz = width()/2 - izadjiDugme->boundingRect().width()/2;
    int izyPoz = 150;
    izadjiDugme->setPos(izxPoz,izyPoz);
    connect(izadjiDugme, SIGNAL(clicked()),this,SLOT(close()));
    grafikaDodajNaScenu(izadjiDugme);
}

void Igra::grafikaNacrtajPolja(int x, int y)
{
    int POMERAJ=50;
    int i, j;

    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            Polje *polje = new Polje();
            //OVDE DODATI POMOCU CONNECT KAD SE KLIKNE NA POLJE DA SE POZOVE FUNKCIJA unetaPozicija iz KLACE Igra
            //igra->collection[i][j]=polje;
            polje->setX(i);
            polje->setY(j);
            polje->setPos(x+ j*POMERAJ, y+ i*POMERAJ);
            if((i+j)%2 == 0)
                polje->grafikaPostaviBoju(Qt::lightGray);
            else
                polje->grafikaPostaviBoju(Qt::darkGray);
            connect(polje, SIGNAL(clicked()), this , SLOT(unetaPozicija()));
            igra->grafikaDodajNaScenu(polje);
        }

}

void Igra::grafikaMrtveBele()
{
    QGraphicsRectItem *bele=new QGraphicsRectItem();
    bele->setRect(0,0,200,600);
    bele->setBrush(QColor(121,85,72));
    bele->setZValue(-1);
    grafikaDodajNaScenu(bele);

    QGraphicsTextItem *grafikaMrtveBele = new QGraphicsTextItem("POJEDENE BELE");
    QFont font("arial" , 15);
    grafikaMrtveBele->setFont(font);
    grafikaMrtveBele->setPos(10,0);
    grafikaMrtveBele->setDefaultTextColor(Qt::white);
    grafikaDodajNaScenu(grafikaMrtveBele);

}
void Igra::grafikaMrtveCrne()
{
    QGraphicsRectItem *crne=new QGraphicsRectItem();
    crne->setRect(600,0,200,600);
    crne->setBrush(QColor(121,85,72));
    crne->setZValue(-1);
    grafikaDodajNaScenu(crne);

    QGraphicsTextItem *grafikaMrtveCrne = new QGraphicsTextItem("POJEDENE CRNE");
    QFont font("arial" , 15);
    grafikaMrtveCrne->setFont(font);
    grafikaMrtveCrne->setPos(610,0);
    grafikaMrtveCrne->setDefaultTextColor(Qt::black);
    grafikaDodajNaScenu(grafikaMrtveCrne);
}

void Igra::grafikaKrajIgre(int pobednik)
{
    QGraphicsTextItem *ispis = new QGraphicsTextItem();
    QFont font("arial" , 65);
    ispis->setFont(font);
    ispis->setDefaultTextColor(Qt::red);
    ispis->setPos(50, height()/2-75);
    if(pobednik==0)
    {
        ispis->setPlainText("BELI JE POBEDIO");
    }
    if(pobednik==1)
    {
        ispis->setPlainText("CRNI JE POBEDIO");
    }
    if(pobednik==2)
    {
        ispis->setPlainText("NERESENO JE");
    }
    grafikaDodajNaScenu(ispis);

    Dugme * igrajPonovo = new Dugme("IGRAJ PONOVO");

    int ixPoz = width()/2 - igrajPonovo->boundingRect().width()/2;
    int iyPoz = 0;
    igrajPonovo->setPos(ixPoz,iyPoz);
    connect(igrajPonovo,SIGNAL(clicked()) , this , SLOT(pocniOpetIgru()));
    grafikaDodajNaScenu(igrajPonovo);

    Dugme * izadjiDugme = new Dugme("IZADJI");
    izadjiDugme->setPos(width()/2-izadjiDugme->boundingRect().width()/2, height()/2+200);
    connect(izadjiDugme, SIGNAL(clicked()),this,SLOT(close()));
    grafikaDodajNaScenu(izadjiDugme);
}

void Igra::grafikaUkloniFiguru(int x, int y)
{
    int POMERAJ=50;

    if(_tabla[x][y]->getBoja() == 0)
    {
        _tabla[x][y]->setPos(0+(_brojPojedenihBelihFigura%3)*POMERAJ, 50+(_brojPojedenihBelihFigura/3)*POMERAJ);
        _brojPojedenihBelihFigura++;
    }
    else
    {
        _tabla[x][y]->setPos(600+(_brojPojedenihCrnihFigura%3)*POMERAJ, 50+(_brojPojedenihCrnihFigura/3)*POMERAJ);
        _brojPojedenihCrnihFigura++;
    }
}

void Igra::grafikaNacrtajCrne(int x, int y)
{
    int POMERAJ=50;
    int i;

    //crni pesaci
    for (i=0; i<8; i++)
    {
        Pesak *pesak=new Pesak(1,i,1);
        pesak->setPozicija(1,i);
        pesak->setPos(x+i*POMERAJ-7, y+ 1*POMERAJ-7);
        _tabla[1][i]=pesak;
        _tabla[1][i]->grafikaSetX(x+i*POMERAJ-7);
        _tabla[1][i]->grafikaSetY(y+1*POMERAJ-7);
        pesak->grafikaPostaviSliku();
        igra->grafikaDodajNaScenu(pesak);
    }

    //crne ostale
    Top *top=new Top(0, 0, 1);
    top->setPozicija(0,0);
    top->setPos(x-7,y-7);
    _tabla[0][0]=top;
    _tabla[0][0]->grafikaSetX(x-7);
    _tabla[0][0]->grafikaSetY(y-7);
    top->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(top);

    Top *top1=new Top(0, 7, 1);
    top1->setPozicija(0,7);
    top1->setPos(x+7*POMERAJ-7,y-7);
    _tabla[0][7]=top1;
    _tabla[0][7]->grafikaSetX(x+7*POMERAJ-7);
    _tabla[0][7]->grafikaSetY(y-7);
    top1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(top1);

    Konj *konj=new Konj(0, 1, 1);
    konj->setPozicija(0,1);
    konj->setPos(x+1*POMERAJ-7,y-7);
    _tabla[0][1]=konj;
    _tabla[0][1]->grafikaSetX(x+1*POMERAJ-7);
    _tabla[0][1]->grafikaSetY(y-7);
    konj->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(konj);

    Konj *konj1=new Konj(0, 6, 1);
    konj1->setPozicija(0,6);
    konj1->setPos(x+6*POMERAJ-7,y-7);
    _tabla[0][6]=konj1;
    _tabla[0][6]->grafikaSetX(x+6*POMERAJ-7);
    _tabla[0][6]->grafikaSetY(y-7);
    konj1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(konj1);

    Lovac *lovac=new Lovac(0, 5, 1);
    lovac->setPozicija(0,5);
    lovac->setPos(x+5*POMERAJ-7,y-7);
    _tabla[0][5]=lovac;
    _tabla[0][5]->grafikaSetX(x+5*POMERAJ-7);
    _tabla[0][5]->grafikaSetY(y-7);
    lovac->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(lovac);

    Lovac *lovac1=new Lovac(0, 2, 1);

    lovac1->setPozicija(0,2);
    lovac1->setPos(x+2*POMERAJ-7,y-7);
    _tabla[0][2]=lovac1;
    _tabla[0][2]->grafikaSetX(x+2*POMERAJ-7);
    _tabla[0][2]->grafikaSetY(y-7);
    lovac1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(lovac1);

    Kraljica *kraljica=new Kraljica(0, 3, 1);
    kraljica->setPozicija(0,3);
    kraljica->setPos(x+3*POMERAJ-5,y-6);
    _tabla[0][3]=kraljica;
    _tabla[0][3]->grafikaSetX(x+3*POMERAJ-5);
    _tabla[0][3]->grafikaSetY(y-6);
    kraljica->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(kraljica);

    Kralj *kralj=new Kralj(0, 4, 1);
    kralj->setPozicija(0,4);
    kralj->setPos(x+4*POMERAJ-5,y-6);
    _tabla[0][4]=kralj;
    _tabla[0][4]->grafikaSetX(x+4*POMERAJ-5);
    _tabla[0][4]->grafikaSetY(y-6);
    kralj->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(kralj);
}

void Igra::grafikaNacrtajBele(int x, int y)
{
    int POMERAJ=50;
    int i;

    //beli pesaci
    for (i=0; i<8; i++)
    {
        Pesak *pesak=new Pesak(6,i,0);
        pesak->setPozicija(6,i);
        pesak->setPos(x+i*POMERAJ-7, y+ 6*POMERAJ-7);
        _tabla[6][i]=pesak;
        _tabla[6][i]->grafikaSetX(x+i*POMERAJ-7);
        _tabla[6][i]->grafikaSetY(y+ 6*POMERAJ-7);
        pesak->grafikaPostaviSliku();
        igra->grafikaDodajNaScenu(pesak);
    }
    //bele ostale
    Top *top=new Top(7, 0, 0);
    top->setPozicija(7,0);
    top->setPos(x+0*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][0]=top;
    _tabla[7][0]->grafikaSetX(x+0*POMERAJ-7);
    _tabla[7][0]->grafikaSetY(y+7*POMERAJ-7);
    top->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(top);

    Top *top1=new Top(7, 7, 0);
    top1->setPozicija(7,7);
    top1->setPos(x+7*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][7]=top1;
    _tabla[7][7]->grafikaSetX(x+7*POMERAJ-7);
    _tabla[7][7]->grafikaSetY(y+7*POMERAJ-7);
    top1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(top1);

    Konj *konj=new Konj(7, 1, 0);
    konj->setPozicija(7,1);
    konj->setPos(x+1*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][1]=konj;
    _tabla[7][1]->grafikaSetX(x+1*POMERAJ-7);
    _tabla[7][1]->grafikaSetY(y+7*POMERAJ-7);
    konj->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(konj);

    Konj *konj1=new Konj(7, 6, 0);
    konj1->setPozicija(7,6);
    konj1->setPos(x+6*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][6]=konj1;
    _tabla[7][6]->grafikaSetX(x+6*POMERAJ-7);
    _tabla[7][6]->grafikaSetY(y+7*POMERAJ-7);
    konj1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(konj1);

    Lovac *lovac=new Lovac(7, 5, 0);
    lovac->setPozicija(7,5);
    lovac->setPos(x+5*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][5]=lovac;
    _tabla[7][5]->grafikaSetX(x+5*POMERAJ-7);
    _tabla[7][5]->grafikaSetY(y+7*POMERAJ-7);
    lovac->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(lovac);

    Lovac *lovac1=new Lovac(7, 2, 0);
    lovac1->setPozicija(7,2);
    lovac1->setPos(x+2*POMERAJ-7,y+7*POMERAJ-7);
    _tabla[7][2]=lovac1;
    _tabla[7][2]->grafikaSetX(x+2*POMERAJ-7);
    _tabla[7][2]->grafikaSetY(y+7*POMERAJ-7);
    lovac1->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(lovac1);

    Kraljica *kraljica=new Kraljica(7, 3, 0);
    kraljica->setPozicija(7,3);
    kraljica->setPos(x+3*POMERAJ-5,y+7*POMERAJ-6);
    _tabla[7][3]=kraljica;
    _tabla[7][3]->grafikaSetX(x+3*POMERAJ-5);
    _tabla[7][3]->grafikaSetY(y+7*POMERAJ-6);
    kraljica->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(kraljica);

    Kralj *kralj=new Kralj(7, 4, 0);
    kralj->setPozicija(7,4);
    kralj->setPos(x+4*POMERAJ-5,y+7*POMERAJ-6);
    _tabla[7][4]=kralj;
    _tabla[7][4]->grafikaSetX(x+4*POMERAJ-5);
    _tabla[7][4]->grafikaSetY(y+7*POMERAJ-6);
    kralj->grafikaPostaviSliku();
    igra->grafikaDodajNaScenu(kralj);
}

void Igra::grafikaNacrtajKraljicu(int x, int y, int boja)
{
    int gx = 200;
    int gy = igra->height()/2-200;
    int POMERAJ=50;

    Kraljica *kraljica = new Kraljica(x, y, boja);
    kraljica->setPozicija(x,y);
    kraljica->setPos(gx+y*POMERAJ-5,gy+x*POMERAJ-6);
    kraljica->grafikaSetX(gx+y*POMERAJ-5);
    kraljica->grafikaSetY(gy+x*POMERAJ-6);
    kraljica->grafikaPostaviSliku();
    _tabla[x][y] = kraljica;
    grafikaDodajNaScenu(kraljica);
}

void Igra::grafikaDodajNaScenu(QGraphicsItem *item)
{
    scena->addItem(item);
}

void Igra::setUnetoPolje(Polje *a)
{
    _unetoPolje = a;
}
