//#include "tabla.h"
//#include "figura.h"
//#include "polje.h"
//#include "igra.h"
//#include <QGraphicsTextItem>

//extern Igra *igra;
//Tabla::Tabla()
//{

//}

//void Tabla::nacrtajPolja(int x, int y)
//{
//    int POMERAJ=50;
//    int i, j;

//    for(i=0; i<8; i++)
//        for(j=0; j<8; j++)
//        {
//            Polje *polje = new Polje();
//            //OVDE DODATI POMOCU CONNECT KAD SE KLIKNE NA POLJE DA SE POZOVE FUNKCIJA uneta_pozicija iz KLACE Igra
//            //igra->collection[i][j]=polje;
//            polje->setX(i);
//            polje->setY(j);
//            polje->setPos(x+ j*POMERAJ, y+ i*POMERAJ);
//            if((i+j)%2 == 0)
//                polje->postaviBoju(Qt::lightGray);
//            else
//                polje->postaviBoju(Qt::darkGray);
//            connect(polje, SIGNAL(clicked()),this,SLOT(uneta_pozicija(polje)));
//            igra->dodajNaScenu(polje);
//        }

//}

