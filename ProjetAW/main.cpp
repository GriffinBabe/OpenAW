#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);
	Window w;
	w.show();
	return a.exec();
}
