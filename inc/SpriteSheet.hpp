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

#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

class SpriteSheet {

public:
  enum SheetState {
    BUILDING,
    READY,
    DONE  
  };
		   
  SpriteSheet(sf::Vector2u &singleFrameSize, unsigned int frameCount);
  SpriteSheet(sf::Vector2u singleFrameSize, unsigned int frameCount);

  bool addFrame(sf::Image &frame);
  bool addFrame(sf::Image frame);
  SheetState getState() const noexcept;
  bool saveToFile(const std::string &filename);

private:

  sf::Texture spriteSheet_;
  sf::Vector2u frameSize_;
  unsigned int maxCount_;
  SheetState state_;
};
