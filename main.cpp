#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <stdlib.h>
#include<bits/stdc++.h>
#include <BmpLoader.h>

using namespace std;
double odx=0,odx_limit=0,odz=0;
double leftsdx=0,rightsdx=0;
double windowHeight=960, windowWidth=540;
GLfloat alpha = 0.0, theta = 0.0, gamma = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0,theta2=0;
GLboolean bRotate = false, uRotate = false, fanRotate=false,light_0_on = true, light_1_on = true;
GLboolean amb_light_0 = true, dif_light_0 = true, spec_light_0 = true,amb_light_1 = true, dif_light_1 = true, spec_light_1 = true;


unsigned int ID;
double eyex = 65;
double eyey = 50;
double eyez = 825;
double centerx = eyex;
double centery = eyey;
double centerz = 0;
double upx = 0;
double upy = 1;
double upz = 0;
double limit = 360;
double def_value = 1;
GLfloat angleYaw = 90.0, anglePitch = 0.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 90.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = -90.0, angleRollLimit2 = -90.0;
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;
double near_id=17, far_id = 20000000;


static void resize(int width, int height)
{
    const float ar = (float) height / (float) width;
//    ini_x = width/2;
//    ini_y = height/2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -ar, ar, near_id, far_id);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}


static GLfloat v_box[8][3] =
{
    {-2.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {-2.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},

    {-2.0, 2.0, 0.0},
    {2.0, 2.0, 0.0},
    {-2.0, 2.0, 2.0},
    {2.0, 2.0, 2.0}
};

static GLubyte quadIndices[6][4] =
{
    {0,2,3,1},
    {0,2,6,4},
    {2,3,7,6},
    {1,3,7,5},
    {1,5,4,0},
    {6,7,5,4}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
int ii = 1;
GLuint ID_[100];

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID_[ii]);
    glBindTexture(GL_TEXTURE_2D, ID_[ii]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[ii++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void drawBox()
{
    //  glColor3f(1,1,1);
    //GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
                    v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
                    v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);

        glVertex3fv(&v_box[quadIndices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices[i][2]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&v_box[quadIndices[i][3]][0]);
        glTexCoord2f(0,0);
    }


    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}
static GLfloat bin_coordinate[8][3] =
{
    {0,0,0},
    {0,0,2},
    {2,0,2},
    {2,0,0},
    {1.5,-4,0},
    {0.5,-4,0},
    {0.5,-4,2},
    {1.5,-4,2}
};
static GLubyte bin_Indices[5][4] =
{
    {2,1,6,7},
    {3,2,7,4},
    {0,3,4,5},
    {1,0,5,6},
    {7,6,5,4}

};
void draw_cube(GLfloat r, GLfloat g,GLfloat b)
{

//    r = r/255.0;
//    g = g/255.0;
//    b = b/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCube(1);

}

void draw_sphere(GLfloat r, GLfloat g,GLfloat b)
{

//    r = r/255.0;
//    g = g/255.0;
//    b = b/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(1,10,10);

}
void draw_cone(GLfloat r, GLfloat g,GLfloat b)
{

//    r = r/255.0;
//    g = g/255.0;
//    b = b/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCone(2,2,10,10);

}
void draw_bin(GLfloat r, GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <5; i++)
    {
        //glColor3f(1,1,0);
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&bin_coordinate[bin_Indices[i][0]][0]);
        glVertex3fv(&bin_coordinate[bin_Indices[i][1]][0]);
        glVertex3fv(&bin_coordinate[bin_Indices[i][2]][0]);
        glVertex3fv(&bin_coordinate[bin_Indices[i][3]][0]);
    }



    glEnd();
}
void seat()
{
    glPushMatrix();
    glScalef(3,0.5,3);
    draw_cube(0.98,0.969,0.784);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.8,-1.5);
    glScalef(3,4,0.5);
    draw_cube(0.98,0.969,0.784);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,1.5,0);
    glRotatef(-45,1,0,0);
    glScalef(0.3,4,0.3);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,1.5,0);
    glRotatef(-45,1,0,0);
    glScalef(0.3,4,0.3);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.5,0);
    glScalef(3,0.3,0.3);
    draw_cube(0,0,0);
    glPopMatrix();
}
void ferris_wheel(float r, float g, float b)
{
    glPushMatrix();
    glPushMatrix();
    glScalef(0.8,0.8,0.6);
    draw_sphere(r,g,b);
    glPopMatrix();
    GLUquadricObj *p = gluNewQuadric();
    //gluQuadricDrawStyle(GLU__LINE);
    gluCylinder(p,2,2,1,100,100);
    glPushMatrix();
    glScalef(0.2,4,0.2);
    draw_cube(r,g,b);
    glPopMatrix();

    int theta_temp=90;
    for(int i=1; i<=3; i++)
    {
        glPushMatrix();
        glRotatef(theta_temp,0,0,1);
        glScalef(0.2,4,0.2);
        draw_cube(r,g,b);
        glPopMatrix();
        theta_temp-=45;
    }
    glPopMatrix();


}
void ferris_wheel_seat()
{
    //chair
    glPushMatrix();
    glTranslatef(10,0,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,0,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,10,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-10,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7,7,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,7,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,-7,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7,-7,1);
    glRotatef(90,1,0,0);
    glScalef(0.8,0.8,0.8);
    seat();
    glPopMatrix();
}
void ferris_wheel_stand()
{
    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(30,0,0,1);
    glScalef(0.5,10,1);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0,3);
    glRotatef(-40,1,0,0);
