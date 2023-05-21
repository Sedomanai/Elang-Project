/*****************************************************************//**
 * @file   main_window.h
 * @brief  Custom extension for QMainWindow.
 *		   The functionalities of some of the built-in QT widgets is either not enough or requires a workaround.
 *		   This extension not only helps extend those functionalities, it also provides a catch-all interface
 *		   that does not require one inheriting from either the base QT class or this class.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/

#pragma once
#include "elang/common/signal.h"

namespace el {
	/**
	 * Custom extension for QMainWindow.
	 * 
	 * The interface is built around signals and slots.
	 * Custom signals and slots were used over QSignals and QSlots.
	 * The reason for that is actually consistency - there were some cases where QSignals and QSlots cannot satisfy.
	 */
	class QMainWindowExtension : public QMainWindow
	{
		Q_OBJECT

	public:
		signal<> sig_Shown;
		void showEvent(QShowEvent* event) override;

		//void dropEvent(QDropEvent* event) override;
		//void focusInEvent(QFocusEvent*) override;
		//void focusOutEvent(QFocusEvent*) override;
		//void mousePressEvent(QMouseEvent*) override;
		//void keyPressEvent(QKeyEvent*) override;
		//void keyReleaseEvent(QKeyEvent*) override;
	};
}