#include "4.3.2.h"
#include <random>
#include <ctime>

CardApp::CardApp(const TCHAR* appName)
	: Application(appName)
{
}

CardApp::CardApp(const TCHAR* appName, int width, int height, int x, int y)
	: Application(appName, width, height, x, y)
{}

void CardApp::mouseDown(int x, int y)
{
	static std::mt19937 engine(static_cast<unsigned long>(time(nullptr)));
	static std::uniform_int_distribution<int> distSuit(1, 4);
	static std::uniform_int_distribution<int> distRank(1, 13);
	figures.push_back(std::make_shared<Card>(x, y, distSuit(engine), distRank(engine)));
	std::static_pointer_cast<Card>(figures.back())->flip();
	clearAndUpdate();
}

void CardApp::mouseRDown(int x, int y)
{
	figures.push_back(std::make_shared<Circle>(x, y, 40));
	clearAndUpdate();
}

void CardApp::paint()
{
	for (auto& i : figures)
		i->draw(*this);
}

int mainLAF()
{
	CardApp app(TEXT("Cards"));

	app.run();

	return 0;
}
