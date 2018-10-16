#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {

	string args[] = { "Hey", "Those", "Are", "Arguments" };
	Game game(args);
	qInfo("Starting game");
	game.printArgs();

	QApplication a(argc, argv);
	Window w;
	w.show();
	return a.exec();
}
