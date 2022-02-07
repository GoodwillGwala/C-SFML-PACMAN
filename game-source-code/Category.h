/**
∗ @namespace <Category>
∗ @brief This class facilitates identifying categories of Game Objects.
*
* The categories are based on the type of object or the state it is in
* This allows combining different objects to ease communication to objects of different types and states.
*/
#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
        /**
        ∗ @brief  enum for identifying different Categories of the Game Objects.
        *
        *
        * The categories are instantiated using a 16 bit binary presentation
        * i.e 1 << 0 = 0000 ,  1 << 1 = 0010 etc
        * This representation allows categories to be combined instead of creating new objects.
        * This facilitates communication to a group of objects.
        */
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,

		NormalPac           = 1 << 1,

		SuperPac            = 1 << 2,
        GodPac              = 1 << 3,


		NormalGhost         = 1 << 4,

		ScaredGhost         = 1 << 5,
        SquishedGhost       = 1 << 6,


		Food                = 1 << 7,
        PowerPallet         = 1 << 8,
        SuperPallet         = 1 << 9,

        Wall                = 1 << 10,
		Door                = 1 << 11,
        Key                 = 1 << 12,





//      combining different categories


 		SubNormalPac     = NormalPac | SuperPac ,

 		SuperNormalPac   = SuperPac ^ GodPac,
 		SuperNormalEnemy = ScaredGhost ^ SquishedGhost,

        EnemyGameObject  = NormalGhost | ScaredGhost| SquishedGhost |  SuperNormalEnemy,
 		PlayerGameObject = SuperPac | NormalPac | GodPac | SuperNormalPac,

 		GameObject       = PlayerGameObject | EnemyGameObject,

        Pickup           = Food | PowerPallet | SuperPallet,

		Tile             = Wall | Door,
	};
}

#endif