//    glRotatef(60,0,0,1);
    glScalef(0.5,10,1);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,0,1);
    glScalef(0.5,10,1);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();
}
void light()
{
    glPushMatrix();
    glTranslatef(24.2,9,2.5);
    glScalef(1,1,4);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5, 0.5, 0.5, 1.0);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(24.2,9,2.5);
    glScalef(0.9,0.9,3.9);
//    glColor3f(255,255,255);
//    glutSolidCube(1);
    draw_cube(1,1,1);
    glPopMatrix();
}
void open_close_door()
{

    if(odx<=11&&odx_limit<=11)
    {
        odx+=5;
        odx_limit+=5;
    }
    else if(odx>0&&odx_limit>=11)
    {
        odx-=5;
    }
    else{
        odx_limit=0;
    }
}

void gate()
{
//        front wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(odx,0,0);
    glTranslatef(-10,-26.5,5.5);
    glScalef(4.8,9.8,1.0);
    glBindTexture(GL_TEXTURE_2D, 36);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glTranslatef(odx,0,0);
    glTranslatef(9.5,-26.5,4.5);
    glScalef(4.8,9.8,1.0);
    glBindTexture(GL_TEXTURE_2D, 36);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-1,0);
    //glRotatef(180,0,0,1);
    glScalef(15,8,1);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\fair.bmp");
    glBindTexture(GL_TEXTURE_2D, 1);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //exit left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,-7,0);
    glScalef(3,3,1);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\exit.bmp");
    glBindTexture(GL_TEXTURE_2D, 15);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //exit right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-7,0);
    glScalef(3,3,1);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\exit.bmp");
    glBindTexture(GL_TEXTURE_2D, 15);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //entry
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-7,0);
    glScalef(9.5,3,1);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\welcome.bmp");
    glBindTexture(GL_TEXTURE_2D, 3);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall
    glPushMatrix();
    glTranslatef(-30,-17,1);
    glScalef(1,20,1.5);
    draw_cube(0.929,0.827,0.035);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30,-17,1);
    glScalef(1,20,1.5);
    draw_cube(0.929,0.827,0.035);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,-17,1);
    glScalef(1,20,1.5);
    draw_cube(0.929,0.827,0.035);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20,-17,1);
    glScalef(1,20,1.5);
    draw_cube(0.929,0.827,0.035);
    glPopMatrix();

}
void ferris_wheel1()
{
    glPushMatrix();
    glTranslatef(10,7,1);
    glScalef(2,2,1);
    glPushMatrix();
    glRotatef(-60,1,0,0);
    glRotatef(theta2,0,0,1);
    glPushMatrix();
    glScalef(5,5,1);
    ferris_wheel(0.98,0.741,0.078);
    glPopMatrix();

    glPushMatrix();
    ferris_wheel_seat();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,-5,0);
    ferris_wheel_stand();
    glPopMatrix();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(13,-11.5,-12);
    glScalef(12,0.9,12);
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




}
void ferris_wheel2()
{
    //1
    glPushMatrix();
    glTranslatef(15,0,0);
    glPushMatrix();
    glTranslatef(1,29,1);
    glRotatef(theta2,0,1,1);//y,z
    glPushMatrix();
    glTranslatef(-28,9,1);
    glScalef(1.5,1.5,1.5);
    glRotatef(theta2,0,1,0);
    glPushMatrix();
    glRotatef(-60,1,0,0);
    //glRotatef(theta2,0,0,1);
    glPushMatrix();
    glScalef(5,5,1);
    ferris_wheel(0.431,0.286,0.114);
    glPopMatrix();

    glPushMatrix();
    ferris_wheel_seat();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    //////////////////////////////////////

    //2
    glPushMatrix();
    glTranslatef(28,9,1);
    glScalef(1.5,1.5,1.5);
    glRotatef(theta2,0,1,0);
    glPushMatrix();
    glRotatef(-60,1,0,0);
    //glRotatef(theta2,0,0,1);
    glPushMatrix();
    glScalef(5,5,1);
    ferris_wheel(0.431,0.286,0.114);
    glPopMatrix();

    glPushMatrix();
    ferris_wheel_seat();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    /////////////////////////////////////

    glPushMatrix();
    glScalef(56,1,1);
    draw_cube(0.89,0.71,0.498);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-28,5,0);
    glScalef(1,10,1);
    draw_cube(0.89,0.71,0.498);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28,5,0);
    glScalef(1,10,1);
    draw_cube(0.89,0.71,0.498);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-10,0);
    glRotatef(-90,1,0,0);
    glScalef(5,5,20);
    draw_cone(0.89,0.71,0.498);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,25,0);
    glRotatef(theta2,0,1,0);
    glScalef(5,5,5);
    draw_sphere(0,0,1);
    glPopMatrix();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(13,-11.5,-12);
    glScalef(12,0.9,12);
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(20,-9,-12);
    glScalef(5,0.9,12);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,-6,-12);
    glScalef(3,0.9,12);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(21,-3,-12);
    glScalef(1,0.9,12);
    drawBox();
    glPopMatrix();
}
void floor1()
{
    glPushMatrix();
    glTranslatef(20,-20,0);
    glScalef(900,3,1100);
    draw_cube(0.361,0.839,0.369);
    glPopMatrix();

}
void ferris_wheel3()
{
    glPushMatrix();
    glTranslatef(12,0,0);
    glPushMatrix();
    glTranslatef(0,3,0);
    glRotatef(90,1,0,0);
    //glScalef(3,3,1);
    glScalef(6.5,6.5,1);
    draw_sphere(1,0,0);
    glPopMatrix();

    //stand
    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(1,15,1);
    draw_cube(1,1,0);
    glPopMatrix();

    //ghurbe
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(1.5,1.5,1.5);
    glRotatef(theta2,0,1,0);
    glPushMatrix();
    glTranslatef(0,-2,0);
    glRotatef(-90,1,0,0);
    glScalef(3,3,3);
    draw_cone(0,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,-3.8,0);
    glRotatef(-45,0,0,1);
    glScalef(0.2,5,0.2);
    draw_cube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7,-3.8,0);
    glRotatef(45,0,0,1);
    glScalef(0.2,5,0.2);
    draw_cube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-3.5,7);
    glRotatef(-45,1,0,0);
    glScalef(0.2,5,0.2);
    draw_cube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-3.5,-7);
    glRotatef(45,1,0,0);
    glScalef(0.2,5,0.2);
    draw_cube(1,1,0);
    glPopMatrix();
    //chair
    glPushMatrix();
    glTranslatef(-10.5,-5.5,-1);
    glScalef(1,0.5,1);
    draw_bin(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.8,-5.5,-1);
    glScalef(1,0.5,1);
    draw_bin(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,-5.2,-10);
    glScalef(1,0.5,1);
    draw_bin(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,-5.2,8.5);
    glScalef(1,0.5,1);
    draw_bin(1,1,0);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

        //base
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glTranslatef(13,-11.5,-12);
//    glScalef(8,0.9,12);
//    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
//    glBindTexture(GL_TEXTURE_2D, 4);
//    drawBox();
//
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

}
void base(){
        //base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(13,-11.5,-12);
    glScalef(8,0.9,12);
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void sitting()
{
    //stand
    glPushMatrix();
    glTranslatef(0,-10,0);
    glScalef(1,25,1);
    draw_cube(0.5,0,0.5);
    glPopMatrix();

    //umbrella
    glPushMatrix();
    glTranslatef(0,-2,0);
    glRotatef(-90,1,0,0);
    glScalef(6,6,3);
    draw_cone(0.6,0,1);
    glPopMatrix();
    //sit
    glPushMatrix();
    glTranslatef(0,-18,0);
    glScalef(18,5,5);
    draw_cube(0.5,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-18,0);
    glRotatef(90,0,1,0);
    glScalef(18,5,5);
    draw_cube(0.5,0.5,0.5);
    glPopMatrix();

}
float skyD=0,sklimit=0;
bool skdrop = false;
void skydropseat()
{
    glPushMatrix();
    glTranslatef(8,1.8,-2);
    glScalef(20,2,0.5);
    draw_cube(0.98,0.969,0.784);
    glPopMatrix();
    for(float i = 0; i<=20; i+=3.5)
    {
        glPushMatrix();
        glTranslatef(i,0,0);
        glPushMatrix();
        glScalef(3,0.5,3);
        draw_cube(0.98,0.969,0.784);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,1.8,-1.5);
        glScalef(3,4,0.5);
        draw_cube(0.98,0.969,0.784);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.5,1.5,0);
        glRotatef(-45,1,0,0);
        glScalef(0.3,4,0.3);
        draw_cube(0,0,0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.5,1.5,0);
        glRotatef(-45,1,0,0);
        glScalef(0.3,4,0.3);
        draw_cube(0,0,0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,1.5,0);
        glScalef(3,0.3,0.3);
        draw_cube(0,0,0);
        glPopMatrix();
        glPopMatrix();


    }
}
void skydrop()
{
    float r = 0.957, g = 0.988, b = 0.012;
    for(float i = 0; i<=10; i+=1.5)
    {
        glPushMatrix();
        glTranslatef(i,0,0);
        glScalef(0.8,30,1);
        draw_cube(r,g,b);
        glPopMatrix();
        r-=0.05;
        g-=0.05;

        glPushMatrix();
        glTranslatef(i+0.7,0,0);
        glScalef(0.5,30,1);
        draw_cube(0.902,0.98,0.784);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(0,skyD,0);
    glTranslatef(-4.5,-10,2);
    //glScalef(2,2,2);
    skydropseat();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4.5,-17,-5);
    glScalef(6,0.5,6);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4.5,-16,-5);
    glScalef(5,0.5,5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick_w.bmp");
    glBindTexture(GL_TEXTURE_2D, 5);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
float swing_theta=0, swing_limit=0;
float swing_theta2=0, swing_limit2=0;
bool swing_on=false;
void swing_chair()
{
    glPushMatrix();
    glTranslatef(1,0,0);
    glRotatef(90,0,1,0);
    GLUquadricObj *p = gluNewQuadric();
    gluCylinder(p,1,1,0.5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(90,0,1,0);
//    GLUquadricObj *p = gluNewQuadric();
    gluCylinder(p,1,1,0.5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,-15,0);
    glScalef(4.8,0.5,3);
    draw_cube(0.98,0.969,0.784);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2,-7.5,0);
    glScalef(0.5,15,0.5);
    draw_cube(0.639,0.467,0.322);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2,-7.5,0);
    glScalef(0.5,15,0.5);
    draw_cube(0.639,0.467,0.322);
    glPopMatrix();



}
void swing()
{
    //left handle
    glPushMatrix();
    glTranslatef(0,0,5.5);
    glRotatef(-30,1,0,0);
    glScalef(0.5,25,0.5);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-5.5);
    glRotatef(30,1,0,0);
    glScalef(0.5,25,0.5);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();

    //right handle
    glPushMatrix();
    glTranslatef(30,0,0);
    glPushMatrix();
    glTranslatef(0,0,5.5);
    glRotatef(-30,1,0,0);
    glScalef(0.5,25,0.5);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-5.5);
    glRotatef(30,1,0,0);
    glScalef(0.5,25,0.5);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();
    glPopMatrix();
