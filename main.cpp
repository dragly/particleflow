// all
#include <QtGui>
#include <QDebug>
// Symbian
#ifdef Q_WS_S60
#include <eikenv.h>
#include <eikappui.h>
#include <aknenv.h>
#include <aknappui.h>
#endif
// not Symbian
//#if defined(Q_WS_MAEMO_5) || defined(Q_OS_LINUX)
#include <QGLWidget>
//#endif
// internal (all)
#include "gamescene.h"
#include "gameview.h"

int main(int argc, char *argv[])
{
//#ifdef Q_WS_S60
// QApplication::setGraphicsSystem("openvg");
//#endif
    qDebug() << "Starting app";
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    qDebug() << "Enabling settings";
    QCoreApplication::setOrganizationName("Dragly");
    QCoreApplication::setOrganizationDomain("dragly.org");
    QCoreApplication::setApplicationName("Nanoparticles");

// Symbian specific code
#ifdef Q_OS_SYMBIAN
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*> (CEikonEnv::Static()->AppUi());
    TRAPD(error,
          if (appUi) {
        // Lock application orientation into landscape
        appUi->SetOrientationL(CAknAppUi::EAppUiOrientationLandscape);
    }
    );
#endif
    qDebug() << "landscape loaded";

    qDebug() << "Starting view";
    GameView view;

#if QT_VERSION > 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    view.setAttribute(Qt::WA_LockLandscapeOrientation, true);
#endif // QT_VERSION < 0x040702
    qDebug() << "landscape loaded second run";

    // Font loading
    qDebug() << "Starting database";
    QFontDatabase database;
    if(!database.addApplicationFont(":/fonts/novasquare/NovaSquare.ttf")) {
        qWarning() << "Could not load Nova font!";
    }
    qDebug() << "font loaded";

//#if defined(Q_WS_MAEMO_5) || defined(Q_OS_LINUX)

    // Use OpenGL widget
    QGLWidget *glwidget = new QGLWidget();
    view.setViewport(glwidget); // IMPORTANT: Disabling this makes animations with images sluggish. Disable only if enteriely necessary, and try to find another option to draw smooth animations first.

    //#endif
    qDebug() << "setViewport";

#if defined(Q_WS_S60)
    view.showFullScreen();
    qDebug() << "showFullScreen";
#elif defined(Q_WS_MAEMO_5)
    view.showFullScreen();
#else
    view.show();
#endif

    return a.exec();
}
