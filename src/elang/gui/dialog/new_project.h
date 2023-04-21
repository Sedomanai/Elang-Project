#pragma once

#include <qmessagebox.h>
#include <qfiledialog>
#include <qdialog>
#include "../uic/ui_new_project.h"


namespace el {

	class NewProjectDialog : public QDialog
	{
		Q_OBJECT

	public:
		NewProjectDialog(QWidget* parent = Q_NULLPTR);
		QString saveNewProject(Project& project);
		bool accepted;
	private:
		Ui::NewProjectUI ui;
	};
} 