//
//    //horizontal
    glPushMatrix();
    glTranslatef(15,10,0);
    glScalef(32,0.5,0.5);
    draw_cube(0.929,0.58,0.251);
    glPopMatrix();


    //chair

    for(float i=0; i<30; i+=8)
    {
        glPushMatrix();
        glTranslatef(i,10,0);
        glRotatef(swing_theta,1,0,0);
        swing_chair();
        glPopMatrix();
    }
    //base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(13,-11.5,-12);
    glScalef(12,0.9,12);
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void sky2()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,25);
    glTranslatef(50,350,-600);
    glScalef(250,0.01,400);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,34);
    glTranslatef(20,-30,-590);
    glScalef(200,200,0.01);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//////
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,35);
    glTranslatef(420,-30,-590);
    glScalef(0.01,200,400);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,34);
    glTranslatef(-380,-30,-590);
    glScalef(0.01,200,400);
    drawBox();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void sky()
{

    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(0,140,0);
    glScalef(2000000,0,2000000);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-200,-500);
    glScalef(2000000,2000000,0);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawBox();
    glPopMatrix();
//        glDisable(GL_TEXTURE_GEN_S);
//    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
}
void icecream_parlour()

{

    //ice cream
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(-11,4,0);
    glRotatef(25,0,0,1);
    glRotatef(90,1,0,0);
    glScalef(3,2,10);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 4);
    draw_cone(0.953,0.988,0.604);

    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(-11,4,-1);
    glScalef(5,5,4);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice5.bmp");
    glBindTexture(GL_TEXTURE_2D, 6);
    draw_sphere(1,1,1);
    //glBindTexture(GL_TEXTURE_2D, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);


    //back wall
    glPushMatrix();
    glTranslatef(12.5,-0.5,-10);
    glScalef(26,24.5,1.0);
    draw_cube(0.953,0.988,0.604);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,3.5,6);
    glScalef(6,4,0.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice6.bmp");
    glBindTexture(GL_TEXTURE_2D, 7);
    drawBox();
    //  glBindTexture(GL_TEXTURE_2D, 8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //left
    glPushMatrix();
    glTranslatef(0,-12.2,-9.5);
    glScalef(0.25,12,7.5);
    drawBox();
    glPopMatrix();

    //right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-12.2,-9.5);
    glScalef(0.25,12,7.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice4.bmp");
    glBindTexture(GL_TEXTURE_2D, 8);
    drawBox();
    //  glBindTexture(GL_TEXTURE_2D, 9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,-12.8,-9.5);
    glScalef(10,0.25,8.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
    glBindTexture(GL_TEXTURE_2D, 9);
    drawBox();
    //glBindTexture(GL_TEXTURE_2D, 9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //front wall
//    glPushMatrix();
//    glTranslatef(odx,0,0);
//    glTranslatef(12.5,0,5.5);
//    glScalef(26,24.0,1.0);
//    draw_cube(1,1,1);
//    glPopMatrix();

    //board
    glPushMatrix();
    glTranslatef(12.5,18,4.5);
    glScalef(21,10,1);
    draw_cube(0.953,0.988,0.604);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,13,4.5);
    glScalef(4,4,0.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
    glBindTexture(GL_TEXTURE_2D, 9);
    drawBox();
    //glBindTexture(GL_TEXTURE_2D, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chhad
    glPushMatrix();
    //glRotatef(90, 0, 1, 0 );
    glTranslatef(12.5,12.5,-2.5);
    glScalef(26.0,1.0,15.0);
    glColor3f(128, 128, 128);
    draw_cube(1,0,1);
    glPopMatrix();

    //.......................sink..........................//

    //with back wall
    glPushMatrix();
    glTranslatef(20.0,-9,-6.0);
    glScalef(10,7,7);
    draw_cube(0.82,1.,0.459);
    glPopMatrix();
    //with right wall
    glPushMatrix();
    glTranslatef(22.0,-8.7,1.0);
    glScalef(5,6.5,8);
    draw_cube(0.659,0.929,0.843);
    glPopMatrix();

    //border on sink
    glPushMatrix();
    glTranslatef(19.5,-6,1.0);
    glScalef(0.2,0.2,8);
    draw_cube(0,0,0);
    glPopMatrix();
    //horizontal line on sink
    glPushMatrix();
    glTranslatef(19.5,-9,1.0);
    glScalef(0.2,6.5,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,-8,2.0);
    glScalef(0.2,2,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,-8,0.0);
    glScalef(0.2,2,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    //........................................fridge.....................//
    glPushMatrix();
    glTranslatef(5,-6.3,-7);
    glScalef(5,9,4);
    draw_cube(0.02,0.776,0.929);
    glPopMatrix();

    //fridge base
    glPushMatrix();
    glTranslatef(5,-11.5,-7);
    glScalef(5.5,1.5,4.5);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

    //fridge door
    glPushMatrix();
    glTranslatef(5.2,-3.5,-5);
    glScalef(4,3,1);
    draw_cube(0.737,0.922,0.961);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2,-8,-5);
    glScalef(4,4.5,1);
    draw_cube(0.737,0.922,0.961);
    glPopMatrix();

    //fridge handle
    glPushMatrix();
    glTranslatef(6.5,-3.5,-4.5);
    glScalef(.3,1.5,.3);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,-7,-4.5);
    glScalef(.3,1.5,.3);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

}

void noodles_parlour()

{

    //back wall
    glPushMatrix();
    glTranslatef(12.5,-0.5,-10);
    glScalef(26,24.5,1.0);
    draw_cube(0.953,0.988,0.604);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,3.5,6);
    glScalef(6,4,0.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice6.bmp");
    glBindTexture(GL_TEXTURE_2D, 10);
    drawBox();
    //  glBindTexture(GL_TEXTURE_2D, 8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-12.2,-9.5);
    glScalef(0.25,12,7.5);
    glBindTexture(GL_TEXTURE_2D, 13);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-12.2,-9.5);
    glScalef(0.25,12,7.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice4.bmp");
    glBindTexture(GL_TEXTURE_2D, 13);
    drawBox();
    //  glBindTexture(GL_TEXTURE_2D, 9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,-12.8,-9.5);
    glScalef(10,0.25,8.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
    glBindTexture(GL_TEXTURE_2D, 12);
    drawBox();
    //glBindTexture(GL_TEXTURE_2D, 9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //front wall
//    glPushMatrix();
//    glTranslatef(odx,0,0);
//    glTranslatef(12.5,0,5.5);
//    glScalef(26,24.0,1.0);
//    draw_cube(1,1,1);
//    glPopMatrix();

    //board
    glPushMatrix();
    glTranslatef(12.5,18,4.5);
    glScalef(21,10,1);
    draw_cube(0.953,0.988,0.604);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,13,4.5);
    glScalef(4,4,0.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
    glBindTexture(GL_TEXTURE_2D, 14);
    drawBox();
    //glBindTexture(GL_TEXTURE_2D, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chhad
    glPushMatrix();
    //glRotatef(90, 0, 1, 0 );
    glTranslatef(12.5,12.5,-2.5);
    glScalef(26.0,1.0,15.0);
    glColor3f(128, 128, 128);
    draw_cube(1,0,1);
    glPopMatrix();

    //.......................sink..........................//

    //with back wall
    glPushMatrix();
    glTranslatef(20.0,-9,-6.0);
    glScalef(10,7,7);
    draw_cube(0.82,1.,0.459);
    glPopMatrix();
    //with right wall
    glPushMatrix();
    glTranslatef(22.0,-8.7,1.0);
    glScalef(5,6.5,8);
    draw_cube(0.659,0.929,0.843);
    glPopMatrix();

    //border on sink
    glPushMatrix();
    glTranslatef(19.5,-6,1.0);
    glScalef(0.2,0.2,8);
    draw_cube(0,0,0);
    glPopMatrix();
    //horizontal line on sink
    glPushMatrix();
    glTranslatef(19.5,-9,1.0);
    glScalef(0.2,6.5,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,-8,2.0);
    glScalef(0.2,2,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,-8,0.0);
    glScalef(0.2,2,0.2);
    draw_cube(0,0,0);
    glPopMatrix();

    //........................................fridge.....................//
    glPushMatrix();
    glTranslatef(5,-6.3,-7);
    glScalef(5,9,4);
    draw_cube(0.02,0.776,0.929);
    glPopMatrix();

    //fridge base
    glPushMatrix();
    glTranslatef(5,-11.5,-7);
    glScalef(5.5,1.5,4.5);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

    //fridge door
    glPushMatrix();
    glTranslatef(5.2,-3.5,-5);
    glScalef(4,3,1);
    draw_cube(0.737,0.922,0.961);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2,-8,-5);
    glScalef(4,4.5,1);
    draw_cube(0.737,0.922,0.961);
    glPopMatrix();

    //fridge handle
    glPushMatrix();
    glTranslatef(6.5,-3.5,-4.5);
    glScalef(.3,1.5,.3);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,-7,-4.5);
    glScalef(.3,1.5,.3);
    draw_cube(0.3,0.2,0.2);
    glPopMatrix();

}

