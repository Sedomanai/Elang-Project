#include "elang/elpch.h"
#include "elang/gui/widget/logo.h"
#include "elproj/atlas_editor/q_elang_atlas_editor.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    el::QElangLogo* logo = new el::QElangLogo("../__el_gui/logo.png");

    bool applicationOpened = false;
    logo->sig_Loaded.connect([&]() {
        auto atlas_editor = new el::QElangAtlasEditor;
        atlas_editor->sig_Shown.connect([&]() {
            if (!applicationOpened) {
                //cout << "close logo" << endl;
                logo->close();
                applicationOpened = true;
            }
            });
        atlas_editor->show();
        });
    logo->show();

    return a.exec();
}