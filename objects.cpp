#include "objects.h"
#include "world.h"
#include "textures.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

void Object::set_px(float px) {
  this->px = px;
}

void Object::set_py(float py) {
  this->py = py;
}

void Object::set_pz(float pz) {
  this->pz = pz;
}

void Object::set_sx(float sx) {
  this->sx = sx;
}

void Object::set_sy(float sy) {
  this->sy = sy;
}

void Object::set_sz(float sz) {
  this->sz = sz;
}

void Object::set_angle(float angle) {
  this->angle = angle;
}

float Object::get_px() {
  return px;
}

float Object::get_py() {
  return py;
}

float Object::get_pz() {
  return pz;
}

float Object::get_sx() {
  return sx;
}

float Object::get_sy() {
  return sy;
}

float Object::get_sz() {
  return sz;
}

float Object::get_angle() {
  return angle;
}

void Ground::render(Camera &c) {
  glLoadIdentity();
  c.setup();
  glBindTexture(GL_TEXTURE_2D, textures[t_ground]);
  glBegin(GL_QUADS); {
    glTexCoord2f(0.0, 0.0); glVertex3f(400, -400, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-400, -400, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-400, 400, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(400, 400, 0);
  } glEnd();
}

void Walls::render(Camera &c) {
  glLoadIdentity();
  c.setup();
  glBindTexture(GL_TEXTURE_2D, textures[t_wall]);
  glBegin(GL_QUADS); {
    // left
    glTexCoord2f(0.0,  0.0);  glVertex3f(-400, -400, 0);
    glTexCoord2f(20.0, 0.0);  glVertex3f(-400,  400, 0);
    glTexCoord2f(20.0, 1.0); glVertex3f(-400,  400, 8);
    glTexCoord2f(0.0,  1.0); glVertex3f(-400, -400, 8);
    // right
    glTexCoord2f(0.0,  0.0);  glVertex3f(400,  400, 0);
    glTexCoord2f(20.0, 0.0);  glVertex3f(400, -400, 0);
    glTexCoord2f(20.0, 1.0); glVertex3f(400, -400, 8);
    glTexCoord2f(0.0,  1.0); glVertex3f(400,  400, 8);
    // front
    glTexCoord2f(0.0,  0.0);  glVertex3f(400,  -400, 0);
    glTexCoord2f(20.0, 0.0);  glVertex3f(-400, -400, 0);
    glTexCoord2f(20.0, 1.0); glVertex3f(-400, -400, 8);
    glTexCoord2f(0.0,  1.0); glVertex3f(400,  -400, 8);
    // back
    glTexCoord2f(0.0,  0.0);  glVertex3f(-400, 400, 0);
    glTexCoord2f(20.0, 0.0);  glVertex3f(400,  400, 0);
    glTexCoord2f(20.0, 1.0); glVertex3f(400,  400, 8);
    glTexCoord2f(0.0,  1.0); glVertex3f(-400, 400, 8);
  } glEnd();
}

Box::Box() {
  px = py = pz = 0;
  sx = sy = 30;
  sz = 9.42;
  angle = 0;
}

Box::Box(const Box &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
}

Box Box::operator = (const Box &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
  return *this;
}

void Box::render(Camera &c, bool transparent) {
  glLoadIdentity();
  c.setup();
  glTranslatef(px, py, pz);
  glRotatef(angle, 0, 0, 1);
  glBindTexture(GL_TEXTURE_2D, textures[t_boxwall]);
  if(transparent) {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glColor4f(1.0, 1.0, 1.0, 0.20);
  }
  glBegin(GL_QUADS); {
    // left
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, -sy, 0);
    glTexCoord2f(sy / 4, 0.0); glVertex3f(-sx, sy, 0);
    glTexCoord2f(sy / 4, sz / 4); glVertex3f(-sx, sy, sz);
    glTexCoord2f(0.0, sz / 4); glVertex3f(-sx, -sy, sz);
    // right
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, sy, 0);
    glTexCoord2f(sy / 4, 0.0); glVertex3f(sx, -sy, 0);
    glTexCoord2f(sy / 4, sz / 4); glVertex3f(sx, -sy, sz);
    glTexCoord2f(0.0, sz / 4); glVertex3f(sx, sy, sz);
    // front
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, -sy, 0);
    glTexCoord2f(sy / 4, 0.0); glVertex3f(-sx, -sy, 0);
    glTexCoord2f(sy / 4, sz / 4); glVertex3f(-sx, -sy, sz);
    glTexCoord2f(0.0, sz / 4); glVertex3f(sx, -sy, sz);
    // back
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, sy, 0);
    glTexCoord2f(sy / 4, 0.0); glVertex3f(sx, sy, 0);
    glTexCoord2f(sy / 4, sz / 4); glVertex3f(sx, sy, sz);
    glTexCoord2f(0.0, sz / 4); glVertex3f(-sx, sy, sz);
  } glEnd();
  glBindTexture(GL_TEXTURE_2D, textures[t_roof]);
  glBegin(GL_QUADS); {
    // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, -sy, 0);
    glTexCoord2f(sy / 16, 0.0); glVertex3f(-sx, sy, 0);
    glTexCoord2f(sy / 16, sx / 16); glVertex3f(sx, sy, 0);
    glTexCoord2f(0.0, sx / 16); glVertex3f(sx, -sy, 0);
    // top
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, -sy, sz);
    glTexCoord2f(sy / 16, 0.0); glVertex3f(-sx, sy, sz);
    glTexCoord2f(sy / 16, sx / 16); glVertex3f(sx, sy, sz);
    glTexCoord2f(0.0, sx / 16); glVertex3f(sx, -sy, sz);
  } glEnd();
  if(transparent) {
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glColor4f(1.0, 1.0, 1.0, 1.0);
  }
}

