#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "../game-source-code/GameEngine.h"
#include "../game-source-code/World.h"
#include "../game-source-code/Maze.h"
#include "../game-source-code/Player.h"
#include "../game-source-code/GameObject.h"
#include "../game-source-code/GameOverState.h"
#include "../game-source-code/GameState.h"
#include "../game-source-code/GameStateMachine.h"
#include "../game-source-code/PauseState.h"
#include "../game-source-code/Pickup.h"
#include "../game-source-code/ResourceHolder.h"
#include "../game-source-code/ResourceIdentifiers.h"
#include "../game-source-code/SplashState.h"
#include "../game-source-code/SpriteNode.h"
#include "../game-source-code/TextNode.h"
#include "../game-source-code/State.h"
#include "../game-source-code/StateIdentifiers.h"
#include "../game-source-code/Tile.h"
#include "../game-source-code/Door.h"
#include "../game-source-code/Utility.h"
#include "../game-source-code/DataTables.h"


//Game Engine Tests
TEST_CASE("Game Engine is Initialised Successfully")
{
    CHECK_NOTHROW(GameEngine());
}

//World Tests
TEST_CASE("World is Initialised with Player Object Successfully")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    CHECK(mWorld.hasAlivePlayer());


}

TEST_CASE("World is Initialised with Edible Objects Successfully")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    CHECK(mWorld.hasEdibles());


}
//Maze Tests
TEST_CASE("Maze is Initialised with Edible Objects Successfully")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    Maze mMaze{ mWorld.getTextures()};

    CHECK(mMaze.Pickupcount() > 0);


}
//
TEST_CASE("Maze  Contains Player Spawn Position")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    Maze mMaze{mWorld.getTextures()};

    CHECK(mMaze.playerSpawn() != sf::Vector2f(0.f,0.f));


}
//
//
TEST_CASE("Maze  Contains Enemy Spawn Position")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    Maze mMaze{ mWorld.getTextures()};

    CHECK(mMaze.enemySpawn() != sf::Vector2f(0.f,0.f));


}

TEST_CASE("Enemy Spawn Position is Not Equal Player Spawn Position")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    Maze mMaze{ mWorld.getTextures()};

    CHECK(mMaze.enemySpawn() != mMaze.playerSpawn());


}


//Player Tests
TEST_CASE("Player Object is Initialised with Correct Spawn Position")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    Maze mMaze{ mWorld.getTextures()};

    CHECK(mMaze.playerSpawn() == mWorld.getPlayer().getPosition());

}

TEST_CASE("Player Object Moves")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};

    auto LEFT  = sf::Vector2f(-1,0);
    mWorld.getPlayer().setVelocity(LEFT);
    auto TimePerFrame = sf::seconds(1.f/60.f);
    mWorld.update(TimePerFrame);

    CHECK_FALSE(mMaze.playerSpawn() == mWorld.getPlayer().getPosition());


}
//
TEST_CASE("Player Object Moves Left")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};


    auto position = mWorld.getPlayer().getPosition();
    auto LEFT  = sf::Vector2f(-1,0);
    mWorld.getPlayer().setVelocity(LEFT);
    auto TimePerFrame = sf::seconds(1.f/60.f);
    mWorld.update(TimePerFrame);

    CHECK( position.x > mWorld.getPlayer().getPosition().x );


}
//
//
TEST_CASE("Player Object Moves Right")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};


    auto position = mWorld.getPlayer().getPosition();
    auto RIGHT  = sf::Vector2f(1,0);
    mWorld.getPlayer().setVelocity(RIGHT);
    auto TimePerFrame = sf::seconds(1.f/60.f);
    mWorld.update(TimePerFrame);

    CHECK( position.x < mWorld.getPlayer().getPosition().x );


}
//
TEST_CASE("Player Object Moves Up")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};


    auto position = mWorld.getPlayer().getPosition();
    auto RIGHT  = sf::Vector2f(0,-1);
    mWorld.getPlayer().setVelocity(RIGHT);
    auto TimePerFrame = sf::seconds(1.f/60.f);
    mWorld.update(TimePerFrame);


    CHECK( position.y > mWorld.getPlayer().getPosition().y );


}
//
TEST_CASE("Player Object Moves Down")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    auto position = mWorld.getPlayer().getPosition();
    auto RIGHT  = sf::Vector2f(0,1);
    mWorld.getPlayer().setVelocity(RIGHT);
    auto TimePerFrame = sf::seconds(1.f/60.f);
    mWorld.update(TimePerFrame);

    CHECK( position.y < mWorld.getPlayer().getPosition().y );


}

