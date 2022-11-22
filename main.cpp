#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <ctime>
#include<bits/stdc++.h>

using namespace std;

class BmpLoader
{
    public:
        unsigned char* textureData;
        int iWidth, iHeight;

        BmpLoader(const char*);
        ~BmpLoader();

    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
};

BmpLoader::BmpLoader(const char* filename)
{
    FILE *file=0;
    file=fopen(filename, "rb");
    if(!file)
        cout<<"File not found"<<endl;
    fread(&bfh, sizeof(BITMAPFILEHEADER),1,file);
    if(bfh.bfType != 0x4D42)
        cout<<"Not a valid bitmap"<<endl;
    fread(&bih, sizeof(BITMAPINFOHEADER),1,file);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;
    textureData = new unsigned char[bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(textureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for(int i=0; i<bih.biSizeImage; i+=3)
    {
        temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;

    }

    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}

BmpLoader::~BmpLoader()
{
    delete [] textureData;
}
int fh = 15, fw=50;

double windowHeight=1400, windowWidth=1400;
GLfloat alpha=0.0, theta = 0.0, gamma = 0.0;
GLfloat theta1=0.0, theta2 = 0.0, theta3 = 0.0, theta4 = 0.0;
GLfloat axis_x=0.0, axis_y=0.0, axis_z=0.0;
GLfloat eye_x = fw/2, eye_z = 1.2*fw, eye_y = fh/2;
GLfloat look_x = fw/2, look_y = fh/2, look_z = fw/2;
GLfloat ux = 0, uy = 1, uz = 0;
GLfloat nearPLane = 2, farPlane = 2500;
GLfloat dx, dy, dz, dxyz;
unsigned int ID1[100];

GLboolean bRotate = false, uRotate = false, kRotate = false;
GLboolean fRotate1 = false, fRotate2 = false, fRotate3 = false, fRotate4 = false;

double roll_value = 0.2, pi = acos(-1), cs_angle=cos(pi/180), sn_angle=sin(pi/180);

double scale_x = 1;
double scale_y = 1;
double scale_z = 1;

int tabW = 4;
int tabH = 4;
int tabL = 5;

double dtx = 0;

int l1=0,l2=0,l3=0;

GLfloat ctheta = 0;
GLfloat ctheta1 = 0;

GLboolean cRotate = false;

int fdc=0;
int fdtheta=0;

int fdcl=0;
int fdltheta=0;

double shop1G = 1;
double shop2G = 1;
double Shop3G = 1;
//***me****
GLboolean fan_rotate = true;
GLfloat theta_pakha=0.0;
//***em***


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0}
};

