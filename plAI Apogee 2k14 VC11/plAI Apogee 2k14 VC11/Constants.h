#pragma once

#define PI 3.1416f

#define GAME_DESIRED_UPDATE_FPS 60
#define GAME_DESIRED_DRAW_FPS 60
#define GAME_VERTICAL_SYNC_ENABLED true

#define GAME_FONT "C:\\Windows\\Fonts\\Calibri.ttf"

#define DEFAULT_MAP_PATH "Maps\\good map 1366x768.bmp"
#define WATER_TEXTURE_PATH "Images\\water.jpg"
#define GRASS_TEXTURE_PATH "Images\\grass.png"
#define RAFT1_TEXTURE_PATH "Images\\raft1.png"
#define RAFT2_TEXTURE_PATH "Images\\raft2.png"
#define FISH_TEXTURE_PATH "Images\\fish\\whale 32.png"
#define IEEE_LOGO_PATH "Images\\ieee_mb_white.png"
#define BITS_LOGO_PATH "Images\\bits.png"
#define APOGEE_LOGO_PATH "Images\\apogee.png"

//sounds:
#define FISH_COLLECT_SOUND_PATH "C:/Windows/Media/tada.wav"
#define LAND_COLLISION_SOUND_PATH "C:/Windows/Media/windows default.wav"
#define INTER_RAFT_COLLISION_SOUND_PATH "sounds\\Collision interraft.wav"
#define CANNON_BALL_FIRE_SOUND_PATH "sounds\\explosion-fire.wav"
#define CANNON_BALL_STRIKE_SOUND_PATH "sounds\\Explosion cannon hit.wav"
#define WELCOME_MUSIC_PATH "sounds\\welcome.ogg"
#define BACKGROUND_MUSIC_PATH "sounds\\background.ogg"
#define WATER_MUSIC_PATH "sounds\\ocean.ogg"
#define CREDITS_MUSIC_PATH "sounds\\credits.ogg"
//#define PLAYER1_HEADER_FILE "HumanPlayerWASD.h"
//#define PLAYER1_CLASS_NAME HumanPlayerWASD
#define PLAYER1_HEADER_FILE "SampleAIPlayer.h"
#define PLAYER1_CLASS_NAME SampleAIPlayer
#define PLAYER2_HEADER_FILE "param_name.h"
#define PLAYER2_CLASS_NAME param_name

#define FISH_WIDTH 36
#define FISH_HEIGHT 36
#define FISH_PRESENSE_RADIUS 18

#define RAFT_RADIUS 30
#define RAFT_MASS 1000.0f
#define RAFT_ENGINE_FORCE 400.0f * RAFT_MASS
#define RAFT_DRAG_REGULAR 10.0f
#define RAFT_DRAG_BRAKE 50.0f
#define RAFT_COEFF_RESTITUTION 0.2f
#define RAFT_VISIBILITY_RADIUS 150
#define RAFT_MAX_HEALTH 100
#define RAFT_NUMBER_OF_COLLISION_POINTS 36


#define CANNON_BALL_SPEED 200 //pixels per second
#define CANNON_BALL_RADIUS 3 //pixels
#define CANNONBALL_DAMAGE 1
#define CANNONBALL_FIRE_MIN_LAG 0.5f //in seconds

#define COLOR_VISIBILITY_REGION sf::Color(255, 255, 255, 30)

#define NUMBER_OF_PRESET_FISH_SPRITES 9

#define RIPPLEMAP_WIDTH 320
#define RIPPLEMAP_HEIGHT 180

#define LOGO_HEIGHT 20
#define INFO_BAR_HEIGHT 30