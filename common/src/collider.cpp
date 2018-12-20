#include "collider.h"

/*!
 * \brief Collider::Collider
 * \param parent
 */
Collider::Collider(QObject *parent) : QObject(dynamic_cast<QObject*>(parent)) {  }

/*!
 * \brief Collider::collide
 * \param value
 * \param actor
 * \param tile_x
 * \param tile_y
 * \param tile_size
 */
void Collider::collide(int value, Actor *actor, int tile_x, int tile_y, int tile_size)
{
    switch(value) { // which value does our tile have?

          /* All 15 tile types can be described with only 4 collision methods. These
          methods are mixed and matched for each unique tile. */

          case  1: collide_top      (actor, tile_y            ); break;
          case  2: collide_right    (actor, tile_x + tile_size); break;
          case  3: if (collide_top  (actor, tile_y            )) return;// If there's a collision, we don't need to check for anything else.
                   collide_right    (actor, tile_x + tile_size); break;
          case  4: collide_bottom   (actor, tile_y + tile_size); break;
          case  5: if (collide_top  (actor, tile_y            )) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case  6: if (collide_right(actor, tile_x + tile_size)) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case  7: if (collide_top  (actor, tile_y            )) return;
                   if (collide_right(actor, tile_x + tile_size)) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case  8: collide_left     (actor, tile_x            ); break;
          case  9: if (collide_top  (actor, tile_y            )) return;
                   collide_left     (actor, tile_x            ); break;
          case 10: if (collide_left (actor, tile_x            )) return;
                   collide_right    (actor, tile_x + tile_size); break;
          case 11: if (collide_top  (actor, tile_y            )) return;
                   if (collide_left (actor, tile_x            )) return;
                   collide_right    (actor, tile_x + tile_size); break;
          case 12: if (collide_left (actor, tile_x            )) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case 13: if (collide_top  (actor, tile_y            )) return;
                   if (collide_left (actor, tile_x            )) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case 14: if (collide_left (actor, tile_x            )) return;
                   if (collide_right(actor, tile_x            )) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
          case 15: if (collide_top  (actor, tile_y            )) return;
                   if (collide_left (actor, tile_x            )) return;
                   if (collide_right(actor, tile_x + tile_size)) return;
                   collide_bottom   (actor, tile_y + tile_size); break;
    }

 }


/*!
 * \brief Collider::collidePlatformBottom
 * \param actor
 * \param tile_bottom
 * \return
 *
 *This will resolve a collision (if any) between an object and the y location of
 * some tile's bottom. All of these functions are pretty much the same, just adjusted
 * for different sides of a tile and different trajectories of the object.
 */
bool Collider::collide_bottom(Actor *actor, int tile_bottom)
{

/* If the top of the object is above the bottom of the tile and on the previous
    frame the top of the object was below the bottom of the tile, we have entered into
    this tile. Pretty simple stuff. */
    if (actor->get_top() < tile_bottom && actor->get_old_top() >= tile_bottom) {

      actor->set_top(tile_bottom);// Move the top of the actor->to the bottom of the tile.
      actor->velocity_y(0);     // Stop moving in that direction.
      return true;               // Return true because there was a collision.

    } return false;              // Return false if there was no collision.
}

/*!
 * \brief Collider::collidePlatformLeft
 * \param actor
 * \param tile_left
 * \return
 */
bool Collider::collide_left(Actor *actor, int tile_left)
{
    if (actor->get_right() > tile_left && actor->get_old_right() <= tile_left) {

          actor->set_right(tile_left - 0.01);// -0.01 is to fix a small problem with rounding
          actor->velocity_x(0);
          return true;

        } return false;

}

/*!
 * \brief Collider::collidePlatformRight
 * \param actor
 * \param tile_right
 * \return
 */
bool Collider::collide_right(Actor *actor, int tile_right)
{
    if (actor->get_left() < tile_right && actor->get_old_left() >= tile_right) {

          actor->set_left(tile_right);
          actor->velocity_x(0);
          return true;

        } return false;

}

/*!
 * \brief Collider::collidePlatformTop
 * \param actor
 * \param tile_top
 * \return
 */
bool Collider::collide_top(Actor *actor, int tile_top)
{
    if (actor->get_bottom() > tile_top && actor->get_old_bottom() <= tile_top) {

          actor->set_bottom(tile_top - 0.01);
          actor->velocity_y(0);
          actor->jumping(false);
          return true;

        } return false;

}
