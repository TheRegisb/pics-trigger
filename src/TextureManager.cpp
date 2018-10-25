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

TextureManager::TextureManager(const char *filename)
{
	if (!_texture.loadFromFile(filename)) {
		throw new std::runtime_error("Failed to load image (see console output)");
	}
	_texture.setSmooth(true);
}

TextureManager::~TextureManager()
{
}

sf::Sprite TextureManager::getTextureAsSprite() const noexcept
{
	sf::Sprite sprite(_texture);

	return sprite;
}

sf::Sprite TextureManager::getPartialTextureAsSprite(sf::IntRect dimensions) const noexcept
{
	sf::Sprite sprite(_texture);

	sprite.setTextureRect(dimensions);
	return sprite;
}

sf::Vector2u TextureManager::getSize() const noexcept
{
	return _texture.getSize();
}
