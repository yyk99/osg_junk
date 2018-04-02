//
// yyk 2018
//

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Texture2D>
#include <osgUtil/ShaderGen>

#include <osgViewer/Viewer>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osg/Math>

// for the grid data..
#include "terrain_coords.h"

// Bezier stuff
typedef float number_t;
#include <vector>
//

osg::Geode* createTerrain()
{
    osg::Geode* geode = new osg::Geode();


    // ---------------------------------------
    // Set up a StateSet to texture the objects
    // ---------------------------------------
    osg::StateSet* stateset = new osg::StateSet();

    osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile("Images/lz.rgb");
    if (image)
    {
        osg::Texture2D* texture = new osg::Texture2D;
        texture->setImage(image);
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
        stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
    }

    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    geode->setStateSet(stateset);

#if 0
    float radius = 0.8f;
    float height = 1.0f;

    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5f);

    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2 * radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints));
#endif

    osg::HeightField* grid = new osg::HeightField;
    grid->allocate(38, 39);
    grid->setXInterval(0.28f);
    grid->setYInterval(0.28f);

    for (unsigned int r = 0; r < 39; ++r)
    {
        for (unsigned int c = 0; c < 38; ++c)
        {
            grid->setHeight(c, r, vertex[r + c * 39][2]);
        }
    }
    geode->addDrawable(new osg::ShapeDrawable(grid));

    return geode;
}

//%
//%
//%
//tx = ty = linspace(-8, 8, 41)';
//[xx, yy] = meshgrid(tx, ty);
//r = sqrt(xx . ^ 2 + yy . ^ 2) + eps;
//tz = sin(r) . / r;
//mesh(tx, ty, tz);
//xlabel("tx");
//ylabel("ty");
//zlabel("tz");
//title("3-D Sombrero plot");

osg::Geode *createSombreroHat()
{
    osg::Geode* geode = new osg::Geode();

    // ---------------------------------------
    // Set up a StateSet to texture the objects
    // ---------------------------------------
    osg::StateSet* stateset = new osg::StateSet();

    osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile("Images/lz.rgb");
    if (image)
    {
        osg::Texture2D* texture = new osg::Texture2D;
        texture->setImage(image);
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
        stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
    }

    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    geode->setStateSet(stateset);

    osg::HeightField* grid = new osg::HeightField;
    const int N = 41;

    grid->allocate(N, N);

    float dx = 16.0 / (N - 1);
    float dy = 16.0 / (N - 1);

    grid->setXInterval(dx);
    grid->setYInterval(dy);
    //grid->setOrigin(osg::Vec3f(-8, -8, 0));

    float eps = 2.22e-16;
    for (int r = 0; r < N; ++r) {
        float y = dy * (r - N/2);
        for (int c = 0; c < N; ++c) {
            float x = dx * (c - N/2);
            float R = sqrt(x *x  + y * y) + eps;
            float tz = 5 * sin(R) / R;
            grid->setHeight(c, r, tz);

//            std::cout << tz << " ";
        }
    }
//    std::cout << std::endl;
    geode->addDrawable(new osg::ShapeDrawable(grid));

    return geode;
}

#if 0
//
//
//
function plot3_b3()
P = zeros(2, 4, 3);
P(1, :, : ) = [0, 0, 0; 0, 0, 10; 100, 0, -35; 100, 0, 0];
P(2, :, : ) = [0, 0, 0; 0, 100, 150; 100, 100, 150; 100, 100, 0];
P(3, :, : ) = [0, 200, 0; 0, 200, 100; 100, 200, 100; 100, 200, 0];

%disp(P);

n = 50;
X = zeros(1, (n + 1)*(n + 1));
Y = zeros(size(X));
Z = zeros(size(X));