ostream & operator << (ostream &dest, Box &src) {
  dest << "box" << endl;
  dest << "position " << src.px << ' ' << src.py << ' ' << src.pz << endl;
  dest << "rotation " << (src.angle / 180.0 * M_PI) << endl;
  dest << "size " << src.sx << ' ' << src.sy << ' ' << src.sz << endl;
  dest << "end" << endl;
  dest << endl;
  return dest;
}

Pyramid::Pyramid() {
  px = py = pz = 0;
  sx = sy = 8.2;
  sz = 10.25;
  angle = 0;
}

Pyramid::Pyramid(const Pyramid &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
}

Pyramid Pyramid::operator = (const Pyramid &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
  return *this;
}

void Pyramid::render(Camera &c, bool transparent) {
  glLoadIdentity();
  c.setup();
  glTranslatef(px, py, pz);
  glRotatef(angle, 0, 0, 1);
  glBindTexture(GL_TEXTURE_2D, textures[t_pyrwall]);
  if(transparent) {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glColor4f(1.0, 1.0, 1.0, 0.20);
  }
  glBegin(GL_TRIANGLES); {
    // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, -sy, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-sx,  sy, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(sx,   sy, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(sx,   sy, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(sx,  -sy, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-sx, -sy, 0);
    // left
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, sy,  0);
    glTexCoord2f(0.5, 1.0); glVertex3f(0,   0,   sz);
    glTexCoord2f(1.0, 0.0); glVertex3f(-sx, -sy, 0);
    // right
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, sy,  0);
    glTexCoord2f(0.5, 1.0); glVertex3f(0,  0,   sz);
    glTexCoord2f(1.0, 0.0); glVertex3f(sx, -sy, 0);
    // front
    glTexCoord2f(0.0, 0.0); glVertex3f(sx,  -sy, 0);
    glTexCoord2f(0.5, 1.0); glVertex3f(0,   0,   sz);
    glTexCoord2f(1.0, 0.0); glVertex3f(-sx, -sy, 0);
    // back
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, sy, 0);
    glTexCoord2f(0.5, 1.0); glVertex3f(0,   0,  sz);
    glTexCoord2f(1.0, 0.0); glVertex3f(sx,  sy, 0);
  } glEnd();
  if(transparent) {
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glColor4f(1.0, 1.0, 1.0, 1.0);
  }
}

