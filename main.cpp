#include <igra.h>
#include <QApplication>

Igra *igra;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    igra = new Igra();
    igra->show();
    igra->grafikaDaLiKorisnikZeliDaIgraSah();

    a.exec();
    delete igra;

    return 0;
}