void ticket_counter(){

    //back wall
    glPushMatrix();
    glTranslatef(12.5,-0.5,-10);
    glScalef(26,24.5,1.0);
    draw_cube(0.961,0.62,0.173);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,3.5,6);
    glScalef(6,4,0.5);
    glBindTexture(GL_TEXTURE_2D, 18);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,-12,6);
    glScalef(6,4,0.5);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    glPushMatrix();
//    glTranslatef(12.5,-12,6);
//    glScalef(6,4,0.5);
//
//    glPopMatrix();



    //left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-12.2,-9.5);
    glScalef(0.25,12,7.5);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(25,-12.2,-9.5);
    glScalef(0.25,12,7.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice4.bmp");
    glBindTexture(GL_TEXTURE_2D, 16);
    drawBox();
    //  glBindTexture(GL_TEXTURE_2D, 9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    //floor
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glTranslatef(12.5,-12.8,-9.5);
//    glScalef(10,0.25,8.5);
////    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
//    glBindTexture(GL_TEXTURE_2D, 17);
//    drawBox();
//    //glBindTexture(GL_TEXTURE_2D, 9);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    //board
    glPushMatrix();
    glTranslatef(12.5,18,4.5);
    glScalef(21,10,1);
    draw_cube(0.953,0.988,0.604);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.5,13,4.5);
    glScalef(4,4,0.5);
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");
    glBindTexture(GL_TEXTURE_2D, 15);
    drawBox();
    //glBindTexture(GL_TEXTURE_2D, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chhad
    glPushMatrix();
    //glRotatef(90, 0, 1, 0 );
    glTranslatef(12.5,12.5,-2.5);
    glScalef(26.0,1.0,15.0);
    glColor3f(128, 128, 128);
    draw_cube(1,0,1);
    glPopMatrix();
}

