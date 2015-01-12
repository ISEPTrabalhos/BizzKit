#include "Upload.h"
#include "ServicesHandler.h"

int Upload::uploadProgress(string username, int positions [])
{
	ServicesHandler *service = new ServicesHandler;
	int res = service->uploadRoute(username, positions);
	return res;
}

