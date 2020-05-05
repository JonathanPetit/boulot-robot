#include <algorithm>
#include "obstacle_rectangle.hpp"

namespace pathplanning::map {

    RectangleObstacle::RectangleObstacle(const geometry::Point& corner, const geometry::Point& opposite_corner):
        geometry::StraightRectangle(corner, opposite_corner) {}

    SurfaceRelationship RectangleObstacle::get_relation_with_zone(const geometry::StraightRectangle& rectangle) const {
        if (contains(rectangle)) {
            return SurfaceRelationship::CONTAINS;
        }  else if (contained(rectangle)) {
            return SurfaceRelationship::CONTAINED;
        } else if (overlap(rectangle)) {
            return SurfaceRelationship::OVERLAP;
        }
        return SurfaceRelationship::DISJOINT;
    }

    bool RectangleObstacle::contains(const geometry::StraightRectangle& rectangle) const {
        if (get_left_line() < rectangle.get_left_line() && get_right_line() > rectangle.get_right_line() &&
                get_bottom_line() < rectangle.get_bottom_line() && get_top_line() > rectangle.get_top_line()) {
            return true;
        }
        return false;
    }

    bool RectangleObstacle::contained(const geometry::StraightRectangle& rectangle) const {
        if (rectangle.get_left_line() < get_left_line() && rectangle.get_right_line() > get_right_line() && 
            rectangle.get_bottom_line() < get_bottom_line() && rectangle.get_top_line() > get_top_line()) {
                return true;
        }
        return false;
    }

    bool RectangleObstacle::overlap(const geometry::StraightRectangle& rectangle) const {
        if (get_right_line() < rectangle.get_left_line() || get_left_line() > rectangle.get_right_line()) {
            // If x coordinates don't cross, it's impossible to have an overlap
            return false;
        }
        if (get_top_line() < rectangle.get_bottom_line() || get_bottom_line() > rectangle.get_top_line()) {
            // If y coordinates don't cross, it's impossible to have an overlap
            return false;
        }
        return true;
    }
}
