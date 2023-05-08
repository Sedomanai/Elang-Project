#pragma once

#include <QDialog>
#include <qspinbox.h>
#include "elang/common/string.h"

#include "ui_auto_gen.h"

namespace el
{
	class AtlasAutoGenerator : public QDialog
	{
		Q_OBJECT

	public:
		AtlasAutoGenerator(QWidget* parent = Q_NULLPTR);
		~AtlasAutoGenerator();

		uint sortorder, margin;
		bool gen;
	private:
		Ui::AtlasAutoGeneratorUI ui;
		void closeEvent(QCloseEvent*) override;
	};

}
