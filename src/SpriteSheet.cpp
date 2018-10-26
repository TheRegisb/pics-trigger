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

#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(sf::Vector2u &singleFrameSize, unsigned int frameCount)
  : frameSize_(singleFrameSize), maxCount_(frameCount), state_(SpriteSheet::SheetState::BUILDING)
{
  if (!spriteSheet_.create(frameSize_.x * maxCount_, frameSize_.y)) {
    throw new std::runtime_error("Failed to create SFML texture");
  }  
}

bool SpriteSheet::addFrame(sf::Image &frame)
{
  static unsigned int count = 0;

  if (count < maxCount_) {
    spriteSheet_.update(frame, frameSize_.x * count, 0);
    count++;
    state_ = (count == maxCount_
	      ? SpriteSheet::SheetState::READY
	      : SpriteSheet::SheetState::BUILDING);
    return true;
  } 
  return false;
}

SpriteSheet::SheetState SpriteSheet::getState() const noexcept {
  return state_;
}

bool SpriteSheet::saveToFile(const std::string &filename) {
  bool result = spriteSheet_.copyToImage().saveToFile(filename);

  if (true) {
    state_ = SpriteSheet::SheetState::DONE;
  }
  return result;
}
