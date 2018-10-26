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

#include <iostream>

constexpr int VERSION_MAJOR = 1;
constexpr int VERSION_MINOR = 0;

int optionsHandle(const char *);

int main(int ac, char **av)
{
	if (ac == 2 && av[1][0] == '-') {
		return optionsHandle(av[1]);
	} else if (ac != 2) {
		std::cerr << av[0] << ": Bad syntax, "
			  << "type " << av[0] << " --help for more info."
			  << std::endl;
		return EXIT_FAILURE;
	}
	return picstrigger(av[1]);
}

int optionsHandle(const char *arg)
{
	switch (hash(arg)) {
	case (hash("--version")):
	case (hash("-v")):
		std::cout << "pics-trigger, "
			  << "version " << VERSION_MAJOR << "." << VERSION_MINOR
			  << ", made by Régis Berthelot, licensed under the "
			  << "Apache Licence version 2.0"
			  << std::endl;
		return EXIT_SUCCESS;
	case (hash("--help")):
	case (hash("-h")):
		std::cout << "Usage: pics-trigger [OPTION] [image-file]"
			  << std::endl << std::endl
			  << "  -h,--help" << std::endl
			  << "\t\tDisplay this help message"
			  << std::endl
			  << "  -v,--version" << std::endl
			  << "\t\tDisplay version number, author and licensing"
			  << std::endl;
	return EXIT_SUCCESS;
	default:
		std::cerr << "bad arg + help" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}