ostream & operator << (ostream &dest, Pyramid &src) {
  dest << "pyramid" << endl;
  dest << "position " << src.px << ' ' << src.py << ' ' << src.pz << endl;
  dest << "rotation " << (src.angle / 180.0 * M_PI) << endl;
  dest << "size " << src.sx << ' ' << src.sy << ' ' << src.sz << endl;
  dest << "end" << endl;
  dest << endl;
  return dest;
}

Teleporter::Teleporter() {
  px = py = pz = 0;
  sx = 4.48;
  sy = 0;
  sz = 20.16;
  angle = 0;
  border = 1;
}

Teleporter::Teleporter(const Teleporter &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
  this->border = r.border;
}

Teleporter Teleporter::operator = (const Teleporter &r) {
  this->px = r.px;
  this->py = r.py;
  this->pz = r.pz;
  this->sx = r.sx;
  this->sy = r.sy;
  this->sz = r.sz;
  this->angle = r.angle;
  this->border = r.border;
  return *this;
}

void Teleporter::render(Camera &c, bool transparent) {
  glLoadIdentity();
  c.setup();
  glTranslatef(px, py, pz);
  glRotatef(angle, 0, 0, 1);
  glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);
  glColor3f(0.25, 0.25, 0.25);
  if(transparent) {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glColor4f(0.25, 0.25, 0.25, 0.20);
  }
  glBegin(GL_QUADS); {
    glVertex3f(sx, 0, 0); glVertex3f(-sx, 0, 0); glVertex3f(-sx, 0, sz); glVertex3f(sx, 0, sz);
  } glEnd();
  glColor3f(1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_COLOR_MATERIAL);
  if(transparent) {
    glColor4f(1.0, 1.0, 1.0, 0.20);
  }
  glBindTexture(GL_TEXTURE_2D, textures[t_caution]);
  glBegin(GL_QUADS); {
    ///// first box /////
    // left
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(-sx - border, border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(-sx - border, -border / 2, sz);
    // right
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(-sx, -border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(-sx, -border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(-sx, border / 2, sz);
    // front
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, -border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(-sx - border, -border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(-sx, -border / 2, sz);
    // back
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(-sx, border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(-sx, border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(-sx - border, border / 2, sz);
    // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, border / 2, 0);
    glTexCoord2f(border, border); glVertex3f(-sx, border / 2, 0);
    glTexCoord2f(0.0, border); glVertex3f(-sx, -border / 2, 0);
    ///// second box /////
    // left
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(sx, border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(sx, border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(sx, -border / 2, sz);
    // right
    glTexCoord2f(0.0, 0.0); glVertex3f(sx + border, border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(sx + border, -border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(sx + border, -border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(sx + border, border / 2, sz);
    // front
    glTexCoord2f(0.0, 0.0); glVertex3f(sx + border, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(sx, -border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(sx, -border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(sx + border, -border / 2, sz);
    // back
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(sx + border, border / 2, 0);
    glTexCoord2f(border, sz); glVertex3f(sx + border, border / 2, sz);
    glTexCoord2f(0.0, sz); glVertex3f(sx, border / 2, sz);
    // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(sx, -border / 2, 0);
    glTexCoord2f(border, 0.0); glVertex3f(sx, border / 2, 0);
    glTexCoord2f(border, border); glVertex3f(sx, border / 2, sz);
    glTexCoord2f(0.0, border); glVertex3f(sx, -border / 2, sz);
    ///// third box /////
    // left
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, -border / 2, sz);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, border / 2, sz);
    glTexCoord2f(border, border); glVertex3f(-sx - border, border / 2, sz + border);
    glTexCoord2f(0.0, border); glVertex3f(-sx - border, -border / 2, sz + border);
    // right
    glTexCoord2f(0.0, 0.0); glVertex3f(sx + border, border / 2, sz);
    glTexCoord2f(border, 0.0); glVertex3f(sx + border, -border / 2, sz);
    glTexCoord2f(border, border); glVertex3f(sx + border, -border / 2, sz + border);
    glTexCoord2f(0.0, border); glVertex3f(sx + border, border / 2, sz + border);
    // front
    glTexCoord2f(0.0, 0.0); glVertex3f(sx + border, -border / 2, sz);
    glTexCoord2f(sx + border * 2, 0.0); glVertex3f(-sx - border, -border / 2, sz);
    glTexCoord2f(sx + border * 2, border); glVertex3f(-sx - border, -border / 2, sz + border);
    glTexCoord2f(0.0, border); glVertex3f(sx + border, -border / 2, sz + border);
    // back
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, border / 2, sz);
    glTexCoord2f(sx + border * 2, 0.0); glVertex3f(sx + border, border / 2, sz);
    glTexCoord2f(sx + border * 2, border); glVertex3f(sx + border, border / 2, sz + border);
    glTexCoord2f(0.0, border); glVertex3f(-sx - border, border / 2, sz + border);
    // top
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, -border / 2, sz + border);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, border / 2, sz + border);
    glTexCoord2f(border, sx); glVertex3f(sx + border, border / 2, sz + border);
    glTexCoord2f(0.0, sx); glVertex3f(sx + border, -border / 2, sz + border);
    // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(-sx - border, -border / 2, sz);
    glTexCoord2f(border, 0.0); glVertex3f(-sx - border, border / 2, sz);
    glTexCoord2f(border, sx); glVertex3f(sx + border, border / 2, sz);
    glTexCoord2f(0.0, sx); glVertex3f(sx + border, -border / 2, sz);
  } glEnd();
  if(transparent) {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, 1.0);
  }
}

void Teleporter::set_border(float border) {
  this->border = border;
}

float Teleporter::get_border() {
  return border;
}

ostream & operator << (ostream &dest, Teleporter &src) {
  dest << "teleporter" << endl;
  dest << "position " << src.px << ' ' << src.py << ' ' << src.pz << endl;
  dest << "rotation " << (((src.angle / 180.0) - 90) * M_PI) << endl;
  dest << "size " << src.sy << ' ' << src.sx << ' ' << src.sz << endl;
  dest << "border " << src.border << endl;
  dest << "end" << endl;
  dest << endl;
  return dest;
}

Base::Base() : Object() {
  color = 1;
}

Base::Base(const Base &b) {
  this->px = b.px;
  this->py = b.py;
  this->pz = b.pz;
  this->color = b.color;
  this->sx = b.sx;
  this->sy = b.sy;
  this->sz = b.sz;
  this->color = b.color;
}

Base Base::operator = (const Base &b) {
  this->px = b.px;
  this->py = b.py;
  this->pz = b.pz;
  this->color = b.color;
  this->sx = b.sx;
  this->sy = b.sy;
  this->sz = b.sz;
  this->color = b.color;
  return *this;
}

void Base::render(Camera &c, bool transparent) {
  glLoadIdentity();
  c.setup();
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  switch(color) {
    case 1:
      glColor3f(1.0, 0.0, 0.0);
      break;
    case 2:
      glColor3f(0.0, 1.0, 0.0);
      break;
    case 3:
      glColor3f(0.0, 0.0, 1.0);
      break;
    case 4:
      glColor3f(1.0, 0.0, 1.0);
      break;
  }
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(px, py, pz);
  glRotatef(angle, 0, 0, 1);
  glBegin(GL_QUADS); {
    glVertex3f(-sx, -sy, 0);
    glVertex3f(-sx, sy, 0);
    glVertex3f(sx, sy, 0);
    glVertex3f(sx, -sy, 0);
  } glEnd();
  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
}

void Base::set_color(int color) {
  this->color = color;
}

int Base::get_color() {
  return color;
}

ostream & operator << (ostream &dest, Base &src) {
  dest << "base\n";
  dest << "position " << src.get_px() << ' ' << src.get_py() << ' ' << src.get_pz() << endl;
  dest << "rotation " << src.get_angle() << endl;
  dest << "size " << src.get_sx() << ' ' << src.get_sy() << ' ' << src.get_sz() << endl;
  dest << "color " << src.get_color() << endl;
  dest << "end\n\n";
  return dest;
}

Link::Link() {
  from = "";
  from_side = 0;
  to = "";
  to_side = 0;
}

Link::Link(const Link &r) {
  from = r.from;
  to = r.to;
}

Link Link::operator = (const Link &r) {
  from = r.from;
  to = r.to;
  return *this;
}

void Link::render(Camera &c, World *w) {
  if(from == "" || to == "") {
    return;
  }
  Element fromE = w->getElementByName(from);
  Element toE = w->getElementByName(to);
  if(fromE.type == Element::NONE || toE.type == Element::NONE)
    return;
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);

  // in
  glLoadIdentity();
  c.setup();
  glTranslatef(fromE.get_px(), fromE.get_py(), fromE.get_pz());
  glRotatef(fromE.get_angle(), 0, 0, 1);
  if(from_side == 1)
    glRotatef(180, 0, 0, 1);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_TRIANGLES); {
    // arrow head
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -8, fromE.get_sz() / 2);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -4, fromE.get_sz() / 2 + 2);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -4, fromE.get_sz() / 2 - 2);
    // arrow tail
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -4, fromE.get_sz() / 2 - 1);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -4, fromE.get_sz() / 2 + 1);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, 0,  fromE.get_sz() / 2 + 1);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, 0,  fromE.get_sz() / 2 + 1);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, 0,  fromE.get_sz() / 2 - 1);
    glVertex3f(-fromE.get_sx() / 2 - 0.1, -4, fromE.get_sz() / 2 - 1);
  } glEnd();

  // out
  glLoadIdentity();
  c.setup();
  glTranslatef(toE.get_px(), toE.get_py(), toE.get_pz());
  glRotatef(toE.get_angle(), 0, 0, 1);
  if(to_side == 1)
    glRotatef(180, 0, 0, 1);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES); {
    // arrow head
    glVertex3f(-toE.get_sx() / 2 - 0.1, -8, toE.get_sz() / 2);
    glVertex3f(-toE.get_sx() / 2 - 0.1, -4, toE.get_sz() / 2 + 2);
    glVertex3f(-toE.get_sx() / 2 - 0.1, -4, toE.get_sz() / 2 - 2);
    // arrow tail
    glVertex3f(-toE.get_sx() / 2 - 0.1, -4, toE.get_sz() / 2 - 1);
    glVertex3f(-toE.get_sx() / 2 - 0.1, -4, toE.get_sz() / 2 + 1);
    glVertex3f(-toE.get_sx() / 2 - 0.1, 0,  toE.get_sz() / 2 + 1);
    glVertex3f(-toE.get_sx() / 2 - 0.1, 0,  toE.get_sz() / 2 + 1);
    glVertex3f(-toE.get_sx() / 2 - 0.1, 0,  toE.get_sz() / 2 - 1);
    glVertex3f(-toE.get_sx() / 2 - 0.1, -4, toE.get_sz() / 2 - 1);
  } glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
}

void Link::set_from(string from) {
  this->from = from;
}

void Link::set_from_side(int from_side) {
  this->from_side = from_side;
}

void Link::set_to(string to) {
  this->to = to;
}

void Link::set_to_side(int to_side) {
  this->to_side = to_side;
}

string Link::get_from() {
  return from;
}

int Link::get_from_side() {
  return from_side;
}

string Link::get_to() {
  return to;
}

int Link::get_to_side() {
  return to_side;
}