GLfloat mini_fence_coordinate[8][3] =
{
    {3.0,-5.0,0.0},
    {3.0,5.0,0.0},
    {1.0,5.0,0.0},
    {1.0,-5.0,0.0},

    {3.0,-5.0,2.0},
    {3.0,5.0,2.0},
    {1.0,5.0,2.0},
    {1.0,-5.0,2.0},

};
static GLubyte mini_fence_indices[6][4] =
{
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};

void draw_mini_fence_cube()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_diffuse[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_specular[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_shininess[] = {20};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        // glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][0]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][1]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][2]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][3]][0]);
    }
    glEnd();
}

float fence_gate_slide = 0.0;

void draw_fence()
{
    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(j,5,0);
        draw_mini_fence_cube();
        glPopMatrix();

        if(j<113){
        glPushMatrix();
        glTranslatef(j+6,5,0);
        glRotatef(90,0,0,1);
        draw_mini_fence_cube();
        glPopMatrix();}

    }

    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(0,5,j);
        draw_mini_fence_cube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,5,j);
        glRotatef(90,1,0,0);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(120,5,j);
        draw_mini_fence_cube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(120,5,j);
        glRotatef(90,1,0,0);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=0;j<=45;j+=4)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(j,0,121);
        glBindTexture(GL_TEXTURE_2D,36);
        //draw_mini_fence_cube();
        glScalef(1,7,1);
        drawBox();

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    for (int j=79;j<=120;j+=4)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(j,0,121);
        glBindTexture(GL_TEXTURE_2D,36);
        //draw_mini_fence_cube();
        glScalef(1,7,1);
        drawBox();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

