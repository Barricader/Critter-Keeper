#pragma once
#include <string>

class App {
	private:
		std::string message;

	public:
		App(std::string text) {
			message = text;
		}

		std::string getMessage() {
			return message;
		}
};