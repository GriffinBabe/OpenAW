#include "window.h"

Window::Window() {
	setWindowTitle(tr("Advance Wars by QtCuteTeam"));
	GLWidget *openGL = new GLWidget(&helper, this);
	QLabel *openGLLabel = new QLabel(tr("Graphics"));
	openGLLabel->setAlignment(Qt::AlignCenter);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(openGL);
	layout->addWidget(openGLLabel);
	setLayout(layout);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
	timer->start(50);
}