//        if(j<113){
//        glPushMatrix();
//        glTranslatef(j+5,5,120);
//        glRotatef(90,0,0,1);
//        draw_mini_fence_cube();
//
//        glPopMatrix();}
    }

//    for (int j=46;j<=74;j+=4)
//    {
//        glPushMatrix();
//        glTranslatef(j+fence_gate_slide,5,115);
//        draw_mini_fence_cube();
//        glPopMatrix();
//    }

//    glPushMatrix();
//    glTranslatef(0,0,117);
//    glScalef(60,.07,1);
//    draw_cube(0.54, 0.27, 0.075);
//    glPopMatrix();
}


void tree(){
    glPushMatrix();
    glTranslatef(0,20,50);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glScalef(10,9,10);
    glBindTexture(GL_TEXTURE_2D, 19);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14,0,0);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14,0,0);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-14);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,14);
    glBindTexture(GL_TEXTURE_2D, 21);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    //2nd layer
    glPushMatrix();
    glTranslatef(-9,10,5);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,10,-5);
    glScalef(10,9,10);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8,9,8);
    glScalef(10,9,10);
    glBindTexture(GL_TEXTURE_2D, 24);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,25,8);
    glScalef(12,12,12);
    glBindTexture(GL_TEXTURE_2D, 24);
    draw_sphere(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,25,8);
    glScalef(12,12,12);
    glBindTexture(GL_TEXTURE_2D, 23);
    draw_sphere(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    GLUquadricObj *p = gluNewQuadric();
    glScalef(1,40,1);
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D, 4);
    gluCylinder(p,2,2,1,100,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void torus_swing(){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,35,0);
    glRotatef(180,1,0,0);
    glRotatef(swing_theta,1,0,0);
    glPushMatrix();
//    glRotatef(180,1,0,0);
//    glRotatef(swing_theta,1,0,0);
    glScalef(0.2,15,0.2);
    glBindTexture(GL_TEXTURE_2D, 4);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,40,0);
    glRotatef(swing_theta2,0,1,0);
    glScalef(1,1,1);
    glutSolidTorus(1,12,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,35,0);
    glScalef(0.5,2,0.3);
    glutSolidTorus(1,3,100,100);
    glPopMatrix();
    glPopMatrix();

}
void draw_hammock()
{
    float r = 100;
    glBegin(GL_POINTS);
    glColor3f(1,0,1);

    for(float i=180;i<360;i+=0.01)
    {
        float theta = acos(-1)*i/180 ;
        glVertex2f(r*cos(theta), r*sin(theta));
    }
    glEnd();
}


void draw_ham()
{
    for(float i = 0; i<20;i+=1)
    {
        glPushMatrix();
        glRotatef(i*1.5,1,0,0);
        draw_hammock();
        glPopMatrix();
    }

    for(float i = 1; i<20;i+=1)
    {
        glPushMatrix();
        glRotatef(-i*1.5,1,0,0);
        draw_hammock();
        glPopMatrix();
    }


}

void fun_fair()
{
    //...............................hammock.........................//
    glPushMatrix();
    glTranslatef(95,25,-168);
    glScalef(0.43,0.4,0.8);
    glRotatef(swing_theta,1,0,0);
    draw_ham();
    glPopMatrix();

    //..............................tree..............................///
    for(int i=10; i<=90; i+=42)
    {
        glPushMatrix();
        glTranslatef(i,0,-220);
        glPushMatrix();
        glTranslatef(-20,5,50);
        torus_swing();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0,14,0);
        glScalef(1,1.8,1);
        tree();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-20,-6,50);
        base();
        glPopMatrix();
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(140,0,-220);
    glPushMatrix();
    glTranslatef(0,14,0);
    glScalef(1,1.5,1);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20,-6,50);
    base();
    glPopMatrix();
    glPopMatrix();

    //.............................noodles parlor.......................//
    glPushMatrix();
    glTranslatef(-150,0,-120);
    glRotatef(70,0,1,0);
    glScalef(1.5,1.5,1.5);
    noodles_parlour();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-115,2,-160);
    sitting();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-115,2,-140);
    sitting();
    glPopMatrix();
    //.............................icecream parlor.......................//
    glPushMatrix();
    glTranslatef(-160,0,-60);
    glRotatef(70,0,1,0);
    glScalef(1.5,1.5,1.5);
    icecream_parlour();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-125,2,-80);
    sitting();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-125,2,-100);
    sitting();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150,2,-40);
    sitting();
    glPopMatrix();

    //................................sky...............................//
    glPushMatrix();
    //glTranslatef(-30,-7,-5);
    sky2();
    glPopMatrix();

    //................................swing............................//
    glPushMatrix();
    glTranslatef(250,-7,-25);
    //glRotatef(-70,0,1,0);
    swing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160,-7,-20);
    glRotatef(-70,0,1,0);
    swing();
    glPopMatrix();

    //................................skydrop...........................//
    glPushMatrix();
    glTranslatef(-80,32,-175);
    glScalef(3,3,1);
    skydrop();
    glPopMatrix();
    //................................floor............................//
    glPushMatrix();
    floor1();
    glPopMatrix();
    //................................gate.............................//
    glPushMatrix();
    glTranslatef(0,0,50);
    glPushMatrix();
    glTranslatef(76,75,262);
    glScalef(2.1,3.5,1);
    gate();
    glPopMatrix();
        //.....................................fence........................//

    glPushMatrix();
    glTranslatef(-200,-18,-400);
    glScalef(4.5,2,5.5);
    draw_fence();
    glPopMatrix();
    //.............................ticket counter......................//
    glPushMatrix();
    glTranslatef(7,0,250);
    //glRotatef(-70,0,1,0);
    glScalef(1.2,1.5,1.5);
    ticket_counter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(118,0,250);
    //glRotatef(-70,0,1,0);
    glScalef(1.2,1.5,1.5);
    ticket_counter();
    glPopMatrix();
    glPopMatrix();
    //................................sitting...........................//
