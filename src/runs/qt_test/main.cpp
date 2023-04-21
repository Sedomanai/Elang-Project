#include "elang/elpch.h"
#include "elang/gui/widget/logo.h"
#include "elang/gui/extension/main_window.h"
// #include  <atlas/q_elang_atlas_editor.h>

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QApplication a(argc, argv);

    el::QElangLogo* logo = new el::QElangLogo("../gui/logo.png");

    bool applicationOpened = false;
    logo->sig_Loaded.connect([&]() {
        //el::QElangAtlasEditor* test = new el::QElangAtlasEditor;
        auto test = new el::QMainWindowExtension;
        test->sig_Shown.connect([&]() {
            if (!applicationOpened) {
                //cout << "close logo" << endl;
                logo->close();
                applicationOpened = true;
            }
            });
        test->show();
    });
    logo->show();

	return a.exec();
}