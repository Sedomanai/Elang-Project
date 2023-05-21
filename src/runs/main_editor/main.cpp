#include "elang/elpch.h"
#include "elgui/widget/logo.h"
#include "elproj/atlas_editor/q_elang_atlas_editor.h"
#include "elproj/main_editor/q_main.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icon.png"));

    el::QElangLogo* logo = new el::QElangLogo("../__el_gui/logo.png");

    bool applicationOpened = false;
    logo->sig_Loaded.connect([&]() {
        auto main_editor = new el::QElangMainEditor;
        main_editor->sig_Shown.connect([&]() {
            if (!applicationOpened) {
                logo->close();
                applicationOpened = true;
            }});
        main_editor->show();
    });
    logo->show();

    return a.exec();
}