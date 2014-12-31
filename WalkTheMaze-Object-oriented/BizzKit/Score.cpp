#include "Score.h"
#include "ServicesHandler.h"

int Score::uploadScore(string username,string levelName, int score)
{
	ServicesHandler *service = new ServicesHandler();
	int points = service->score(username, levelName, score);
	return points;
}