//    glPushMatrix();
//    glTranslatef(-10,3,-80);
//    sitting();
//    glPopMatrix();

    //................................ferris_wheel1.....................//
    glPushMatrix();
    glTranslatef(250,-4,-115);
    glScalef(1,1.2,1);
    ferris_wheel1();
    glPopMatrix();


    //................................ferris_wheel2....................//

    glPushMatrix();
    glTranslatef(190,-7,-180);
    ferris_wheel2();
    glPopMatrix();
//
    //..........................wheel3................................//

    glPushMatrix();
    glTranslatef(-45,-7,-55);
    glPushMatrix();
    glScalef(3,1,3);
    base();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-10);
    ferris_wheel3();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50,0,-10);
    ferris_wheel3();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25,0,20);
    ferris_wheel3();
    glPopMatrix();
    glPopMatrix();
}
void lightF(double x, double y, double z, GLenum L, bool light_on, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);


//    glTranslatef(x,y,z);
//    glutSolidSphere(1,100,100);
    if(light_on)
    {

        if(L==GL_LIGHT0)
        {
            if(amb_light_0) glLightfv( L, GL_AMBIENT, light_ambient);
            else glLightfv( L, GL_AMBIENT, no_light);

            if(dif_light_0) glLightfv( L, GL_DIFFUSE, light_diffuse);
            else glLightfv( L, GL_DIFFUSE, no_light);

            if(spec_light_0) glLightfv( L, GL_SPECULAR, light_specular);
            else glLightfv( L, GL_SPECULAR, no_light);

            glLightfv( L, GL_POSITION, light_position);
        }
        else
        {
            if(amb_light_1) glLightfv( L, GL_AMBIENT, light_ambient);
            else glLightfv( L, GL_AMBIENT, no_light);

            if(dif_light_1) glLightfv( L, GL_DIFFUSE, light_diffuse);
            else glLightfv( L, GL_DIFFUSE, no_light);

            if(spec_light_1) glLightfv( L, GL_SPECULAR, light_specular);
            else glLightfv( L, GL_SPECULAR, no_light);

            glLightfv( L, GL_POSITION, light_position);
        }
    }

    else
    {
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }

    if(spot)
    {

        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 55);
    }

}

