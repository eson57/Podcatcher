#include <QtQuick>


#include <sailfishapp.h>
#include "podcatcherui.h"


#include <execinfo.h>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

[[ noreturn ]] void handler(int sig) {
  void *array[100];
  int size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 100);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

        signal(SIGSEGV, handler);   // install our handler


    QGuiApplication* app = SailfishApp::application(argc,argv);

    auto* ui = new PodcatcherUI();


    return app->exec();

}

