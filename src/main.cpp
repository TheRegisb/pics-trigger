// Copyright 2018 Régis Berthelot

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "pics-trigger.hpp"
#include "hashUtils.hpp"
#include "Parameters.hpp"

#include <iostream>
#include <sstream>
#include <regex>

constexpr int VERSION_MAJOR = 1;
constexpr int VERSION_MINOR = 1;
constexpr int CODE_CONTINUE = 0xCAFE;

int optionsHandle(char **);
void displayVersion();
void displayHelp();
bool setFrameCount(const char *str);
bool setTint(const char *str);

int main(int ac, char **av)
{
	int retCode;
	int indexOfLastElement;

	if (ac == 1) {
		std::cerr << av[0] << ": Bad syntax, "
			  << "type " << av[0] << " --help for more info."
			  << std::endl;
		return EXIT_FAILURE;
	}
	if ((retCode = optionsHandle(av)) != CODE_CONTINUE) {
		return retCode;
	}
	for (indexOfLastElement = 0; av[indexOfLastElement + 1] != nullptr; indexOfLastElement++);
	return picstrigger(av[indexOfLastElement]);
}

int optionsHandle(char **args)
{
	for (int i = 1; args[i + 1] != nullptr; i++) {
		switch (hash(args[i])) {
		case (hash("--version")):
		case (hash("-v")):
			displayVersion();
		return EXIT_SUCCESS;

		case (hash("--help")):
		case (hash("-h")):
			displayHelp();
		return EXIT_SUCCESS;

		case (hash("--frames")):
		case (hash("-f")):
			if (setFrameCount(args[i + 1])) {
				i++;
				break;
			} else {
				return EXIT_FAILURE;
			}
		break;

		case (hash("--no-playback")):
		case (hash("-p")):
			Parameters::get().setKeepOnPlaying(false);
		break;

		case (hash("-t")):
		case (hash("--tint")):
			if (setTint(args[i + 1])) {
				i++;
				break;
			} else {
				return EXIT_FAILURE;
			}
		break;

		default:
			std::cerr << "Error: Unknown error" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return CODE_CONTINUE;
}

void displayVersion() {
	std::cout << "pics-trigger, "
		  << "version " << VERSION_MAJOR << "." << VERSION_MINOR
		  << ", made by Régis Berthelot, licensed under the "
		  << "Apache Licence version 2.0"
		  << std::endl;
}

void displayHelp() {
	std::cout << "Usage: pics-trigger [OPTION] [image-file]"
		  << std::endl << std::endl
		  << "  -h,--help" << std::endl
		  << "\t\tDisplay this help message"
		  << std::endl
		  << "  -v,--version" << std::endl
		  << "\t\tDisplay version number, author and licensing"
		  << std::endl
		  << "  -f,--frames" << std::endl
		  << "\t\tNumber of frames in the output sheet, must be greater than zero"
		  << std::endl
		  << "  -p,--no-playback" << std::endl
		  << "\t\tStop the program once the sprite sheet is completed"
		  << std::endl;
}

bool setFrameCount(const char *str) {
	int frameCount;

	if (!str) {
		std::cerr << "Error: Missing frames count" << std::endl;
		return false;
	}
	try {
		frameCount = std::stoi(str);
	} catch (const std::invalid_argument &e) {
		std::cerr << "Error: Frames count is not a valid number" << std::endl;
		return false;
	}
	if (frameCount <= 0) {
		std::cerr << "Error: Frames count cannot be lower than one" << std::endl;
		return false;
	}
	Parameters::get().setNumberOfFrames(frameCount);
	return true;
}

bool setTint(const char *str) {
	std::stringstream ss;
	unsigned int rgba;

	if (!str) {
		std::cerr << "Error: Missing RGB value for tint" << std::endl;
		return false;
	}
	if (!std::regex_match(str, std::regex("^[0-9A-Fa-f]{6}$"))) {
		std::cerr << "Error: Not a valid RGB value" << std::endl;
		return false;
	}
	ss << std::hex << str << "FF";
	ss >> rgba;
	Parameters::get().setColorTint(rgba);
	return true;
}
