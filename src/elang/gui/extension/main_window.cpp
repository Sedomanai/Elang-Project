#include "main_window.h"

void el::QMainWindowExtension::showEvent(QShowEvent* event) {
	sig_Shown.invoke();
}
