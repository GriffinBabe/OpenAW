#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

	string args[] = { "Hey", "Those", "Are", "Arguments" };
	Game game(args);
	qDebug("Starting game");
	game.printArgs();

	QApplication a(argc, argv);
	Window w;
	w.show();
	qDebug("going tu return");
	return a.exec();
}