static GLubyte cube_Indices[6][4] =
{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {0, 1, 5, 4},
    {3, 2, 6, 7},
    {0, 3, 7, 4},
    {1, 2, 6, 5}
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

void drawsphere(double x, double y, double z)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { .95, .7, .25, 1.0 };
    GLfloat mat_diffuse[] = { .95, .7, .25, 1.0 };
    GLfloat mat_specular[] = { .95, .7, .25, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (x, y, z);
}

void drawSpehereCustom(double x, double slcs, double stks, GLfloat amx,GLfloat amy,GLfloat amz,GLfloat shine){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { amx,amy,amz, 1.0 };
    GLfloat mat_diffuse[] = { amx,amy,amz, 1.0 };
    GLfloat mat_specular[] = { amx,amy,amz, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (x, slcs, stks);
}

void drawHalfSphere(int scaley, int scalex, GLfloat r,GLfloat rx,GLfloat gx,GLfloat bx) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { rx,bx,gx, 1.0 };
    GLfloat mat_diffuse[] = { rx,bx,gx, 1.0 };
    GLfloat mat_specular[] = { rx,bx,gx, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



   int i, j;
   GLfloat v[scalex*scaley][3];

   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }
//    glColor3f(.8,.8,.8);
   glBegin(GL_QUADS);
//   glColor3f(.8,.8,.8);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
 }

void drawglDisk(GLfloat in_rad,GLfloat rad, GLfloat r,GLfloat g,GLfloat b){
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r,g,b,1 };
    GLfloat mat_diffuse[] = { r,g,b,1 };
    GLfloat mat_specular[] = { r,g,b,1 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    gluDisk(quad, in_rad,rad, 32,32);
}

void drawCylinder(GLfloat in_r,GLfloat out_r,GLfloat h,GLint slcs,GLint stks, GLfloat r,GLfloat g,GLfloat b){
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r,g,b,1 };
    GLfloat mat_diffuse[] = { r,g,b,1 };
    GLfloat mat_specular[] = { r,g,b,1 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    gluCylinder(quad,in_r,out_r,h,slcs,stks);
}

void drawCone(GLfloat rad, GLfloat h, GLint slcs, GLint stks, GLfloat r,GLfloat g,GLfloat b){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r,g,b,1 };
    GLfloat mat_diffuse[] = { r,g,b,1 };
    GLfloat mat_specular[] = { r,g,b,1 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCone(rad, h, slcs, stks);
}

void drawglcube(double x){

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.58,.24,0.23,1 };
    GLfloat mat_diffuse[] = { 0.58,.24,0.23,1 };
    GLfloat mat_specular[] = { 0.58,.24,0.23,1 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCube(x);
}

void drawcube(GLfloat amb_x, GLfloat amb_y, GLfloat amb_z, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { amb_x, amb_y, amb_z, 1 };
    GLfloat mat_diffuse[] = { amb_x, amb_y, amb_z, 1 };
    GLfloat mat_specular[] = { amb_x, amb_y, amb_z, 1 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++){

        getNormal3p(v_cube[cube_Indices[i][0]][0],v_cube[cube_Indices[i][0]][1],v_cube[cube_Indices[i][0]][2],
                    v_cube[cube_Indices[i][1]][0],v_cube[cube_Indices[i][1]][1],v_cube[cube_Indices[i][1]][2],
                    v_cube[cube_Indices[i][2]][0],v_cube[cube_Indices[i][2]][1],v_cube[cube_Indices[i][2]][2]
                    );

        glVertex3fv(&v_cube[cube_Indices[i][0]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_cube[cube_Indices[i][1]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[cube_Indices[i][2]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[cube_Indices[i][3]][0]);glTexCoord2f(0,0);
    }

    glEnd();
}

static void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;
    double PI_ = 3.1416;
   twopi = 2 * PI_;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt/2; j++) {
         for (k = 4; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}

void drawTexSphere(GLfloat in_r, GLfloat r,GLfloat g,GLfloat b){
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r,g,b,1 };
    GLfloat mat_diffuse[] = { r,g,b,1 };
    GLfloat mat_specular[] = { r,g,b,1 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    gluSphere(quad,in_r,32,32);
}

void LoadTexture(const char*filename, int idx)
{
    glGenTextures(1, &ID1[idx]);
    glBindTexture(GL_TEXTURE_2D, ID1[idx]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID1[idx]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void environment(){


///   Back Wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glScalef(fw*5, fh*10, 1);
    glTranslatef(-0.4,0,-7);
    drawcube(.7,.7,.7,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

///    Left side wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glScalef(1, fh*10, fw*3);
    glTranslatef(-100,0,-.046);
    drawcube(.7,.7,.7,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

///    Right Side wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glScalef(1, fh*10, fw*3);
    glTranslatef(150,0,-.046);
    drawcube(.7,.7,.7,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

///    Opposite wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);
    glPushMatrix();
    glScalef(fw*5, fh*10, 1);
    glTranslatef(-.4,0,143);
    drawcube(.7,.7,.7,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

///    Upper Sky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glScalef(fw*5, 1, fw*5);
    glTranslatef(-.4,fh*10,-0.076);
    drawcube(.7,.7,.7,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Surface
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glScalef(fw*5, 0.1, fw*5);
    glTranslatef(-.4,0,-0.076);
    drawcube(.8,.8,.8,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void parking(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 20);
    glPushMatrix();
    glScalef(30, 0.2, 30);
    glTranslatef(1.7,0,.66);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void walklane(){
    glPushMatrix();
    glScalef(60, 0.2, 2.5);
    glTranslatef(0,0,20);
    drawcube(.3,.2,.1,60);
    glPopMatrix();
}

void road(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 21);
    glPushMatrix();
    glScalef(10, 0.2, 100);
    glTranslatef(6,0,.5);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tree()
{
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    ///body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
    glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 2.5, 2.5, 30, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leaf
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    float tx = 0, ty = -10, tz = 0, sx = 1, sy = 1, sz = 1;
    for(int i=0;i<10;i++)
    {
        glPushMatrix();
        glTranslatef(tx,ty,tz);
        glRotatef(-90,1,0,0);
        glScalef(sx, sy, sz);
        gluCylinder(quad, 12-i, 0, 10, 32, 32);
        glPopMatrix();
        ty += 5;// sx -= 0.08;
    }
    glDisable(GL_TEXTURE_2D);
}

void trees(int xgap,int zgap){
    glPushMatrix();
    glScalef(.5,.3, .2);
    glTranslatef(-20-xgap,27,200-zgap);
    tree();
    glPopMatrix();
}

void plantTrees(){
    int xgap = 0;
    int zgap = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            trees(xgap,zgap);
            zgap += 40;
        }
        zgap = 0;
        xgap+=30;
    }

    glPushMatrix();
    glScalef(1,.6, .8);
    glTranslatef(65,30,12);
    tree();
    glPopMatrix();

}

void frontDoor(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    glScalef(fw/3+1, fh, .1);
    glTranslatef(0,0,fw*10);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void frontDoor2(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    glScalef(fw/3+1, fh, .1);
    glTranslatef(2,0,fw*10);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void slideDoor(double dtx){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 23);
    glPushMatrix();
    glScalef(fw/3+1, fh, .1);
    glTranslatef(1+dtx,0,fw*9.96);
    drawcube(.7,.8,.8,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void floor(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glScalef(fw, 0.2, fw);
    drawcube(0.6,0.7,0.6,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void roof(){
    glPushMatrix();
    glScalef(fw, 0.2, fw);
    glTranslatef(0,fh*5,0);
    drawcube(0.2,0.2,0.2,60);
    glPopMatrix();
}

//*******************me*********************
void interactWithwelcome(){

	char str1[] = "You are warmly welcomed!!";
	int l1 = strlen(str1); // see how many characters are in text string.
	glPushMatrix();

//	glColor3f(0.0f, 0.0f, 0.0f);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0,0,0,1 };
    GLfloat mat_diffuse[] = { 00,0,0,1 };
    GLfloat mat_specular[] = { 1,1,1,1 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

	glRasterPos3f(22.2,12.7,48.1); // location to start printing text
	for( int i=0; i < l1; i++) // loop until i is greater then l
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str1[i]);
//		if(str1[i]==' ') delay(1);
		 // Print a character on the screen
	}
	glPopMatrix();
}


void welcome(){

    glPushMatrix();
    glTranslated(23,15,48);
    glRotatef(90,1,0,0);
    drawCylinder(.025,.025,1.8,30,30,0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(27,15,48);
    glRotatef(90,1,0,0);
    drawCylinder(.025,.025,1.8,30,30,0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(22,12.5,48);
    glScalef(6,1,.05);
    drawcube(1,1,.9,60);
    glPopMatrix();
    interactWithwelcome();

}

void water_fall()
{
    ///water
//    glTranslated(0,0,10);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-10,2,50);
    //glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_matt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientt[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusett[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_speculartt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesstt[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusett);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_speculartt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesstt);

    //drawCube();
    GLUquadric *qd1s;
    qd1s = gluNewQuadric();
    gluQuadricTexture(qd1s, TRUE);
    gluDisk(qd1s,0,6.9,100,200);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///waterfall
//    //1
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-10,1.5,52.5);
    glScalef(1, 1, 1);
    glRotatef(90,0,1,0);
    glRotatef(theta_pakha, 0.0, 0.0, 1.0);
    GLfloat no_mat502[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
//
    //2
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-13,1.5,50);
    glScalef(1, 1, 1);
    glRotatef(180,0,1,0);
    glRotatef(-theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
//    //3
//
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-9.5,1.5,46.5);
    glScalef(1, 1, 1);
    glRotatef(270,0,1,0);
    glRotatef(theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
//    //4
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-7,1.5,49.5);
    glScalef(1, 1, 1);
    glRotatef(360,0,1,0);
    glRotatef(-theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //upper layer

    //5
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-12,1.5,51.5);
    glScalef(1, 1, 1);
    glRotatef(45,0,1,0);
    glRotatef(theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
//
//    //6
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-12.5,1.5,48);
    glScalef(1, 1, 1);
    glRotatef(135,0,1,0);
    glRotatef(-theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//////
////    //7
////
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-8,1.5,48);
    glScalef(1, 1, 1);
    glRotatef(225,0,1,0);
    glRotatef(theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
    //8
    glBindTexture(GL_TEXTURE_2D, 49);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-8,1.5,52);
    glScalef(1, 1, 1);
    glRotatef(315,0,1,0);
    glRotatef(-theta_pakha, 0.0, 0.0, 1.0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);


    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,3,3,.5,200,200);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 50);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-10,3,50);
    glScalef(1, 1.5, 1);
    glRotatef(90,1,0,0);
    GLfloat no_mat502s[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502s[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse502s[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular502s[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502s[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *obs = gluNewQuadric();
    gluQuadricTexture(obs, TRUE);
    gluCylinder(obs,1,1,2,20,20);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///waterside
    glBindTexture(GL_TEXTURE_2D, 50);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-10,3,50);
    glScalef(1, 1.5, 1);
    glRotatef(90,1,0,0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

//    GLUquadricObj *obs = gluNewQuadric();
    gluQuadricTexture(obs, TRUE);
    gluCylinder(obs,7,7,2,20,20);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


//**************************em*****************************


void side_wall(double x){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(1.0, fh, fw);
    glTranslatef(0,0,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void right_side_wall(double x){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(1.0, fh, fw);
    glTranslatef(fw,0.0,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void back_wall(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(fw, fh, 1);
    drawcube(0.2,0.2,0.6,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void wallDoor(){
    glPushMatrix();
    glScalef(5, fh, 10);
    drawcube(0.6,0.4,0.3,60);
    glPopMatrix();
}

void divider(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(0.5, fh, 10.0);
    glTranslatef(fw+10,0.0,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
//    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\messy-wall.bmp");
    glPushMatrix();
    glScalef(0.5, fh, 10.0);
    glTranslatef(10,0.0,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void counterFront(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 43);
    glPushMatrix();
    glScalef((fw/2)-3, 6.0, 0.1);
    glTranslatef(0.21,0.0,100);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 45);
    glPushMatrix();
    glScalef((fw/2)-7, 6.0, 0.1);
    glTranslatef(1.65,0.0,100);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void counterTable(){
    glPushMatrix();
    glScalef((fw/2)-7, 0.1, 2);
    glTranslatef(1.65,60.0,5);
    drawcube(0.6,.7,.8,60);
    glPopMatrix();

    glPushMatrix();
    glScalef((fw/2)-3, 0.1, 2);
    glTranslatef(.21,60.0,5);
    drawcube(0.6,.7,.8,60);
    glPopMatrix();
}

void shoptop(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    glScalef(fw/2, 3.0, 0.1);
    glTranslatef(.2,4.0,100);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glPushMatrix();
    glScalef(fw/2-5, 3.0, 0.1);
    glTranslatef(1.5,4.0,100);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void shop3(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(fh-2, fh, 0.5);
    glTranslatef(0,0,32);
    drawcube(0.6,.7,.8,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glScalef(fh-2, fh, 0.5);
    glTranslatef(0,0,72);
    drawcube(0.6,.7,.8,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Counter front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 46);
    glPushMatrix();
    glScalef(0.1 , 6.0,fw/2-8);
    glTranslatef(130,0,2.12);
    glRotatef(90,0,1,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Counter table
    glPushMatrix();
    glScalef(2, 0.1, (fw/2)-8);
    glTranslatef(6.5,60.0,1.145);
    drawcube(0.6,.7,.8,60);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glScalef(0.1, 3.0, fw/2-5);
    glTranslatef(128,4.0,0.82);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

///Chair table set
void table(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);

    glPushMatrix();
    glScalef(tabW,0.2,tabL);
    glTranslatef(11.5,20,8);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.2,tabH,tabL);
    glTranslatef(234,0,8);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.2,tabH,tabL);
    glTranslatef(226+5*tabW,0,8);
    drawcube(1,1,1,60);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///Draw Chair
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);

    glPushMatrix();
    glScalef(5,tabH/2+0.8,tabL);
    glTranslatef(tabW*2,0,8);
    drawcube(1,1,1,60);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///Chair divider
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 16);

    glPushMatrix();
    glScalef(.5,tabH*2/2+0.8,tabL);
    glTranslatef(tabW*2*10+tabW*2/2+0.5,0.5,8);
    drawcube(1,1,1,60);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void tableSet(){
    int tabx = 0;
    int tabz = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            glPushMatrix();
            glTranslatef(tabx,0,tabz);
            table();
            glPopMatrix();
            tabz -= 8;
        }
        tabz = 0;
        tabx-=11.5;
    }
}

/// Basin
void drawBasin(int btx){
    ///Basin Body
    glPushMatrix();
    glColor3f(1,1,1);
    glRotatef(180,0,0,1);
    glTranslatef(-3,-7,39+btx);
    drawHalfSphere(30,20,2,.9,.9,.9);
    glPopMatrix();

    ///Basin Pipe
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(2.8,39+btx,-5);
    gluCylinder(quad, 0.2,0.2,5.2,32,32);
    glPopMatrix();

    ///Water pipe
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(1.5,39+btx,-8);
    gluCylinder(quad, 0.1,0.1,1,32,32);
    glPopMatrix();

    ///Water Pipe 2
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-39-btx,8,1.5);
    gluCylinder(quad, 0.1,0.1,1,32,32);
    glPopMatrix();

    ///Tab regulator
    glPushMatrix();
    glTranslatef(1.5,7.3,39.2+btx);
    glutSolidSphere(.2,32,32);
    glPopMatrix();

    ///Mirror
    glPushMatrix();
    glScalef(.1,4,2);
    glTranslatef(10,2,19+btx/2);
    drawcube(.6,.7,.8,128);
    glPopMatrix();
}

void Basin(){
    int btx = 0;
    for(int i=0;i<3;i++){
        drawBasin(btx);
        btx+=4;
    }
}

/// Fan
void drawfan(){
    glPushMatrix();
    glScalef(4.,.2,0.8);
    drawglcube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.8,.2,4);
    drawglcube(1);
    glPopMatrix();
}

void fan(){
    ///Fan 1
    glPushMatrix();
    glTranslatef(40,13.5,42);
    glRotatef(theta1,0.0,1.0,0.0);
    drawfan();
    glPopMatrix();

    ///Fan holder
    glPushMatrix();
    glScalef(.2,1.5,.2);
    glTranslatef(200,9.33,210);
    drawglcube(1);
    glPopMatrix();

    ///Fan 2
    glPushMatrix();
    glTranslatef(40,13.5,32);
    glRotatef(theta2,0.0,1.0,0.0);
    drawfan();
    glPopMatrix();

    ///Fan holder
    glPushMatrix();
    glScalef(.2,1.5,.2);
    glTranslatef(200,9.33,160);
    drawglcube(1);
    glPopMatrix();

    ///Fan 3
    glPushMatrix();
    glTranslatef(22,13.5,42);
    glRotatef(theta3,0.0,1.0,0.0);
    drawfan();
    glPopMatrix();

    ///Fan holder
    glPushMatrix();
    glScalef(.2,1.5,.2);
    glTranslatef(110,9.33,210);
    drawglcube(1);
    glPopMatrix();

    ///Fan 4
    glPushMatrix();
    glTranslatef(22,13.5,32);
    glRotatef(theta4,0.0,1.0,0.0);
    drawfan();
    glPopMatrix();

    ///Fan holder
    glPushMatrix();
    glScalef(.2,1.5,.2);
    glTranslatef(110,9.33,160);
    drawglcube(1);
    glPopMatrix();
}

/// Clock
void drawclock(int cx){

    glPushMatrix();
    glScalef(.2,cx,.2);
    drawglcube(1);
    glPopMatrix();
}

void Anaclock(){
    ///Minutes Kata
    glPushMatrix();
    glTranslatef(30,10,30.3);
    glRotatef(ctheta,0,0,1);
    glTranslatef(0,2.5,0);
    drawclock(5);
    glPopMatrix();

    ///Hour Kata
    glPushMatrix();
    glTranslatef(30,10,30.2);
    glRotatef(ctheta1,0,0,1);
    glTranslatef(0,1.5,0);
    drawclock(3);
    glPopMatrix();

    ///Background
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glPushMatrix();
    glTranslatef(30,10,30);
    drawglDisk(0,6,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void clockPosition(){
    glPushMatrix();
    glScalef(.3,.3,.3);
    glTranslatef(195,30,95);
    glRotatef(-90,0,1,0);
    Anaclock();
    glPopMatrix();
}

///Shop - 1
void glass(double x, double y){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 29);
    glPushMatrix();
    glTranslatef(32+x,6.5,3-y);
    glRotatef(-90,1,0,0);
    drawCylinder(.3,.4,1,32,32,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glScalef(.5,.1,.1);
    glTranslatef(64.5+x*2,73,30-y*10);
    drawcube(1,1,1,80);
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.6,.1);
    glTranslatef(327+x*10,11.34,30-y*10);
    drawcube(1,1,1,80);
    glPopMatrix();
}

void handlelessGlass(double x, double y, double z){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,30);
    glPushMatrix();
    glTranslatef(32+x,9+z,3-y);
    glRotatef(-90,1,0,0);
    drawCylinder(.3,.4,1,32,32,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pirich(double x,double y){
    glPushMatrix();
    glTranslatef(36,9.3+y,3-x);
    glRotatef(-90,1,0,0);
    drawglDisk(0,.7,.7,.7,.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,37);
    drawCylinder(.7,1.2,.2,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Bottle(double x){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,31);
    glPushMatrix();
    glTranslatef(38.5,9.3,3.4-x);
    glRotatef(-90,1,0,0);
    drawglDisk(0,.7,.1,.1,.1);
    glTranslatef(0,0,.02);
    drawCylinder(.7,.7,1.5,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0,0,1.5);
    drawCylinder(.7,.5,.5,32,32,.6,.9,.6);
    glTranslatef(0,0,.5);
    drawCylinder(.5,.5,.3,32,32,.1,.1,.1);
    glTranslatef(0,0,.3);
    drawglDisk(0,.5,.1,.1,.1);
    glPopMatrix();
}

void cglass()
{
    ///Outer
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,29);
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(90,1,0,0);
    drawCylinder(1.5,1.5,3,32,32,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///inner
    glPushMatrix();
    glRotatef(90,1,0,0);
    drawCylinder(1.48,1.48,3,32,32,1,1,1);
    glPopMatrix();

    ///glass base
    glPushMatrix();
    glTranslated(0,-3,0);
    glRotated(90, 1,0,0);
    drawglDisk(0,1.5,.6,.6,.6);
    glPopMatrix();

    ///glass handle
    glPushMatrix();
    glTranslated(1.5, -1.5, 0);
    glScaled(.8,1,2);
    glRotated(-90,0,0,1);
    torus(20,10);
    glPopMatrix();
}

void drawglass(double x, double y){
    glPushMatrix();
    glScalef(.4,.5,.4);
    glTranslatef(82.5+x,16,7.5+y);
    glRotatef(180,0,1,0);
    cglass();
    glPopMatrix();
}

void coffeeMaker(){
    /// Coffee Maker
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    glPushMatrix();
    glScalef(2,3,2);
    glTranslatef(22.5,2.5,0.6);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glScalef(2,.5,2);
    glTranslatef(22.5,21,0.6);
    drawcube(0.1,.2,.3,60);
    glTranslatef(.75,.4,1.02);
    drawglDisk(0,.1,1,1,1);
    glTranslatef(-.25,0,0);
    drawglDisk(0,.05,1,1,1);
    glTranslatef(-.25,0,0);
    drawglDisk(0,.05,1,1,1);
    glPopMatrix();

    ///Stand
    glPushMatrix();
    glScalef(.2,1.5,2);
    glTranslatef(225,4,0.6);
    drawcube(0.1,.1,.1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,1.5,2);
    glTranslatef(234,4,0.6);
    drawcube(0.1,.1,.1,60);
    glPopMatrix();

    ///Water Pot
    glPushMatrix();
    glTranslatef(46,11.8,2);
    glRotatef(90,1,0,0);
    drawCone(1,1,32,32,.6,.7,.8);
    glTranslatef(0,0,-2);
    drawCylinder(1,1,2,32,32,.6,.7,.8);
    glPopMatrix();

    ///Cup stand
    glPushMatrix();
    glScalef(3,.51,4);
    glTranslatef(14,12,0);
    drawcube(.2,.3,.4,60);
    glPopMatrix();

    ///Pipe
    glPushMatrix();
    glTranslatef(45,8,2.5);
    glRotatef(-90,0,1,0);
    drawCylinder(.13,.05,1.3,32,32,.6,.3,.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(43.7,7.55,2.5);
    glRotatef(-90,1,0,0);
    drawCylinder(.05,.05,.5,32,32,.6,.3,.9);
    glPopMatrix();
}

void shopBasin(){

    glPushMatrix();
    glScalef(1.5,1,1);
    glRotatef(-90,1,0,0);
    drawglDisk(0,1.5,.3,.2,.1);
    drawCylinder(1.5,1.7,1.5,32,32,0.67, 0.71, 0.87);
    glTranslatef(0,0,-6.6);
    drawCylinder(.2,.2,6,32,32,0.68, 0.73, 0.6);
    glTranslatef(0,0,8);
    drawCylinder(.05,.1,.5,32,32,0.67, 0.71, 0.87);
    glTranslatef(0,2,.4);
    glRotatef(90,1,0,0);
    drawCylinder(.1,.1,2.2,32,32,0.68, 0.73, 0.6);
    glTranslatef(0,.25,1.5);
    drawSpehereCustom(.2,32,32,.6,.8,.6,80);
    glPopMatrix();

}

void coffeeShop(){

    ///base table
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glPushMatrix();
    glScalef(20,.5,4);
    glTranslatef(1.5,12,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    ///Nicher dividers
    glPushMatrix();
    glScalef(.5,6,4);
    glTranslatef(70,0,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,6,4);
    glTranslatef(80,0,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,6,4);
    glTranslatef(90,0,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Nicher Doors
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
    glPushMatrix();
    glScalef(4.5,6,.1);
    glTranslatef(6.8,0,40);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.5,6,.1);
    glTranslatef(7.9,0,40);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.5,6,.1);
    glTranslatef(9,0,40);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// Uporer Self
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 28);
    glPushMatrix();
    glScalef(.2,6,4);
    glTranslatef(155,1,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,6,4);
    glTranslatef(200,1,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(9,.2,4);
    glTranslatef(3.46,60,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(9,.2,4);
    glTranslatef(3.46,45,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    coffeeMaker();

    ///Glass objects
    double x = 0;
    double y = 0;

    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            drawglass(x,y);
            x+=4;
        }
        x = 0;
        y -= 3.5;
    }

    double hx = 0;
    double hy = 0;
    double hz = 0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<3;k++){
                handlelessGlass(hx,hy,hz);
                hz+=0.9;
            }
            hz=0;
            hx+=1.4;
        }
        hx = 0;
        hy += 1.4;
    }

    double px=0,py=.5;
    for(int i=0;i<12;i++){
        pirich(py,px);
        px+=.18;
    }

    Bottle(0);
    Bottle(1.4);

    ///Right Wall Base Table
    glPushMatrix();
    glScalef(4,.5,5);
    glTranslatef(11.4,12,0.8);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    drawcube(1,1,1,60);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    ///Basin
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(6.5,6.6,-48);
    shopBasin();
    glPopMatrix();

}

///Shop - 2
void iceCreamBox(){
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,2,.2,.2,.2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,32);
    drawCylinder(2,2,2,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0,0,2);
    drawglDisk(0,2,.2,.2,.2);
    glPopMatrix();
}

void juiceBottle(){

    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,2,.1,.2,.2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,33);
    drawCylinder(2,2,3,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0,0,3);
    drawCylinder(2,.5,1.5,32,32,.7,.9,.7);
    glTranslatef(0,0,1.5);
    drawCylinder(.5,.5,.5,32,32,.1,.2,.2);
    glTranslatef(0,0,.5);
    drawglDisk(0,.5,.1,.1,.1);
    glPopMatrix();

}

void fridgeDoorLower(){
    ///Lower Door
    glPushMatrix();
    glScalef(5.2,4,.2);
    glTranslatef(0,0,14);
    drawcube(.816,.29,.171,80);
    glPopMatrix();
    ///Handle
    glPushMatrix();
    glScalef(.1,1,.1);
    glTranslatef(4,2.8,31);
    drawcube(.1,.1,.1,80);
    glPopMatrix();
}

void fridgeDoorUpper(){
    /// Upper Door
    glPushMatrix();
    glScalef(5.2,3.7,.2);
    glTranslatef(0,1.14,14);
    drawcube(.816,.29,.171,80);
    glPopMatrix();
    ///Handle
    glPushMatrix();
    glScalef(.1,1,.1);
    glTranslatef(4,5.8,31);
    drawcube(.1,.1,.1,80);
    glPopMatrix();

}

void fridge(){
    ///Base
    glPushMatrix();
    glScalef(5.2,.3,3);
    drawcube(.8,.8,.8,80);
    glPopMatrix();
    ///Section divider
    glPushMatrix();
    glScalef(5.1,.3,3);
    glTranslatef(0,13.33,0);
    drawcube(.41,.48,.43,80);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.1,.1,2.95);
    glTranslatef(0,28,0);
    drawcube(.41,.48,.43,80);
    glPopMatrix();

    /// Cone Ice-Cream
    double icex = 0;
    double icez = 0;
    for(int i=0;i<9;i++){
        for(int j=0;j<2;j++){
            glPushMatrix();
            glTranslatef(.5+icex,3.2,2.2-icez);
            glRotated(20,1,0,0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,47);
            drawCylinder(.3,0,.7,32,32,1,1,1);
            drawglDisk(0,.3,1,1,1);
            glDisable(GL_TEXTURE_2D);
//            drawCone(.3,.7,32,32,1,1,1);
            glPopMatrix();
            icez += .8;
        }
        icez = 0;
        icex += .5;
    }

    ///Back
    glPushMatrix();
    glScalef(5,8,.2);
    drawcube(.41,.48,.43,80);
    glPopMatrix();
    ///Left
    glPushMatrix();
    glScalef(.2,8,3);
    drawcube(.65,.48,.44,80);
    glPopMatrix();
    ///Right
    glPushMatrix();
    glScalef(.2,8,3);
    glTranslatef(25,0,0);
    drawcube(.65,.48,.44,80);
    glPopMatrix();
    ///Top
    glPushMatrix();
    glScalef(5.2,.3,3);
    glTranslatef(0,26.6,0);
    drawcube(.2,.2,.8,80);
    glPopMatrix();
    ///Icecream Box
    double ix=0,iy=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            glPushMatrix();
            glScalef(.3,.3,.3);
            glTranslatef(14-ix,14+iy,7);
            iceCreamBox();
            glPopMatrix();
            ix+=3.9;
        }
        ix = 0;
        iy += 2.1;
    }
    ///Juice Bottle
    double bx=0,bz=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<9;j++){
            glPushMatrix();
            glScalef(.1,.4,.1);
            glTranslatef(45-bx,1,26-bz);
            juiceBottle();
            glPopMatrix();
            bx+=5;
        }
        bx = 0;
        bz += 5;
    }

    ///Door control
    glPushMatrix();
    glRotatef(fdltheta,0,1,0);
    glTranslatef(-2*fdcl*2.6,0,fdcl*2.1);
    fridgeDoorLower();
    glPopMatrix();

    glPushMatrix();
    glRotatef(fdtheta,0,1,0);
    glTranslatef(-2*fdc*2.6,0,fdc*2.1);
    fridgeDoorUpper();
    glPopMatrix();
}

void iceCreamGlass(){
    glPushMatrix();
    glTranslatef(25,5,35);
    glRotatef(90,1,0,0);
    drawglDisk(0,2,.93,.91,.91);
    drawCylinder(.1,.1,2,32,32,.898,.85,.85);
    glTranslatef(0,0,2);
    glScalef(1,1,2);
    drawCylinder(.1,2,2,32,32,0.85,.55,.55);
    glPopMatrix();
}

void drawIceCreamGlass(double x,double y){
    glPushMatrix();
    glScalef(.3,.4,.3);
    glRotatef(180,1,0,0);
    glTranslatef(106-x,-28.1,-42-y);
    iceCreamGlass();
    glPopMatrix();
}

void iceglass()
{
    ///Outer
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,38);
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(90,1,0,0);
    drawCylinder(1.5,1.5,3,32,32,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///inner
    glPushMatrix();
    glRotatef(90,1,0,0);
    drawCylinder(1.48,1.48,3,32,32,1,1,1);
    glPopMatrix();

    ///glass base
    glPushMatrix();
    glTranslated(0,-3,0);
    glRotated(90, 1,0,0);
    drawglDisk(0,1.5,.6,.6,.6);
    glPopMatrix();

    ///glass handle
    glPushMatrix();
    glTranslated(1.5, -1.5, 0);
    glScaled(.8,1,2);
    glRotated(-90,0,0,1);
    torus(20,10);
    glPopMatrix();
}

void iceGlass(double x, double y){
    glPushMatrix();
    glScalef(.4,.5,.4);
    glTranslatef(82.5+x,16,7.5+y);
    glRotatef(180,0,1,0);
    iceglass();
    glPopMatrix();
}

void iceHandlelessGlass(double x, double y, double z){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,39);
    glPushMatrix();
    glTranslatef(32.5+x,9+z,3-y);
    glRotatef(-90,1,0,0);
    drawCylinder(.3,.4,1,32,32,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void iceCreamShopRak(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,36);
    glPushMatrix();
    glScalef(.2,6,4);
    glTranslatef(155,1,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,6,4);
    glTranslatef(200,1,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(9,.2,4);
    glTranslatef(3.46,60,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(9,.2,4);
    glTranslatef(3.46,45,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Glass objects
    double x = 0;
    double y = 0;

    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            iceGlass(x,y);
            x+=4;
        }
        x = 0;
        y -= 3.5;
    }

    double hx = 0;
    double hy = 0;
    double hz = 0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<3;k++){
                iceHandlelessGlass(hx,hy,hz);
                hz+=0.9;
            }
            hz=0;
            hx+=1.4;
        }
        hx = 0;
        hx = 0;
        hy += 1.4;
    }

    double px=0,py=.5;
    for(int i=0;i<12;i++){
        pirich(py,px);
        px+=.18;
    }
    double ggx=0,ggy=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            drawIceCreamGlass(ggx,ggy);
            ggx+=5;
        }
        ggx = 0;
        ggy+= 4;
    }
}

void iceCreamMaker(){
    glPushMatrix();
    glScaled(4,2,2);
    drawcube(.3,.1,.6,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2);
    glScaled(4,1,2);
    drawcube(.3,.1,.6,100);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 48);
    glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(4,8,2);
    drawcube(1,1,1,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(4,1,4);
    drawcube(.2,.2,.1,100);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 48);
    glPushMatrix();
    glTranslatef(0,5,2);
    glScalef(4,5,2);
    drawcube(1,1,1,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(2,5,3.5);
    glRotatef(90,1,0,0);
    drawCylinder(.3,.1,.3,32,32,.8,.9,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,4.8,3.5);
    glRotatef(90,1,0,0);
    drawCylinder(.1,.1,.5,32,32,.9,.8,.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.3,10.2,4.04);
    glScalef(.5,0.5,0.05);
    drawcube(1,1,1,100);
    glPopMatrix();
}

void iceCreamwithGlass(){

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawglDisk(0,.9,1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,.2,0);
    glRotatef(90,1,0,0);
    drawCylinder(1,0.9,.2,32,32,.2,.6,.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.4,.3,.4);
    drawTexSphere(.3,0.906,0.238,0.19);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,.3,.4);
    drawTexSphere(.3,0.92,0.41,0.19);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.4,.3,0);
    drawTexSphere(.3,0.89,0.167,0.31);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,.3,0);
    drawTexSphere(.3,0.738,0.125,0.125);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7,.08,-.2);
    glScalef(.2,.05,.7);
    drawcube(.1,.1,.1,100);
    glPopMatrix();
}

void icecreamJuiceShop(){
    glPushMatrix();
    glScalef(1,1.3,1);
    glTranslatef(6.5,0.3,.7);
    fridge();
    glPopMatrix();

    ///Back Wall Base Table
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,35);
    glPushMatrix();
    glScalef(20,.5,4);
    glTranslatef(.6,12,0);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Right Wall Base Table
    glPushMatrix();
    glScalef(4,.5,5);
    glTranslatef(6.5,12,0.8);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,35);
    drawcube(1,1,1,60);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    ///Ice Cream Shop Rak
    glPushMatrix();
    glScalef(.8,1,1);
    glTranslatef(37,0,-31);
    glRotatef(-90,0,1,0);
    iceCreamShopRak();
    glPopMatrix();

    /// Ice Cream Shop Basin
    glPushMatrix();
    glTranslatef(22,6.6,2.8);
    shopBasin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,6.6,1.8);
    glScalef(.5,.4,.4);
    iceCreamMaker();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,6.12,11);
    iceCreamwithGlass();
    glPopMatrix();

}


///Shop-3
void chineseShopGlass(){
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,.5,.3,.7,.1);
    drawCylinder(.5,.7,2,32,32,0.78,0.77,0.887);
    glPopMatrix();
}

void chineseShopGamla(){
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,1,.3,.7,.1);
    drawCylinder(1,1.2,1,32,32,.57,.11,.11);
    glPopMatrix();
}

void chineseShopPlate(){
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,1,.7,.7,.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,42);
    drawCylinder(1,1.4,.3,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void chineseShopTray(){
    glPushMatrix();
    glScalef(1,.4,.02);
    drawcube(.7,.7,.8,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,.4,.02);
    glTranslatef(0,0,50);
    drawcube(.7,.7,.8,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(.02,.3,1);
    drawcube(.7,.7,.8,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(.02,.3,1);
    glTranslatef(50,0,0);
    drawcube(.7,.7,.8,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,.1,1);
    drawcube(.3,.7,.6,70);
    glPopMatrix();

}

void Pizza(){
    glPushMatrix();
    glRotatef(90,1,0,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,44);
    drawCylinder(1,1,.4,32,32,1,1,1);
    drawglDisk(0,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void cokeBottle(){
    glPushMatrix();
    glRotatef(-90,1,0,0);
    drawglDisk(0,2,.1,.2,.2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,34);
    drawCylinder(2,2,3,32,32,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0,0,3);
    drawCylinder(2,.5,1.5,32,32,.7,.9,.7);
    glTranslatef(0,0,1.5);
    drawCylinder(.5,.5,.5,32,32,.1,.2,.2);
    glTranslatef(0,0,.5);
    drawglDisk(0,.5,.1,.1,.1);
    glPopMatrix();
}

void frenchFries(){
    glPushMatrix();
    glScalef(.05,.05,.4);
    drawcube(0.98,0.59,0.01,70);
    glPopMatrix();
}

void korai(){
    ///Body
    glPushMatrix();
    glTranslatef(23,4.65,33);
    glRotatef(-180,1,0,0);
    drawHalfSphere(32,32,.8,.1,.9,.9);
    glPopMatrix();

    ///Handle
    glPushMatrix();
    glTranslatef(21.4,4.53,33);
    glScalef(.8,.1,.1);
    drawcube(1,1,.5,80);
    glPopMatrix();
//
    ///Body
    glPushMatrix();
    glTranslatef(26,4.65,33);
    glRotatef(-180,1,0,0);
    drawHalfSphere(32,32,.8,.1,.9,.9);
    glPopMatrix();

    ///handle
    glPushMatrix();
    glTranslatef(26.8,4.53,33);
    glScalef(.8,.1,.1);
    drawcube(1,1,.5,80);
    glPopMatrix();
}

void gasStove(){
    ///Stove Body
    glPushMatrix();
    glScalef(7,.5,1.5);
    glTranslatef(3,6.5,21.33);
    drawcube(.23,.27,.25,60);
    glPopMatrix();
    ///Stand
    glPushMatrix();
    glTranslatef(23,4,33);
    glRotatef(90,1,0,0);
    drawCylinder(.5,.5,.2,32,32,1,1,1);
    glPopMatrix();
    ///Stand
    glPushMatrix();
    glTranslatef(26,4,33);
    glRotatef(90,1,0,0);
    drawCylinder(.5,.5,.2,32,32,1,1,1);
    glPopMatrix();
    ///Switch
    glPushMatrix();
    glTranslatef(23,3.35,33.5);
    glScalef(.05,.3,.1);
    drawcube(1,1,1,60);
    glPopMatrix();
    ///Switch
    glPushMatrix();
    glTranslatef(26,3.35,33.5);
    glScalef(.05,.3,.1);
    drawcube(1,1,1,60);
    glPopMatrix();

    ///Korai
    glPushMatrix();
    korai();
    glPopMatrix();
}

void fastFoodShop(){

    ///Base Table
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 41);
    glPushMatrix();
    glScalef(4,.5,20);
    glTranslatef(.1,12,0.8);
    drawcube(1,1,1,80);
    glPopMatrix();

    ///Back wall base
    glPushMatrix();
    glScalef(10,.5,4);
    glTranslatef(.1,12,4.1);
    drawcube(1,1,1,80);
    glPopMatrix();

    ///Front wall base
    glPushMatrix();
    glScalef(11,.5,4);
    glTranslatef(.11,12,8);
    drawcube(1,1,1,80);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Shop Basin
    glPushMatrix();
    glTranslatef(6.2,6.65,18.2);
    shopBasin();
    glPopMatrix();

    ///Shop Rak
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,40);
    glPushMatrix();
    glScalef(4,.5,10);
    glTranslatef(.1,18,2.6);
    drawcube(1,1,1,60);
    glTranslatef(0,6,0);
    drawcube(1,1,1,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(4,6.5,.5);
    glTranslatef(.1,0.96,26*2);
    drawcube(1,1,1,60);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// Gas Stove
    glPushMatrix();
    glTranslatef(33,3.5,67);
    glRotatef(180,0,1,0);
    gasStove();
    glPopMatrix();

    /// Glass Positioning
    double glsx = 0;
    double glsy = 0;
    double glsz = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<6;k++){
                glPushMatrix();
                glScalef(.5,.5,.5);
                glTranslatef(7-glsx,19.3+glsy,55+glsz);
                chineseShopGlass();
                glPopMatrix();
                glsy += .5;
            }
            glsy = 0;
            glsz += 1.5;
        }
        glsy = 0;
        glsz = 0;
        glsx += 1.5;
    }

    /// Plate Positioning
    double pltx = 0;
    for(int i=0;i<10;i++){
        glPushMatrix();
        glScalef(.8,.8,1.6);
        glTranslatef(3.3,12+pltx,20.38);
        chineseShopPlate();
        glPopMatrix();
        pltx += .25;
    }

    /// Gamla Positioning
    double gamx = 0;
    for(int i=0;i<2;i++){
        glPushMatrix();
        glScalef(1.5,1.8,1.5);
        glTranslatef(2,3.67,19+gamx);
        chineseShopGamla();
        glPopMatrix();
        gamx += 2.5;
    }

    /// Tray Positioning
    glPushMatrix();
    glScalef(3,.5,4);
    glTranslatef(.4,13.212,5.2);
    chineseShopTray();
    glPopMatrix();

    ///Pizza Positioning
    glPushMatrix();
    glScalef(1,.5,1);
    glTranslatef(2.5,14,22);
    Pizza();
    glPopMatrix();

    /// Glass Position on Plate
    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(4,13.5,47.5);
    chineseShopGlass();
    glPopMatrix();

    /// CokeBottle Position
    glPushMatrix();
    glScalef(.2,.6,.2);
    glTranslatef(14,11.25,118.75);
    cokeBottle();
    glPopMatrix();

    ///Fries Positioning
    glPushMatrix();
    glTranslatef(3.7,6.80,23.55);
    frenchFries();
    glTranslatef(-.3,0,0);
    glRotatef(30,0,1,0);
    frenchFries();
    glRotatef(30,0,1,0);
    frenchFries();
    glTranslatef(.3,0,0);
    glRotatef(30,0,1,0);
    frenchFries();
    glTranslatef(.1,0,0);
    glRotatef(20,0,1,0);
    frenchFries();
    glTranslatef(0,0,.1);
    glRotatef(-50,0,1,0);
    frenchFries();
    glTranslatef(.1,0,.2);
    glRotatef(-20,0,1,0);
    frenchFries();
    glPopMatrix();

}

void Shop1SlidingGate(){
    glPushMatrix();
    glScalef(24.8,shop1G,.5);
    glTranslatef(.21,(14+1-shop1G)/shop1G,18);
    drawcube(0.59,0.63,0.7,80);
    glPopMatrix();
}

void Shop2SlidingGate(){
    glPushMatrix();
    glScalef(19.3,shop2G,.5);
    glTranslatef(1.59,(14+1-shop2G)/shop2G,18);
    drawcube(0.63,0.55,0.48,80);
    glPopMatrix();
}

void Shop3SlidingGate(){
    glPushMatrix();
    glScalef(.5,Shop3G,20);
    glTranslatef(24,(14+1-Shop3G)/Shop3G,.8);
    drawcube(0.62,0.54,0.57,60);
    glPopMatrix();
}

///////////////////// Light Area  ////////////////////////////

void sun(){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { .95, .7, .25, 1.0 };
    GLfloat mat_diffuse[] = { .95, .7, .25, 1.0 };
    GLfloat mat_specular[] = { .95, .7, .25, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glPushMatrix();
    glTranslatef(30,73,-6.5);
    glutSolidSphere (1.5, 100, 80);
    glPopMatrix();

    GLfloat no_light[] = {0.0,0.0,0.0,1.0};
    GLfloat light_ambient[]  = { .296, .2764, .288, 1.0};
    GLfloat light_diffuse[]  = { .296, .2764, .288, 1.0 };
    GLfloat light_specular[] = { 1, 1, 1, 1.0 };
    GLfloat light_position[] = { 30, 65, 15, 1.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
//    glEnable(GL_LIGHT0);
}

void tubelight_roof_1(){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {120};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslatef(28,14.7,40);
    glRotatef(90,0,1,0);
    gluCylinder(quad,.3,.3,6,32,32);
    glPopMatrix();

    GLfloat no_light[] = {0.0,0.0,0.0,1.0};
    GLfloat light_ambient[]  = { .296, .2764, .288, 1.0};
    GLfloat light_diffuse[]  = { .296, .2764, .288, 1.0};
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = { 28, 14, 40, 1.0};

    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
//    glEnable(GL_LIGHT1);
}

void tubelight_roof_2(){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {120};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslatef(28,14.7,25);
    glRotatef(90,0,1,0);
    gluCylinder(quad,.3,.3,6,32,32);
    glPopMatrix();

    GLfloat no_light[] = {0.0,0.0,0.0,1.0};
    GLfloat light_ambient[]  = { .296, .2764, .288, 1.0};
    GLfloat light_diffuse[]  = { .296, .2764, .288, 1.0};
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = { 28, 14, 25, 1.0};

    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
}

/////////// Draw Everything /////////////////////

void drawFoodCourt(){
    floor();
    roof();
    //*****me****
    glPushMatrix();
    glTranslated(-5,0,-2);
    water_fall();
    glPopMatrix();
    welcome();
    //****me*****
    side_wall(-fw/2);
    right_side_wall(fw/2);
    back_wall();
    divider();
    counterFront();
    shoptop();
    counterTable();
    shop3();
    coffeeShop();
    icecreamJuiceShop();
    fastFoodShop();
    Shop1SlidingGate();
    Shop2SlidingGate();
    Shop3SlidingGate();
    fan();
    Basin();
    environment();
    frontDoor();
    frontDoor2();
    slideDoor(dtx);
    tableSet();
    clockPosition();
    plantTrees();
    parking();
    walklane();
    road();
    sun();
    tubelight_roof_1();
    tubelight_roof_2();


}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, nearPLane, farPlane);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eye_x,eye_y,eye_z, look_x,look_y,look_z, ux,uy,uz);
    glViewport(0, -300, windowHeight, windowWidth);
    glScalef(scale_x, scale_y, scale_z);

    drawFoodCourt();

    glFlush();
    glutSwapBuffers();
}

/////////// Actions ///////////////

void Yaw_y1(){
    GLfloat tx, tz;

    tx = look_x - eye_x;
    tz = look_z - eye_z;

    dx = tx*cs_angle+tz*sn_angle;
    dz = -tx*sn_angle+tz*cs_angle;

    look_x = dx + eye_x;
    look_z = dz + eye_z;

}

void Yaw_y2(){
    GLfloat tx, tz;

    tx = look_x - eye_x;
    tz = look_z - eye_z;

    dx = tx*cs_angle-tz*sn_angle;
    dz = tx*sn_angle+tz*cs_angle;

    look_x = dx + eye_x;
    look_z = dz + eye_z;
}

void Pitch_y1(){
    GLfloat ty, tz;

    ty = look_y - eye_y;
    tz = look_z - eye_z;

    dy = ty*cs_angle-tz*sn_angle;
    dz = ty*sn_angle+tz*cs_angle;

    look_y = dy + eye_y;
    look_z = dz + eye_z;
}

void Pitch_y2(){
    GLfloat ty, tz;

    ty = look_y - eye_y;
    tz = look_z - eye_z;

    dy = ty*cs_angle+tz*sn_angle;
    dz = -ty*sn_angle+tz*cs_angle;

    look_y = dy + eye_y;
    look_z = dz + eye_z;

}

void Roll_y1(){
    dx = ux*cs_angle-uy*sn_angle;
    dy = ux*sn_angle+uy*cs_angle;

    ux = dx;
    uy = dy;
}

void Roll_y2(){
    dx = ux*cs_angle+uy*sn_angle;
    dy = -ux*sn_angle+uy*cs_angle;

    ux = dx;
    uy = dy;
}

void rotation_eye_right()
{
    eye_x-=look_x;
    eye_z-=look_z;

    float r = sqrt(eye_x*eye_x + eye_z*eye_z);
    float theta_rad = atan(eye_z/eye_x);
    float conv = 180/3.1416;
    float theta_degree = theta_rad*conv;

    if(eye_x < 0 ) theta_degree +=180;

    theta_degree+=1;
    theta_rad = theta_degree/conv;

    eye_x = r*cos(theta_rad);
    eye_z = r*sin(theta_rad);

    eye_x+=look_x;
    eye_z+=look_z;

}

void rotation_eye_left()
{
    eye_x-=look_x;
    eye_z-=look_z;

    float r = sqrt(eye_x*eye_x + eye_z*eye_z);
    float theta_rad = atan(eye_z/eye_x);
    float conv = 180/3.1416;
    float theta_degree = theta_rad*conv;

    if(eye_x < 0 ) theta_degree +=180;

    theta_degree-=1;
    theta_rad = theta_degree/conv;

    eye_x = r*cos(theta_rad);
    eye_z = r*sin(theta_rad);

    eye_x+=look_x;
    eye_z+=look_z;

}

void unitZoomIn(){
    dx = eye_x-look_x;
    dy = eye_y-look_y;
    dz = eye_z-look_z;
    dxyz = sqrt(dx*dx+dy*dy+dz*dz);
    eye_x-=(dx/dxyz);
    eye_y-=(dy/dxyz);
    eye_z-=(dz/dxyz);
    look_x-=(dx/dxyz);
    look_y-=(dy/dxyz);
    look_z-=(dz/dxyz);
}

void unitZoomOut(){
    dx = eye_x-look_x;
    dy = eye_y-look_y;
    dz = eye_z-look_z;
    dxyz = sqrt(dx*dx+dy*dy+dz*dz);
    eye_x+=(dx/dxyz);
    eye_y+=(dy/dxyz);
    eye_z+=(dz/dxyz);
    look_x+=(dx/dxyz);
    look_y+=(dy/dxyz);
    look_z+=(dz/dxyz);
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'l':
        if(l1==1)
        {
//            printf("Sun light off\n");
            l1=0;
            glDisable(GL_LIGHT0);
        }
        else
        {
//            printf("Sun light on\n");
            l1=1;
            glEnable(GL_LIGHT0);
        }
        glutPostRedisplay();
        break;
    case 'k':
        if(l2==1)
        {
//            printf("Roof light-1 off\n");
            l2=0;
            glDisable(GL_LIGHT1);
        }
        else
        {
//            printf("Roof light-1 on\n");
            l2=1;
            glEnable(GL_LIGHT1);
        }
        glutPostRedisplay();
        break;
    case 'j':
        if(l3==1)
        {
//            printf("Roof light-2 off\n");
            l3=0;
            glDisable(GL_LIGHT2);
        }
        else
        {
//            printf("Roof light-2 on\n");
            l3=1;
            glEnable(GL_LIGHT2);
        }
        glutPostRedisplay();
        break;
    case '0':
        cRotate = !cRotate;
        break;
    case '1':
        fRotate1 = !fRotate1;
        break;
    case '2':
        fRotate2 = !fRotate2;
        break;
    case '3':
        fRotate3 = !fRotate3;
        break;
    case '4':
        fRotate4 = !fRotate4;
        break;
    case '5':
        Pitch_y1();
        break;
    case '%':
        Pitch_y2();
        break;
    case '6':
        Yaw_y1();
        break;
    case '^':
        Yaw_y2();
        break;
    case '7':
        Roll_y1();
        break;
    case '&':
        Roll_y2();
        break;
    case 'Z':
        unitZoomOut();
        break;

    case 'z':
        unitZoomIn();
        break;

    case 'x':
        nearPLane+=0.2;
        break;
    case 'X':
        nearPLane-=.2;
        break;
    case 'C': //zoom in
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;
    case 'c': //zoom out
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'v':
        eye_y++;
        look_y++;
        break;
    case 'V':
        eye_y--;
        look_y--;
        break;

    case 'b':
        eye_x++;
        look_x++;
        break;
    case 'B':
        eye_x--;
        look_x--;
        break;
    case 'n':
        eye_z++;
        look_z++;
        break;
    case 'N':
        eye_z--;
        look_z--;
        break;
    case 'h':
        if(dtx<1){
            slideDoor(dtx+=0.02);
//            cout<<dtx<<endl;
        }
        break;
    case 'H':
        if(dtx>0){
            slideDoor(dtx-=0.02);
//            cout<<dtx<<endl;
        }
        break;
    case 'g':
        if(!fdcl){
            fdcl=1;
            fdltheta = 90;
        }
        else{
            fdcl=0;
            fdltheta = 0;
        }
        break;
    case 'G':
        if(!fdc){
            fdc = 1;
            fdtheta = 90;
        }
        else{
            fdc = 0;
            fdtheta = 0;
        }
        break;
    case 'f':
        if(shop2G<15){
            shop2G += 0.5;
            Shop2SlidingGate();
//            cout<<shop1G<<endl;
        }
        break;
    case 'F':
        if(shop2G>1){
            shop2G -= 0.5;
            Shop2SlidingGate();
//            cout<<shop1G<<endl;
        }
        break;
    case 'd':
        if(shop1G<15){
            shop1G += 0.5;
            Shop1SlidingGate();
//            cout<<shop2G<<endl;
        }
        break;
    case 'D':
        if(shop1G>1){
            shop1G -= 0.5;
            Shop1SlidingGate();
//            cout<<shop1G<<endl;
        }
        break;
    case 's':
        if(Shop3G<15){
            Shop3G += 0.5;
            Shop3SlidingGate();
//            cout<<shop2G<<endl;
        }
        break;
    case 'S':
        if(Shop3G>1){
            Shop3G -= 0.5;
            Shop3SlidingGate();
//            cout<<shop1G<<endl;
        }
        break;
    }
}

void animate()
{
    if (fan_rotate == true)
    {
        theta_pakha += 10.0;
        if(theta_pakha > 360) theta_pakha = 0.0;
    }
    if (fRotate1 == true)
    {
        theta1 += 20;
        if(theta1 > 360.0)
            theta1 -= 360.0*floor(theta1/360.0);
    }
    if (fRotate2 == true)
    {
        theta2 += 20;
        if(theta2 > 360.0)
            theta2 -= 360.0*floor(theta2/360.0);
    }
    if (fRotate3 == true)
    {
        theta3 += 20;
        if(theta3 > 360.0)
            theta3 -= 360.0*floor(theta3/360.0);
    }
    if (fRotate4 == true)
    {
        theta4 += 20;
        if(theta4 > 360.0)
            theta4 -= 360.0*floor(theta4/360.0);
    }

    if (cRotate == true)
    {
        time_t result = time(0);
        struct tm * timeinfo;
        timeinfo = localtime(&result);
//        cout<<timeinfo->tm_hour<<" "<<timeinfo->tm_min<<endl;
        int m,h;
        m = timeinfo->tm_min;
        h = timeinfo->tm_hour >= 12? timeinfo->tm_hour-12:timeinfo->tm_hour;
        ctheta = -timeinfo->tm_min*6;
        ctheta1 = -timeinfo->tm_hour*30-timeinfo->tm_min*.5;
    }
    glutPostRedisplay();

}

void showMenu(){
    printf("1. Zoom in-out by unit vector - z\n");
    printf("2. Zoom in-out by near plane - x\n");
    printf("3. Zoom in-out by Scaling - c\n");
    printf("4. Y-axis movement - v\n");
    printf("5. X-axis movement - b\n");
    printf("6. Z-axis movement - n\n");
    printf("7. Sun light on-off - l\n");
    printf("8. Roof light-1 on-off - k\n");
    printf("9. Roof light-2 on-off - j\n");
    printf("10. Fan-1 on-off - 1\n");
    printf("11. Fan-2 on-off - 2\n");
    printf("12. Fan-3 on-off - 3\n");
    printf("13. Fan-4 on-off - 4\n");
    printf("14. Pitch movement - 5\n");
    printf("15. Yaw movement - 6\n");
    printf("16. Roll movement - 7\n");
    printf("17. Door open-close - h\n");
    printf("18. Fridge Lower Door open-close - g\n");
    printf("19. Fridge Upper Door open-close - G\n");
    printf("20. Coffee Shop Door open - F\n");
    printf("21. Coffee Shop Door close - f\n");
    printf("22. Ice-Cream Shop Door open - D\n");
    printf("23. Ice-Cream Shop Door close - d\n");
    printf("24. FastFood Shop Door close - S\n");
    printf("25. FastFood Shop Door close - s\n");
}

void textures(){
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sky.bmp",1);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\foodcourtbanner.bmp",2);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\floor.bmp",3);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\messy-wall.bmp",4);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\kshelf.bmp",5);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\permian.bmp",6);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\Thai2.bmp",7);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chinese.bmp",8);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sky2.bmp",9);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sky3.bmp",10);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sky4.bmp",11);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sky5.bmp",12);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\grass.bmp",13);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\table.bmp",14);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chair.bmp",15);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chair-div.bmp",16);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\grass3.bmp",17);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\treebody2.bmp",18);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\leaves.bmp",19);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\parking.bmp",20);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\road.bmp",21);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\walklane.bmp",22);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\closed.bmp",23);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\clock.bmp",24);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\coffeemaker.bmp",25);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\coffeetable.bmp",26);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\cdoor.bmp",27);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\cshelf.bmp",28);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\cglass2.bmp",29);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chglass.bmp",30);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\ccookies.bmp",31);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\icecreambox.bmp",32);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\pepsi.bmp",33);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\sprite.bmp",34);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\icecreambase.bmp",35);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\icerak.bmp",36);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\plate.bmp",37);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\iceglass1.bmp",38);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\iceglass2.bmp",39);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chineseRak.bmp",40);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chineseBase.bmp",41);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chinesePlate.bmp",42);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\juicebarbanner.bmp",43);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\pizzaside.bmp",44);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\coffeebanner.bmp",45);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\chinesebanner.bmp",46);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\coneicecream.bmp",47);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\icecreammaker.bmp",48);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\water.bmp",49);
    LoadTexture("D:\\Academic\\4th Year\\2k17\\4-2\\CSE 4208\\Project\\FoodCourt\\poolside.bmp",50);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("FoodCourt");

    /// Instructions
    showMenu();
    /// Load Texture Files
    textures();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
