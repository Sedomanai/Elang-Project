#include "elang/elpch.h"
#include "logo.h"

#include "elang/registry/asset_loader.h"
#include <QDebug>
#include <QImageReader>
namespace el
{
	QElangLogo::QElangLogo(QString logoImagePath, QWidget* parent)
		: QWidget(parent), mWidget(0) {
		setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		setAttribute(Qt::WA_NoSystemBackground);
		setAttribute(Qt::WA_TranslucentBackground);
		setAttribute(Qt::WA_TransparentForMouseEvents);
		setAttribute(Qt::WA_DeleteOnClose);

		ui.setupUi(this);

		cout << "Initiating..." << endl;
		if (mLogo.load(logoImagePath)) {
			mWidget = new QWidget();
			mWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
			mWidget->setAttribute(Qt::WA_NoSystemBackground);
			mWidget->setAttribute(Qt::WA_TranslucentBackground);
			mWidget->setAttribute(Qt::WA_TransparentForMouseEvents);

			auto label = new QLabel(mWidget);
			auto pixmap = QPixmap::fromImage(mLogo);
			label->setPixmap(pixmap);
			label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			QPalette paleta;
			paleta.setBrush(mWidget->backgroundRole(), QBrush(pixmap));
			label->setPalette(paleta);
 
			setMaximumSize(label->pixmap().size());
			mWidget->setMaximumSize(size());
			label->setMinimumSize(size());

			mWidget->show();
		} else {
			cout << "Logo not loaded... check path " << string(logoImagePath.toUtf8().constData()) << endl;
		}
		
		// don't ask why
		mCounter = 2;
		ui.openGLWidget->sig_Paint.connect([&]() {
			if (mCounter >= 0) {
				mCounter--;
				if (mCounter == 0 && mWidget) {
					cout << "Initializing GLEW..." << endl;
					glewInit();
					AssetLoader loader;
					cout << "Importing Native GUI..." << endl;
					loader.initCommonAssets();
					loader.importAllGUIAssets();
					sig_Loaded.invoke();
				}
			}
		});
	}

	void QElangLogo::closeEvent(QCloseEvent* e) {
		mLogo = QImage();
		if (mWidget) {
			delete mWidget;
			mWidget = 0;
		}
	}

	QElangLogo::~QElangLogo() {
	

	}
}