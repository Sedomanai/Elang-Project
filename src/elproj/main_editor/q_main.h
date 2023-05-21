#pragma once
#include <qmainwindow.h>
#include <elang/common/signal.h>
#include "q_main_ui.h"

namespace el
{
	class QElangMainEditor : public QMainWindow
	{
		Q_OBJECT
	public:
		QElangMainEditor(QWidget* parent = nullptr);
		signal<> sig_Shown;
	private:
		void showEvent(QShowEvent* e) override;
		Ui::MainWindow ui;
	};
}

