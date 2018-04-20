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
      glVertex3f(-1000.0, -1000.0, 0.0);
      glVertex3f(-1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, -1000.0, 0.0);

      glEnd();

      glBegin( GL_TRIANGLES );
      glColor3f(0, 0.5, 0);
      glVertex3f(-1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, -1000.0, 0.0);

      glEnd();
    }

    Vector3 getNormal( Point3 p ) {
      return p + u.cross( v );
    }

    Material getMaterial( Point3 p ) {
      Real px, py;
      coordinates(p, px, py);
      
      return ((int) px == (int) (px + w)) || ((int) py == (int) (py + w)) ? main_m : band_m;
    }

    Real rayIntersection( const Ray& ray, Point3& p ) {
      Vector3 n = getNormal(c) / getNormal(c).norm();
      Vector3 w = ray.direction / ray.direction.norm();
      Real wn = w.dot(n);
      Real tmp;

      if(wn > 0.0000001f) {
        Vector3 n0w0 = (c - ray.origin) / (c - ray.origin).norm();
        tmp = n.dot(n0w0) / wn;

        p = ray.origin + w * tmp;
        
        return tmp >= 0 ? -1.0f : 1.0f;
      } 
      
      return 1.0f;
    }
  
  public:
    Point3 c;
    Vector3 u, v;
    Material band_m, main_m;
    Real w;
  };
}