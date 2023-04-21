/// <author>
/// Joshua Bradley
/// </author>

#include "PacMan.h"

#include <array>
#include <vector>
#include <sstream>
#include <iostream>

#include "SDL.h"

#include "MovableGameEntity.h"
#include "GameEntity.h"
#include "World.h"
#include "RedGhost.h"
#include "CyanGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include "Ghost.h"
#include "Vector2.h"
#include "Drawer.h"
#include "Avatar.h"

// The length of a square tile in pixels.
const int PacMan::kTileSize = 22;

// Prevents regular object construction.
PacMan::PacMan()
    : 
  drawer_(nullptr),
  game_over_(false),
  score_(0),
  frames_per_second_(0),
  fps_counter_(0),
  lives_(0),
  world_(nullptr),
  avatar_(nullptr),
  ghosts_({}) {
  return;
}

PacMan::PacMan(Drawer* drawer)
  : drawer_(drawer),
    game_over_(false),
	  score_(0),
	  frames_per_second_(0),
    fps_counter_(0),
	  lives_(3),
	  world_(new World()),
    avatar_(new Avatar(Vector2<float>(14.5f, 22.f))),
    ghosts_({
      new RedGhost(Vector2<float>(14.5f, 10.f)),
      new CyanGhost(Vector2<float>(13.f, 13.f)),
      new PinkGhost(Vector2<float>(14.5f, 13.f)),
      new OrangeGhost(Vector2<float>(16.f, 13.f))
    }) {
  try {
    world_->Init();
  }
  catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}

PacMan& PacMan::Instance(Drawer* drawer) {
  static PacMan instance(drawer);

  return instance;
}

bool PacMan::Update(unsigned int elapsed_millis) {
  /*
   * Reads keyboard input.
   * Includes the escape key to exit and arrow keys for directions.
   */ 
  if (!UpdateInput()) {
    return false;
  }

  // Displays FPS every 500 ms.
  if ((fps_counter_ -= elapsed_millis) <= 0) {
    // Calculate FPS.
    if (elapsed_millis > 0) {
      frames_per_second_ = static_cast<unsigned short>(1000 / elapsed_millis);
    }

    fps_counter_ = 500;
  }

  // True if the conditions to make the game end have been met.
  if (CheckEndGameCondition()) {
    // Ensures the game element reset only occurs on the first instance of the game ending.
    if (!game_over_) {
      Reset();
    }

    game_over_ = true;
    return true;
  }

  // Update MovableGameEntities.
  avatar_->Update(elapsed_millis, world_);
  Ghost::Update(elapsed_millis, world_, ghosts_);

  // Check for Avatar intersection with Dots.
  if (world_->CheckDotIntersection(avatar_->position())) {
    score_ += 10;
  }

  // Check for Avatar intersection with Power Pellets.
  if (world_->CheckPowerPelletIntersection(avatar_->position())) {
    score_ += 50;
    avatar_->ResetGhostsCaughtInRow();

    Ghost::HandleVulnerableEvent(ghosts_);
  }

  std::vector<Ghost*> claimed_ghosts {};
  claimed_ghosts.reserve(4);

  bool apply_claimed_effects = false;

  for (auto& g : ghosts_) {
    // True if the Avatar has made contact with the Ghost.
    if ((g->position() - avatar_->position()).GetLength() < 10) {
      // True if the Ghost is alive and not vulnerable.
      if (g->state() == Ghost::state::healthy) {
        // Immediately returns if the player does not have any more lives.
        if (--lives_ < 1) {
          return true;
        }

        // Resets the game elements for the next life.
        Reset();
        return true;
      }

      // If colliding with a vulnerable Ghost, add it to a buffer.
      if (g->state() == Ghost::state::vulnerable) {
        claimed_ghosts.push_back(g);
        apply_claimed_effects = true;
      }
    }
  }


  if (apply_claimed_effects) {
    // Kills all claimed Ghosts.
    for (auto& g : claimed_ghosts) {
      // The score increases by 200, 400, 800, 1600.
      score_ += static_cast<unsigned short>(200 * 1 << avatar_->IncrementGhostsCaughtInRow());
      g->Die(world_);
    }
  }
 	
  return true;
}

bool PacMan::UpdateInput() {
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  
  // Updates the movement direction based on keyboard key input.
  if (keystate[SDL_SCANCODE_UP]) {
	  avatar_->set_direction(Vector2<char>::up, world_);
  } else if (keystate[SDL_SCANCODE_DOWN]) {
    avatar_->set_direction(Vector2<char>::down, world_);
  } else if (keystate[SDL_SCANCODE_RIGHT]) {
    avatar_->set_direction(Vector2<char>::right, world_);
  } else if (keystate[SDL_SCANCODE_LEFT]) {
    avatar_->set_direction(Vector2<char>::left, world_);
  }

  // Escape Key is used for exiting the application.
  return !keystate[SDL_SCANCODE_ESCAPE];
}

// Returns true if there aren't any Dots remaining in the world.
bool PacMan::CheckEndGameCondition() const {
  return !world_->CheckDotsRemaining() || lives_ == 0;
}

void PacMan::Draw(unsigned int elapsed_millis) {
  world_->Draw(drawer_, elapsed_millis);
  avatar_->Draw(drawer_);

  for (Ghost* g : ghosts_) {
    g->Draw(drawer_);
  }

  DrawUI();
}

void PacMan::DrawUI() const
{
  // Drawing lives info.
  std::string livesString;
  std::stringstream liveStream;

  liveStream << lives_;
  livesString = liveStream.str();

  for (unsigned char i = 0; i < lives_; i++) {
    drawer_->Draw("Avatar/Open-Left.png", Vector2<float>(20.f + 40.f * i, 50.f));
  }

  // Drawing score text.
  std::string score_string;
  std::stringstream score_stream;

  score_stream << score_;
  score_string = score_stream.str();
  
  drawer_->DrawText(score_string.c_str(), Vector2<float>(20.f, 100.f));  

  // Display FPS text.
  std::string fps_string;
  std::stringstream fps_stream;

  fps_stream << frames_per_second_;
  fps_string = fps_stream.str();

  drawer_->DrawText(fps_string.insert(0, "FPS: ").c_str(), Vector2<float>(852.f, 50.f));

  // Display end game text.
  if (game_over_) {
    if (lives_ > 0) {
      drawer_->DrawText("LEVEL CLEARED!", Vector2<float>(381.f, 418.f), SDL_Color {252, 252, 0});
    } else {
      drawer_->DrawText("GAME OVER", Vector2<float>(426.f, 418.f), SDL_Color{252, 0, 0});
    }
  }
}

void PacMan::Reset() {
  avatar_->Reset();
  Ghost::Reset(world_, ghosts_);
}