TEST_CASE("Player object collides with Wall")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Tile mTile{ mWorld.getTextures()};

    CHECK_FALSE( collision(mWorld.getPlayer() , mTile));
    mTile.setPosition(mWorld.getPlayer().getPosition());

    CHECK( collision(mWorld.getPlayer() , mTile));
}


TEST_CASE("Player collides with Door")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Door mDoor{mWorld.getTextures()};

    CHECK_FALSE( collision(mWorld.getPlayer() , mDoor));
    mDoor.setPosition(mWorld.getPlayer().getPosition());

    CHECK( collision(mWorld.getPlayer() , mDoor));
}

TEST_CASE("Player collides with Enemy")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    GameObject enemy{GameObject::Type::Blinky, mWorld.getTextures(), mWorld.getFonts()};

    CHECK_FALSE( collision(mWorld.getPlayer() , enemy));
    enemy.setPosition(mWorld.getPlayer().getPosition());

    CHECK( collision(mWorld.getPlayer() , enemy));
}






TEST_CASE("Player object collides with food")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Pickup mPallet{ mWorld.getTextures()};

    CHECK_FALSE( collision(mWorld.getPlayer() , mPallet));
    mPallet.setPosition(mWorld.getPlayer().getPosition());

    CHECK( collision(mWorld.getPlayer() , mPallet));
}

TEST_CASE("Player score increases when rewarded points")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    auto score = 25;
    mWorld.getPlayer().reward(score);

    CHECK( mWorld.getPlayer().getScore() > 0);
}

TEST_CASE("Player score is Equal to reward")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    auto score = 25;

    mWorld.getPlayer().reward(score);

    CHECK( mWorld.getPlayer().getScore() == score);
}



TEST_CASE("Player collides with Pickups")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Pickup mPallet{mWorld.getTextures()};

    CHECK_FALSE( collision(mWorld.getPlayer() , mPallet));
    mPallet.setPosition(mWorld.getPlayer().getPosition());

    CHECK( collision(mWorld.getPlayer() , mPallet));
}

TEST_CASE("Player is rewarded by Food Pickups")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Pickup mPallet{mWorld.getTextures()};

    CHECK( mWorld.getPlayer().getScore() == 0);
    mPallet.apply(mWorld.getPlayer(), Category::Food);
    CHECK( mWorld.getPlayer().getScore() > 0);

}


TEST_CASE("Player takes Damage")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    auto lives = mWorld.getPlayer().getHealth();
    CHECK(mWorld.getPlayer().getHealth() == lives);
    mWorld.getPlayer().damage();
    CHECK_FALSE(mWorld.getPlayer().getHealth() == lives);


}

TEST_CASE("Player can be killed")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    auto lives = mWorld.getPlayer().getHealth();

    mWorld.getPlayer().destroy();
    CHECK(mWorld.getPlayer().getHealth() == 0);
    CHECK(mWorld.getPlayer().isDestroyed());


}


//
TEST_CASE("Player Changes State when collided with Pallets")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Pickup mPallet{mWorld.getTextures(),Pickup::Type::Pallet};

    auto NormalPac = mWorld.getPlayer().getCategory() & GameObject::State::NormalPac;
    CHECK(NormalPac);
    mPallet.apply(mWorld.getPlayer(), Category::PowerPallet);
    auto SuperPac =  mWorld.getPlayer().getCategory() & GameObject::State::SuperPac;

   CHECK(SuperPac);
//
}

