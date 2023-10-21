// LearnReadInitFile.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "ReConfig.h"
#include <fstream>
#include <cassert>

int main() {

	rr::ReConfig config;
	bool ret = config.ReadConfig("config.ini");
	if (ret == false) {
		printf("ReadConfig is Error,Cfg=%s", "config.ini");
		return 1;
	}
	std::string HostName = config.ReadString("MYSQL", "HostName", "");
	int Port = config.ReadInt("MYSQL", "Port", 0);
	std::string UserName = config.ReadString("MYSQL", "UserName", "");
	std::string ren = config.ReadString("MYSQL", "renpenglong", "");
	std::cout << "HostName=" << HostName << std::endl;
	std::cout << "Port=" << Port << std::endl;
	std::cout << "UserName=" << UserName << std::endl;
	std::cout << "renpenglong=" << ren << std::endl;
	return 0;
}


