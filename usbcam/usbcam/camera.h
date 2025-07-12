#pragma once
#include <string>
using namespace std;
struct camerainfo
{
	std::string vid_path;
};
struct boblov : public camerainfo
{
	const std::string log_path = "LOG";
	boblov()
	{
		vid_path = "FILE\\100china";

	}
	bool isType(string path)
	{

	}
};


