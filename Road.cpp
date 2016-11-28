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

#include "Road.h"
#include "io.h"

float Road::_heightref = 0.5;

Road::Road(char *wkt, std::unordered_map<std::string, std::string> attributes, std::string pid, float heightref)
  : Boundary3D(wkt, attributes, pid) {
  _heightref = heightref;
}

TopoClass Road::get_class() {
  return ROAD;
}

bool Road::is_hard() {
  return true;
}

std::string Road::get_mtl() {
  return "usemtl Road\n";
}

bool Road::add_elevation_point(Point2 p, double z, float radius, LAS14Class lasclass, bool lastreturn) {
  if (lastreturn == true && lasclass == LAS_GROUND) {
    Boundary3D::add_elevation_point(p, z, radius, lasclass, lastreturn);
  }
  return true;
}

bool Road::lift() {
  lift_each_boundary_vertices(_heightref);
  smooth_boundary(5);
  return true;
}

std::string Road::get_citygml() {
  std::stringstream ss;
  ss << "<cityObjectMember>" << std::endl;
  ss << "<tran:Road gml:id=\"" << this->get_id() << "\">" << std::endl;
  ss << "<tran:lod1MultiSurface>" << std::endl;
  ss << "<gml:MultiSurface>" << std::endl;
  ss << std::setprecision(3) << std::fixed;
  for (auto& t : _triangles)
    ss << get_triangle_as_gml_surfacemember(t);
  for (auto& t : _triangles_vw)
    ss << get_triangle_as_gml_surfacemember(t, true);
  ss << "</gml:MultiSurface>" << std::endl;
  ss << "</tran:lod1MultiSurface>" << std::endl;
  ss << "</tran:Road>" << std::endl;
  ss << "</cityObjectMember>" << std::endl;
  return ss.str();
}

std::string Road::get_citygml_imgeo() {
  std::stringstream ss;
  ss << "<cityObjectMember>" << std::endl;
  ss << "<tra:TrafficArea gml:id=\"" << this->get_id() << "\">" << std::endl;
  ss << get_imgeo_object_info(this->get_id());
  ss << "<tra:lod2MultiSurface>" << std::endl;
  ss << "<gml:MultiSurface>" << std::endl;
  ss << std::setprecision(3) << std::fixed;
  for (auto& t : _triangles)
    ss << get_triangle_as_gml_surfacemember(t);
  for (auto& t : _triangles_vw)
    ss << get_triangle_as_gml_surfacemember(t, true);
  ss << "</gml:MultiSurface>" << std::endl;
  ss << "</tra:lod2MultiSurface>" << std::endl;
  std::string attribute;
  //if (get_attribute("bgt_functie", attribute)) {
  //  ss << "<imgeo:bgt-functie codeSpace=\"http://www.geostandaarden.nl/imgeo/def/2.1#FunctieWeg\">" << attribute << "</imgeo:bgt-functie>" << std::endl;
  //}
  //if (get_attribute("bgt_fysiekvoorkomen", attribute)) {
  //  ss << "<imgeo:bgt-fysiekVoorkomen codeSpace=\"http://www.geostandaarden.nl/imgeo/def/2.1#FysiekVoorkomenWeg\">" << attribute << "</imgeo:bgt-fysiekVoorkomen>" << std::endl;
  //}
  if (get_attribute("wegdeeloptalud", attribute)) {
    ss << "<imgeo:wegdeelOpTalud>" << attribute << "</imgeo:wegdeelOpTalud>" << std::endl;
  }
  if (get_attribute("plus_functiewegdeel", attribute)) {
    ss << "<imgeo:plus-functieWegdeel codeSpace=\"http://www.geostandaarden.nl/imgeo/def/2.1#FunctieWegPlus\">" << attribute << "</imgeo:plus-functieWegdeel>" << std::endl;
  }
  if (get_attribute("plus_fysiekvoorkomenwegdeel", attribute)) {
    ss << "<imgeo:plus-fysiekVoorkomenWegdeel codeSpace=\"http://www.geostandaarden.nl/imgeo/def/2.1#FysiekVoorkomenWegPlus\">" << attribute << "</imgeo:plus-fysiekVoorkomenWegdeel>" << std::endl;
  }
  ss << "</tra:TrafficArea>" << std::endl;
  ss << "</cityObjectMember>" << std::endl;
  return ss.str();
}

bool Road::get_shape(OGRLayer* layer) {
  return TopoFeature::get_shape_features(layer, "Road");
}
