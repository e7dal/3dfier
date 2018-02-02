/*
  3dfier: takes 2D GIS datasets and "3dfies" to create 3D city models.

  Copyright (C) 2015-2016  3D geoinformation research group, TU Delft

  This file is part of 3dfier.

  3dfier is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  3dfier is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with 3difer.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of 3dfier, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#ifndef Bridge_h
#define Bridge_h

#include "TopoFeature.h"

class Bridge: public Flat {
public:
  Bridge(char *wkt, std::string layername, AttributeMap attributes, std::string pid, float heightref);

  bool          lift();
  bool          add_elevation_point(Point2 &p, double z, float radius, LAS14Class lasclass, bool lastreturn);
<<<<<<< HEAD:src/Bridge.h
  void          get_citygml(std::ostream& of);
  void          get_citygml_imgeo(std::ostream& of);
=======
  void          get_citygml(std::ofstream& of);
  void          get_cityjson(nlohmann::json& j, std::unordered_map<std::string,unsigned long> &dPts);
  void          get_citygml_imgeo(std::ofstream& of);
>>>>>>> origin/cityjson-output:Bridge.h
  std::string   get_mtl();
  bool          get_shape(OGRLayer* layer, bool writeAttributes, AttributeMap extraAttributes = AttributeMap());
  TopoClass     get_class();
  bool          is_hard();
  static float  _heightref;
};

#endif /* Bridge_h */
