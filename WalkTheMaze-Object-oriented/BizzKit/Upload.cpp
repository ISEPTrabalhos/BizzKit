#include "Upload.h"
#include "ServicesHandler.h"

int Upload::uploadProgress(string username, int score, int pos_x, int pos_y)
{
	ServicesHandler *service = new ServicesHandler;
	int res = service->uploadRoute(username, score, pos_x, pos_y);
	return res;
}
