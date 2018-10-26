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

#include <iostream>
TextureManager::TextureManager(const char *filename)
{
	if (!_texture.loadFromFile(filename)) {
		throw new std::runtime_error("Failed to load image (see console output)");
	}
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::Vector2u size = _texture.getSize();
	float displayRatio = (static_cast<float>(desktopMode.width) / desktopMode.height);

	_texture.setSmooth(true);
	// If image is overflowing, set downscale for the largest bound.
	if (size.x > desktopMode.width
	    || size.y > desktopMode.height) {
		_safeScale = (displayRatio > static_cast<float>(size.x) / size.y ?
			       static_cast<float>(desktopMode.height) / size.y
			       : static_cast<float>(desktopMode.width) / size.x);
		_safeSize = sf::Vector2u(size.x * _safeScale, size.y * _safeScale);
	} else {
		_safeScale = 1.0f;
		_safeSize = _texture.getSize();
	}
}

TextureManager::~TextureManager()
{
}

sf::Sprite TextureManager::getTextureAsSprite() const noexcept
{
	sf::Sprite sprite(_texture);

	sprite.setScale(_safeScale, _safeScale);
	return sprite;
}

sf::Sprite TextureManager::getPartialTextureAsSprite(sf::IntRect dimensions) const noexcept
{
	sf::Sprite sprite(_texture);
	// Deduce the original positionx from the scaled down region.
	sf::IntRect scaled(dimensions.left / _safeScale, dimensions.top / _safeScale,
			   dimensions.width / _safeScale, dimensions.height / _safeScale);

	sprite.setTextureRect(scaled);
	sprite.setScale(_safeScale, _safeScale);
	return sprite;
}

sf::Vector2u TextureManager::getSize() const noexcept
{
	return _safeSize;
}
