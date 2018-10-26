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
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

sf::IntRect regionSelector(sf::Sprite fullImage, sf::Vector2u fullSize);
int triggerPlayer(sf::Sprite partialImage, sf::Vector2u partialSize);
void swap(int *left, int *right);

int picstrigger(const char *filename)
{
	try {
		TextureManager tm(filename);
		sf::IntRect region = regionSelector(tm.getTextureAsSprite(),
						    tm.getSize());

		if (region == sf::IntRect(0, 0, 0, 0)) {
			return EXIT_SUCCESS;
		}
		if (region.width < region.left) {
			swap(&region.width, &region.left);
		}
		if (region.height < region.top) {
			swap(&region.height, &region.top);
		}
		return triggerPlayer(tm.getPartialTextureAsSprite(region),
				     sf::Vector2u(std::abs(region.width - region.left),
						  std::abs(region.height - region.top)));
	} catch (const std::runtime_error &e) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

sf::IntRect regionSelector(sf::Sprite fullImage, sf::Vector2u fullSize)
{
	sf::RenderWindow window(sf::VideoMode(fullSize.x, fullSize.y),
				"Region selector");
	sf::IntRect region(0, 0, 0, 0);
	sf::RectangleShape visualSelect;
	bool isSelecting = false;

	window.setFramerateLimit(60);
	visualSelect.setOutlineColor(sf::Color::Red);
	visualSelect.setFillColor(sf::Color(0, 0, 0, 0));
	visualSelect.setOutlineThickness(2);
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				region.left = sf::Mouse::getPosition(window).x;
				region.top = sf::Mouse::getPosition(window).y;
				isSelecting = true;
				visualSelect.setPosition(region.left, region.top);
				break;
			case sf::Event::MouseMoved:
				if (isSelecting) {
					visualSelect.setSize(
						sf::Vector2f(sf::Mouse::getPosition(window).x - region.left,
							     sf::Mouse::getPosition(window).y - region.top));
				}
				break;
			case sf::Event::MouseButtonReleased:
				region.width = sf::Mouse::getPosition(window).x;
				region.height = sf::Mouse::getPosition(window).y;
				window.close();
			}
		}
		window.clear();
		window.draw(fullImage);
		window.draw(visualSelect);
		window.display();
	}
	return region;
}

// TODO
// add color overlay(s ?) and "triggered" tagline
int triggerPlayer(sf::Sprite partialImage, sf::Vector2u partialSize)
{
	sf::RenderWindow window(sf::VideoMode(partialSize.x, partialSize.y),
				"triggered");
	sf::Texture sheet;
	const unsigned int TMP_SHEET_SIZE = 6;
	auto size = window.getSize();
	sheet.create(size.x * TMP_SHEET_SIZE, size.y);

	window.setFramerateLimit(60);
	srand(time(nullptr));
	// Upscale the image by 5% to avoid displaying black bar.
	partialImage.setScale(partialImage.getScale().x * 1.05f,
			      partialImage.getScale().y * 1.05f);
	partialImage.setPosition(-5.0f, -5.0f);
	int loop = 0;
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		partialImage.setPosition((rand() % 10) - 10,
					 (rand() % 10) - 10);
		window.clear();
		window.draw(partialImage);
		if (loop < TMP_SHEET_SIZE) {
			sf::Texture windowContent;
			windowContent.create(size.x, size.y);
			windowContent.update(window);
			sf::Image screenshot = windowContent.copyToImage();
			sheet.update(screenshot, size.x * loop, 0);
			loop++;
		} else if (loop == TMP_SHEET_SIZE) {
			sheet.copyToImage().saveToFile("/tmp/picstrigger_sheet.jpg");
			loop++;
		}
		window.display();
	}
	return 0;
}

void swap(int *left, int *right)
{
	int tmp = *left;

	*left = *right;
	*right = tmp;
}
