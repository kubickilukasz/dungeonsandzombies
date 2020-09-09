#include "Log.h"

void Log::setCurrentTime() {

	timestr = Time::getStringTime();

}

Log::Log() : code ("_none"){
	setCurrentTime();
}

Log::Log(const std::string code) : code (code){
	setCurrentTime();
}

Log::Log(const std::string code,const std::string info) : code(code) , info(info) {
	setCurrentTime();
}

std::string Log::getStr() {

	return "[" + timestr + "]" + ":" + code + " " +  info;

}