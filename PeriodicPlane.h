#include "GraphicalObject.h"

/// Namespace RayTracer
namespace rt {

  struct PeriodicPlane : public GraphicalObject 
  {
    /// Creates a periodic infinite plane passing through \a c and
    /// tangent to \a u and \a v. Then \a w defines the width of the
    /// band around (0,0) and its period to put material \a band_m,
    /// otherwise \a main_m is used.
    PeriodicPlane( Point3 c, Vector3 u, Vector3 v,
                  Material main_m, Material band_m, Real w) {
                    this->c = c;
                    this->u = u;
                    this->v = v;
                    this->main_m = main_m;
                    this->band_m = band_m;
                    this->w = w;
                  };

    void coordinates( Point3 p, Real& x, Real& y) {
      x = u[0] + p[0];
      y = u[0] + p[1];
    }

    void init( Viewer& /* viewer */ ) {}

    void draw( Viewer& /* viewer */ ) {
      glBegin( GL_TRIANGLES );
      glColor3f(0.5, 0, 0);
      glVertex3f(300.0, 210.0, 100.0);
      glVertex3f(340.0, 215.0, 270.0);
      glVertex3f(320.0, 290.0, 200.0);

      glEnd();

      glBegin( GL_TRIANGLES );
      glColor3f(0, 0.5, 0);
      glVertex3f(100.0, 180.0, 100.0);
      glVertex3f(140.0, 115.0, 200.0);
      glVertex3f(120.0, 190.0, 100.0);

      glEnd();
    }

    Vector3 getNormal( Point3 p ) {
      return p + u.cross( v );
    }

    Material getMaterial( Point3 p ) {
      return ((int) p[0] == (int) (p[0] + 0.1f)) || ((int) p[1] == (int) (p[1] + 0.1f)) ? band_m : main_m;
    }

    Real rayIntersection( const Ray& ray, Point3& p ) {
      Real wn = ray.direction.dot(u);
      Real tmp;

      if(wn == 0) {
        if(u.dot(p - ray.origin) == 0) {
          tmp = 0;
          return -1.0f;
        } else {
          return 1.0f;
        }
      } else {
        tmp = u.dot(p - ray.origin) / wn;
      }

      return tmp >= 0 ? -1.0f : 1.0f;
    }
  
  public:
    Point3 c;
    Vector3 u, v;
    Material band_m, main_m;
    Real w;
  };
}