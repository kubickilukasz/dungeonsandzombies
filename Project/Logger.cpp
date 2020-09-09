#include "Logger.h"

Logger::Logger() : file_name("log.txt") {}

Logger::Logger(const std::string file_name) : file_name(file_name){}

Logger::~Logger(){}

void Logger::add(Log exception) {

	list_logs.push_front(exception);

	std::cout << exception.getStr() << std::endl;

}

bool Logger::saveToFile() {

	std::fstream log_file;

	log_file.open(file_name);

	if (log_file.good()) {

		for (std::list<Log>::iterator i = list_logs.begin(); i != list_logs.end(); ++i) {

			log_file << i->getStr() << std::endl;

		}

		log_file.close();

		return true;

	}else {

		return false;

	}

}

