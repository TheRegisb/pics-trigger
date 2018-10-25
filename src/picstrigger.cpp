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

#include "TextureManager.hpp"

int picstrigger(const char *filename)
{
	try {
		TextureManager tm(filename);
	} catch (const std::runtime_error &e) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// TODO display the entire image,
// let user do a cursor selection and return rectangle coords
sf::Vector2u regionSelector(sf::Sprite &fullImage, sf::Vector2u fullSize)
{
	// sf::RenderWindow window(sf::VideoMode(tm.getSize().x, tm.getSize().y), "Region selector");
	// while (window.isOpen())
	// {
	// 	sf::Event event;
	// 	while (window.pollEvent(event))
	// 	{
	// 		if (event.type == sf::Event::Closed)
	// 			window.close();
	// 	}
	// 	window.clear();
	// 	window.draw(sprite);
	// 	window.display();
	// }
	// return EXIT_SUCCESS;
	return sf::Vector2u(0, 0);
}

// TODO display the partial image
// make it jitter around, with overlay, and "triggered" tagline
int triggerPlayer(sf::Sprite &partialImage)
{
	return 0;
}