TEST_CASE("Player Changes State - GodPac")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };

    mWorld.getPlayer().setState(GameObject::State::GodPac);

    auto GodPac =  mWorld.getPlayer().getCategory() & GameObject::State::GodPac;

    CHECK(GodPac);

}

TEST_CASE("Enemy State Changes - Freightened State")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    GameObject enemy{GameObject::Type::Blinky, mWorld.getTextures(), mWorld.getFonts()};

    auto NormalGhost = enemy.getCategory() & GameObject::State::NormalGhost;
    CHECK(NormalGhost);

    enemy.setState(GameObject::State::ScaredGhost);
    auto ScaredGhost =  enemy.getCategory() & GameObject::State::ScaredGhost;

    CHECK(ScaredGhost);
//
}

TEST_CASE("Enemy State Changes - Flattened State")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    GameObject enemy{GameObject::Type::Blinky, mWorld.getTextures(), mWorld.getFonts()};

    auto NormalGhost = enemy.getCategory() & GameObject::State::NormalGhost;
    CHECK(NormalGhost);

    enemy.setState(GameObject::State::SquishedGhost);
    auto SquishedGhost =  enemy.getCategory() & GameObject::State::SquishedGhost;

    CHECK(SquishedGhost);
//
}

TEST_CASE("Correct Category is set")
{

    CHECK(Category::NormalPac == 1<<1);

}

TEST_CASE("Categories can be combined")
{
    auto combinedCategory = Category::NormalPac | Category::SuperPac;
    auto SubNormalPac = Category::SubNormalPac & combinedCategory;

    CHECK(SubNormalPac);

}

TEST_CASE("Categories can be combined")
{
    auto combinedCategory = Category::NormalPac | Category::SuperPac;
    auto SubNormalPac = Category::SubNormalPac & combinedCategory;

    CHECK(SubNormalPac);

}

TEST_CASE("Command Queue can be populated")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Command moveObject;
    CHECK(mWorld.getCommandQueue().isEmpty());
    mWorld.getCommandQueue().push(moveObject);

    CHECK_FALSE(mWorld.getCommandQueue().isEmpty());

}

TEST_CASE("Command Queue can be depopulated")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Command moveObject;
    CHECK(mWorld.getCommandQueue().isEmpty());
    mWorld.getCommandQueue().push(moveObject);

    CHECK_FALSE(mWorld.getCommandQueue().isEmpty());
    mWorld.getCommandQueue().pop();

    CHECK(mWorld.getCommandQueue().isEmpty());


}

TEST_CASE("Commands are dispatched")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};

    GameObject* mGhosty = nullptr;

    std::unique_ptr<GameObject> enemy(new GameObject(GameObject::Ghosty, mWorld.getTextures(), mWorld.getFonts()));
	mGhosty = enemy.get();
	mGhosty->setPosition(mMaze.playerSpawn());
    auto velocity = mGhosty->getVelocity();
    auto new_velocity = sf::Vector2f(-1,0);

    Component node;

    node.attachChild(std::move(enemy));



    struct GameObjectMover
    {
	    GameObjectMover(float vx, float vy)
	    : velocity(vx, vy)
	    {}

	    void operator() (GameObject& GameObject, sf::Time) const
	    {
		    GameObject.setVelocity(velocity * GameObject.getMaxSpeed());

	    }

	    sf::Vector2f velocity;
    };

    Command moveObject;
	moveObject.category = Category::EnemyGameObject;
	moveObject.action = derivedAction<GameObject>(GameObjectMover(new_velocity.x,  new_velocity.y));


    mWorld.getCommandQueue().push(moveObject);
    node.onCommand(moveObject, sf::Time::Zero);

    CHECK_FALSE(velocity == mGhosty->getVelocity());

}

TEST_CASE("Dispatched Commands are only received by the correct category")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};

    GameObject* mGhosty = nullptr;

    std::unique_ptr<GameObject> enemy(new GameObject(GameObject::Ghosty, mWorld.getTextures(), mWorld.getFonts()));
	mGhosty = enemy.get();
	mGhosty->setPosition(mMaze.enemySpawn());

    std::unique_ptr<GameObject> player(new GameObject(GameObject::Pacman, mWorld.getTextures(), mWorld.getFonts()));
	auto mPlayer = player.get();
	mPlayer->setPosition(mMaze.playerSpawn());



    auto ghost_velocity = mGhosty->getVelocity();
    auto player_velocity = mPlayer->getVelocity();

    auto new_velocity_ghost = sf::Vector2f(-1,0);

    Component node;

    node.attachChild(std::move(enemy));

