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

void GLWidget::animate() {
	elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 100;
	update();
}
	
void GLWidget::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	helper->paint(&painter, event, elapsed);
	painter.end();
}