tic;
k = 0;
for i = 1:n + 1
u = 1.0 / n * (i - 1);
for j = 1:n + 1
k = k + 1;
v = 1.0 / n * (j - 1);
B = deCasteljau2(u, v, P);
X(k) = B(1);
Y(k) = B(2);
Z(k) = B(3);
endfor
endfor
toc;

[xx, yy] = meshgrid(linspace(0, 100, n + 1), linspace(0, 200, n + 1));
zz = griddata(X, Y, Z, xx, yy);

%plot3(X, Y, Z, 'o');
mesh(xx, yy, zz);
xlabel("X");
ylabel("Y");
zlabel("Z");
title("3-D plot");


endfunction

#endif


//#
//# u - scalar
//# P - (n, m, 3) is an (n X m) matrix of 3D-points
//#
//function S = deCasteljau2(u0, v0, P)
//  if nargin < 3
//    error("usage: deCasteljau2(u0, v0, P)");
//  endif
//
//  n = size(P, 2);
//  m = size(P, 1);
//  
//  if (n <= m)
//    Q = zeros(m, 3);
//    for j = 1:m
//      Q(j,:) = deCasteljau1(u0, squeeze(P(j,:,:)));
//    endfor
//    S = deCasteljau1(v0, Q);
//  else
//    Q = zeros(n, 3);
//    for i = 1:n
//      Q(i, :) = deCasteljau1(v0, squeeze(P(:,i,:)));
//    endfor
//    S = deCasteljau1(u0, Q);
//  endif
//endfunction

//#
//# u - scalar
//# P - (n, 3) vector of points 3D
//#
//function B = deCasteljau1(u, P)
//  if nargin < 2
//    error("usage: deCasteljau1(u, P)");
//  endif
//
//  n = size(P, 1);
//  Q = P;
//  
//  for k = 1:n-1
//    for i = 1:n-k
//      Q(i,:) = (1.0 - u)*Q(i,:) + u * Q(i+1,:);
//    endfor
//  endfor
//  
//  B = Q(1,:);
//endfunction

#include <cassert>

void deCasteljau1(std::vector<number_t> const &P, size_t n, number_t u, number_t &C)
{
    assert(P.size() == n + 1);
    std::vector<number_t> Q(P); // Use local array so we do not 
                                // destroy control points
    for (size_t k = 1; k <= n; k++) {
        for (size_t i = 0; i <= n - k; i++) {
            Q[i] = (1.0 - u)*Q[i] + u * Q[i + 1];
        }
    }

    C = Q[0];
}

//
osg::Geode *plot3_b3()
{
#if 0
    P = zeros(2, 4, 3);
    P(1, :, : ) = [0, 0, 0; 0, 0, 10; 100, 0, -35; 100, 0, 0];
    P(2, :, : ) = [0, 0, 0; 0, 100, 150; 100, 100, 150; 100, 100, 0];
    P(3, :, : ) = [0, 200, 0; 0, 200, 100; 100, 200, 100; 100, 200, 0];

    %disp(P);

    n = 50;
    X = zeros(1, (n + 1)*(n + 1));
    Y = zeros(size(X));
    Z = zeros(size(X));

    tic;
    k = 0;
    for i = 1:n + 1
        u = 1.0 / n * (i - 1);
    for j = 1:n + 1
        k = k + 1;
    v = 1.0 / n * (j - 1);
    B = deCasteljau2(u, v, P);
    X(k) = B(1);
    Y(k) = B(2);
    Z(k) = B(3);
    endfor
        endfor
        toc;

    [xx, yy] = meshgrid(linspace(0, 100, n + 1), linspace(0, 200, n + 1));
    zz = griddata(X, Y, Z, xx, yy);

    %plot3(X, Y, Z, 'o');
    mesh(xx, yy, zz);
    xlabel("X");
    ylabel("Y");
    zlabel("Z");
    title("3-D plot");
#endif
    return 0;
}



int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // add model to viewer.
    viewer.setSceneData(createSombreroHat());

    return viewer.run();
}