//    auto player = mWorld.getPlayer().get();

    node.attachChild(std::move(player));



    struct GameObjectMover
    {
	    GameObjectMover(float vx, float vy)
	    : velocity(vx, vy)
	    {}

	    void operator() (GameObject& GameObject, sf::Time) const
	    {
		    GameObject.setVelocity(velocity * GameObject.getMaxSpeed());

	    }

	    sf::Vector2f velocity;
    };

    Command moveObject;
	moveObject.category = Category::EnemyGameObject;
	moveObject.action = derivedAction<GameObject>(GameObjectMover(ghost_velocity.x,  ghost_velocity.y));


    mWorld.getCommandQueue().push(moveObject);
    node.onCommand(moveObject, sf::Time::Zero);

    CHECK_FALSE(ghost_velocity == mGhosty->getVelocity());
    CHECK(player_velocity == mPlayer->getVelocity());

}

namespace
{
	    const std::vector<GameObjectData> Table = initializeGameObjectData();
}

TEST_CASE("Data Tables contain Data")
{


    CHECK_FALSE(Table.empty());
}


TEST_CASE("Correct Data can be retrieved From Table")
{
    CHECK(Table[GameObject::Pacman].Health == 3);
    CHECK(Table[GameObject::Pacman].speed == 400.f);
    CHECK(Table[GameObject::Pacman].texture == Textures::Pacman);


}

TEST_CASE("State Machine is Initially Empty")
{
    GameEngine mGameEngine;
    CHECK(mGameEngine.getStateMachine().isEmpty());


}

TEST_CASE("States can be added to State Machine")
{
    GameEngine mGameEngine;


    mGameEngine.getStateMachine().pushState(States::Splash);
    sf::Event event;
    mGameEngine.getStateMachine().handleEvent(event);


    CHECK_FALSE(mGameEngine.getStateMachine().isEmpty());



}


TEST_CASE("States can be removed from State Machine")
{
    GameEngine mGameEngine;


    mGameEngine.getStateMachine().pushState(States::Splash);
    sf::Event event;
    mGameEngine.getStateMachine().handleEvent(event);


    CHECK_FALSE(mGameEngine.getStateMachine().isEmpty());



    mGameEngine.getStateMachine().clearStates();

    mGameEngine.getStateMachine().handleEvent(event);


    CHECK(mGameEngine.getStateMachine().isEmpty());

}




//Enemy Tests
TEST_CASE("Enemy Moves Autonomously")
{
    GameEngine mGameEngine;

    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts() };
    Maze mMaze{ mWorld.getTextures()};
    GameObject* mGhosty = nullptr;

    std::unique_ptr<GameObject> enemy(new GameObject(GameObject::Ghosty, mWorld.getTextures(), mWorld.getFonts()));
	mGhosty = enemy.get();
	mGhosty->setPosition(mMaze.playerSpawn());




	auto velocity = mGhosty->getVelocity();

	CHECK(velocity != sf::Vector2f(0,0));

}
//
TEST_CASE("Current Position is not Equal Previous Position")
{
    GameEngine mGameEngine;
    World mWorld{ mGameEngine.getWindow() , mGameEngine.getFonts()};
    Maze mMaze{ mWorld.getTextures()};
    GameObject* mGhosty = nullptr;

    std::unique_ptr<GameObject> enemy(new GameObject(GameObject::Ghosty, mWorld.getTextures(), mWorld.getFonts()));
	mGhosty = enemy.get();
	mGhosty->setPosition(mMaze.playerSpawn());


    auto previous = mGhosty->getPreviousPosition();
    auto current = mGhosty->getPosition();

    CHECK(previous != current );

    mGhosty = nullptr;
}
