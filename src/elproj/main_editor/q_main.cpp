#include "elang/elpch.h"
#include "q_main.h"

namespace el
{
	QElangMainEditor::QElangMainEditor(QWidget* parent) {
		ui.setupUi(this);
		fio::create_directories("../__el_gui/dat");
		cout << "Connecting Main GUI Editor..." << endl;
	}

	void QElangMainEditor::showEvent(QShowEvent* e) {
		QTimer* timer = new QTimer(this);
		timer->singleShot(500, [&]() { sig_Shown.invoke(); });
	}
}