void bird_view()
{
    swap(eyey, eyez);
    //swap(upy, upz);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//bitwise 0 kora depth buff er
    glMatrixMode( GL_PROJECTION ); //3d to 2d by matrix multiplication. say p , 4x4 matrix
    glLoadIdentity(); //identity matrix load kora projection matrix e, p=I\

    glFrustum(-5, 5, -5, 5, near_id, far_id);//view window er l,r,b,t,5 no. near plane//near change to 15
    //glOrtho(-40,40,-30,30,2,70);
//    gluPerspective(60,1,2,200000);
    glMatrixMode( GL_MODELVIEW ); //same matrix for model and view, 4x4 matrix,
    glLoadIdentity();
    //gluLookAt(5,2,50, 2,0,0, 0,1,0);
    gluLookAt(eyex, eyey, eyez, centerx,centery, centerz, upx,upy,upz);

    //glViewport(0, 0, windowHeight, windowWidth);
    glScalef(scale_x,scale_y,scale_z);
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glScalef(1,1.5,1);

    fun_fair();




    lightF(24.2,9,2.5, GL_LIGHT0, light_0_on, false);
    lightF(22,3,-7, GL_LIGHT1, light_1_on, true);
    glFlush();
    glutSwapBuffers();
}
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'r':
        if(anglePitch>=anglePitchLimit1)
            break;
        anglePitch += def_value;
        centery = 200.0*(sin(anglePitch*3.1416/180.0));
        break;
    case 't':
        if(anglePitch==anglePitchLimit2)
            break;
        anglePitch -= def_value;
        centery = 200.0*(sin(anglePitch*3.1416/180.0));
        break;
    case 'y':
        if(angleYaw==angleYawLimit1)
            break;
        angleYaw += def_value;
        centerx = 200.0*(cos(angleYaw*3.1416/180.0));
        break;
    case 'u':
        if(angleYaw==angleYawLimit2)
            break;
        angleYaw -= def_value;
        centerx = 200.0*(cos(angleYaw*3.1416/180.0));
        break;
    case 'i':
        angleRoll += def_value;
        upx =cos(angleRoll*3.1416/180.0);//-sin(angleYaw*3.1416/180.0));
        upy =sin(angleRoll*3.1416/180.0);

        break;
    case 'o':
        angleRoll -= def_value;
        upx =cos(angleRoll*3.1416/180.0);//-sin(angleYaw*3.1416/180.0));
        upy =sin(angleRoll*3.1416/180.0);

        break;
    case 'a':
        eyex-=5;
        centerx-=5;
        break;
    case 'd':
        eyex+=5;
        centerx+=5;
        break;
    case 'w':
        eyey+=5;
        centery+=5;
        break;
    case 's':
        eyey-=5;
        centery-=5;
        break;
    case 'f':
        eyez+=7;
        centerz+=7;
        glutPostRedisplay();
        break;
    case 'g':
        eyez-=7;
        centerz-=7;
        glutPostRedisplay();
        break;
    case 'z':
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;

    case 'e':
    case 'E':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'x':
        bird_view();
        break;

    case 'q':
    case 'Q':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'j':
        fanRotate=!fanRotate;
        break;

    case 'p':
        open_close_door();
        break;
    case '0':
        light_0_on = !light_0_on;
        break;
    case '9':
        light_1_on = !light_1_on;
        break;


    case '8':
        amb_light_0 = !amb_light_0;
        break;
    case '7':
        dif_light_0 = !dif_light_0;
        break;
    case '6':
        spec_light_0 = !spec_light_0;
        break;


    case '5':
        amb_light_1 = !amb_light_1;
        break;
    case '4':
        dif_light_1 = !dif_light_1;
        break;
    case '3':
        spec_light_1 = !spec_light_1;
        break;
    case 'b':
        skdrop=!skdrop;
        break;
    case 'v':
        swing_on=!swing_on;
        break;

    case 27:	// Escape key
        exit(1);
    }
}
void animate()
{
    if(swing_on)
    {
        if(swing_theta<=35 && swing_limit<=35)
        {
            swing_theta+=1.5;
            swing_limit+=1.5;
        }
        else if(swing_theta>=-35)
        {
            swing_theta-=1.5;
        }
        else
        {
            swing_limit=-35;
        }

        if(swing_theta2<=100 && swing_limit2<=100)
        {
            swing_theta2+=2;
            swing_limit2+=2;
        }
        else if(swing_theta2>=-100)
        {
            swing_theta2-=2;
        }
        else
        {
            swing_limit2=-100;
        }
    }
    if(skdrop)
    {
        if(skyD<=20 && sklimit<=20)
        {
            Sleep(100);
            skyD+=0.8;
            sklimit+=0.8;
        }
        else if(skyD>=0)
        {
            skyD-=0.8;
        }
        else
        {
            sklimit=0;
            Sleep(1000);
        }

    }
    if (bRotate == true)
    {
        theta += 0.6;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.6;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if(fanRotate)
    {
        theta2+=2;
        if(theta2 > 360.0)
            theta2 -= 360.0*floor(theta2/360.0);
    }
    glutPostRedisplay();

}

static void idle(void)
{
    glutPostRedisplay();
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Fun Fair");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    //std::cout<<glGetString(GL_VENDOR)<<std::endl;
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //gate
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\fair.bmp");//1
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\exit.bmp");//2
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\welcome.bmp");//3
    //sky drop
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick.bmp");//4
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\brick_w.bmp");//5
    //ice
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice5.bmp");//6
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice6.bmp");//7
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice4.bmp");//8
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\ice3.bmp");//9

    //noodles
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no1.bmp");//10
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no2.bmp");//11
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no3.bmp");//12
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no4.bmp");
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no5.bmp");//13
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\no6.bmp");//14

    //ticket
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\tic1.bmp");//15
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\tic2.bmp");//16
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\tic3.bmp");//17
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\tic4.bmp");//18

    //tree
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\leaf1.bmp");//19
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\leaf2.bmp");//20
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\g2.bmp");//21
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\leaf3.bmp");//22
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\leaf4.bmp");//23
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\l6.bmp");//24
    //sky
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\skf2.bmp");//25
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\sky2.bmp");//26
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\sk3.bmp");//27
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\sk4.bmp");//28
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill.bmp");//29
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill2.bmp");//30
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill3.bmp");//31
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill4.bmp");//32
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill5.bmp");//33
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill6.bmp");//34
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\vill62.bmp");//35
    //fence
    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\fen7.bmp");//36
    //LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\gate.bmp");//37
//    LoadTexture("E:\\4.2\\Lab\\graphics\\graphics project\\fun_fairr\\images\\fen3.bmp");//38

//    glutKeyboardFunc(myKeyboardFunc);
//    glutDisplayFunc(display);
//    glutIdleFunc(animate);
//    glutMainLoop();

    std::cout<<"eyex,centerx increase = d"<<std::endl;
    std::cout<<"eyex,centerx decrease = a"<<std::endl;
    std::cout<<"eyey,centery increase = w"<<std::endl;
    std::cout<<"eyey,centery decrease = s"<<std::endl;
    std::cout<<"roll = i,o"<<std::endl;
    std::cout<<"pitch = r,t"<<std::endl;
    std::cout<<"yaw = y,u"<<std::endl;
    std::cout<<"skydrop=b"<<std::endl;
    std::cout<<"all ferris wheel=j"<<std::endl;
    std::cout<<"swing, hammock,tire=v"<<std::endl;
    std::cout<<"bird view=x"<<std::endl;


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light0();
    //light1();
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc(idle);
    glutIdleFunc(animate);
    glutMainLoop();

    return EXIT_SUCCESS;

    return 0;
}




