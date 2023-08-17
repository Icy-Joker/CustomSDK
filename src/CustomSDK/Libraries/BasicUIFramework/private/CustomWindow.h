#pragma once

#include <QWidget>

class CustomWindowTitleBar;

class CustomWindow : public QWidget
{
	Q_OBJECT
public:
	CustomWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::Widget);
	~CustomWindow();
public:
	void setCentralWidget(QWidget*);
	QWidget* centralWidget();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
private:
	void initializeUI();
	void initializeFunction();
	void connectSignals();
private:
	CustomWindowTitleBar * title_bar;

	QWidget* widget_center;
};