
#include <Windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include<GL/glut.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <glaux.h>
#include <glut.h>
#include <glu.h>

#define TEXTURE_NUM 1
#pragma comment (lib, "winmm")
#define SOUND_NAME "you.wav"

GLuint texture[TEXTURE_NUM];

char texture_name[TEXTURE_NUM][20]={"christmas.bmp"};
float g_fDistance = -4.5f;
float g_fSpinX    = 0.0f;
float g_fSpinY    = 0.0f;


static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;


void SetupRC(); 
void RenderScene(void);
void ChangeSize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void KeyboardSpe(int key, int x, int y);
void Time(int sec);
void MenuFunc(int button);
void MyMouse(int button, int state, int x, int y);
void MyMotion(int x, int y);

float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;
float yRevolution = 0.0f, zoomIn = -300 , zoomIn1 = 0;
float red = 0, green = 0, blue = 0;
float snowObejct[100][3];
float snowColor[100][3];
float snowDrop[1000][3];
void drop();
int mode = 1, snowNumber = 0;
int ballNumber = 0;
int LoadGLTextures();
GLUquadricObj *quadratic;

void coordinate();//좌표축
void rotationShpere();//자전 구
void tree();
void snow();
void color();

void InitGL() {
     GLfloat Light0_Ambient[]={ 0.5f, 0.5f, 0.5f, 1.0f };
     GLfloat Light0_Diffuse[]={ 1.0f, 1.0f, 1.0f, 1.0f };
     GLfloat Light0_Position[]={ 0.0f, 0.0f, 2.0f, 1.0f };

     glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
     glLightfv(GL_LIGHT0, GL_POSITION,Light0_Position);

     LoadGLTextures();

     glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glClearDepth(1.0f);
     glDepthFunc(GL_LEQUAL);
     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_TEXTURE_2D);
     glShadeModel(GL_SMOOTH);

     quadratic=gluNewQuadric();
     gluQuadricNormals(quadratic, GLU_SMOOTH);
     gluQuadricTexture(quadratic, GL_TRUE);

     glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowPosition(100, 100); 
   glutInitWindowSize(500, 500); 
     InitGL();
   glutCreateWindow("2017648052 손민지");
  
   glutReshapeFunc(ChangeSize);
   glutDisplayFunc(RenderScene);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(KeyboardSpe);
   glutTimerFunc(100, Time, 1);
   SetupRC();
   glutMouseFunc(MyMouse);
   glutMotionFunc(MyMotion);
    LoadGLTextures();

   
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0); 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
   

   glDisable(GL_TEXTURE_GEN_S);
     glDisable(GL_TEXTURE_GEN_T);


   glutMainLoop();
   return 0;
}

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   srand((unsigned)time(NULL));
   for (int i = 0; i < 100; ++i)
   {
      snowObejct[i][0] = rand() % (100 - (-100) + 1) + (-100);//x값
      snowObejct[i][1] = rand() % 150;
      snowObejct[i][2] = rand() % (100 - (-100) + 1) + (-100);//x값
      snowColor[i][0] = rand() % 10 * 0.1;//r
      snowColor[i][1] = rand() % 10 * 0.1;//g
      snowColor[i][3] = rand() % 10 * 0.1;//b
   }
}
void RenderScene()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glPushMatrix();
   glTranslated(0.0, 0.0, zoomIn);
   glTranslated(zoomIn1 ,0.0 , 0.0);
  
   glRotated(xRotation, 1.0f, 0.0f, 0.0f);
   glRotated(yRotation, 0.0f, 1.0f, 0.0f);
   glRotated(zRotation, 0.0f, 0.0f, 1.0f);
   glPushMatrix();
   glTranslatef(0.0f, -50.0f, 0.0f);
   glColor3f(0.5f, 0.5f, 0.5f);
   glBegin(GL_POLYGON);
   glVertex3f(-100.0f, 0.0f, 100.0f);
   glVertex3f(100.0f, 0.0f, 100.0f);
   glVertex3f(100.0f, 0.0f, -100.0f);
   glVertex3f(-100.0f, 0.0f, -100.0f);
   glEnd();
   glPopMatrix();
   for (int i = 0; i <= snowNumber; ++i)
   {
      glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      glTranslated(snowDrop[i][0], -49.0f, snowDrop[i][2]);
      glutSolidSphere(2, 10, 10);
      glPopMatrix();
   }
   snow();
   tree();
   

   rotationShpere();
   glPopMatrix();
   glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   
   case 'x':
      xRotation += 3.0f;
      break;
   case 'y':
      yRotation += 3.0f;
      break;
   case 'z':
      zRotation += 3.0f;
      break;
     
   case '1':
      mode = 1;
      break;
   case '2':
      mode = 2;
      break;

   case '3':
      mode = 3;
      break;
   case ';':
      yRevolution += 3.0;
      break;
   }
   glutPostRedisplay();
}
void KeyboardSpe(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_LEFT:
      zoomIn1++;
      break;
   case GLUT_KEY_UP:
      zoomIn++;
      break;
   case GLUT_KEY_RIGHT:
      zoomIn1--;
      break;
   case GLUT_KEY_DOWN:
      zoomIn--;
      break;
   }
   glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
   GLfloat nRange = 250.0f;
 
   if (h == 0)
      h = 1;
   
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   if (w <= h)
      glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
   else
      glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
   float fAspect;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   fAspect = (float)w / (float)h;
   gluPerspective(45.0, fAspect, 1.0, 500.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
GLvoid Time(int sec)
{
   color();
   drop();
   yRevolution += 9.0f;
   glutPostRedisplay();
   glutTimerFunc(100, Time, 1);
}

void rotationShpere()
{
   glRotated(yRevolution, 0.0f, 1.0f, 0.0f);
   glPushMatrix();//왼쪽 상자
   glTranslatef(17.0f, 45.0f, 15.0f);
   glColor3f(0.0f, 1.0f, 0.0f);

   if (mode == 1) {

      //눈사람 눈
      glColor3f(0.0f, 0.0f, 0.0f);
      glutSolidSphere(5, 20, 20);

      glColor3f(0.0f, 0.0f, 0.0f);
      glTranslatef(-18.0f, 0.0f, 8.0f);
      glutSolidSphere(5, 20, 20);

      //코 만들기
      glRotatef(30, 0, 1, 0);
      glTranslatef(10.0f, -8.0f, 0.0f);
      glColor3f(1.0f, 0.5f, 0.4f);
      glutSolidCone(5, 30, 20, 20);

      //왼쪽팔
      glRotatef(-150, 1, 0, 0);
      glTranslatef(35.0f, 15.0f, 0.0f);
      glColor3f(0.698039f, 0.163333f, 0.163333f);
      glScalef(1.0, 5.0, 0.8);
      glutSolidCube(8.0);

      glTranslatef(-65.0f, 0.0f, 0.0f);
      glColor3f(0.698039f, 0.163333f, 0.163333f);
      glScalef(1.0, 1.0, 0.8);
      glutSolidCube(8.0);

      glPopMatrix();
      glColor3f(0.0f, 0.0f, 0.0f);
      glTranslatef(10.0f, 0.0f, 35.0f);
      glutSolidSphere(5, 20, 20);

      glTranslatef(0.0f, -15.0f, 2.0f);
      glutSolidSphere(5, 20, 20);
      glPushMatrix();
      glPopMatrix();


   }

   else if (mode == 2) {


      glTranslatef(0.0f, 5.0f, 0.0f);
      //앞쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 10.0f, 20.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-20.0f, 10.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 50.0f, 0.0f);
      glEnd();
      //앞쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 10.0f, 20.0f);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(20.0f, 10.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 50.0f, 0.0f);
      glEnd();
      //뒷쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(20.0f, 10.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 10.0f, -20.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 50.0f, 0.0f);
      glEnd();
      //뒷쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 10.0f, -20.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-20.0f, 10.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 50.0f, 0.0f);
      glEnd();


      //두번째 파라미터
      glTranslatef(0.0f, -40.0f, 0.0f);
      //앞쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 20.0f, 40.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-40.0f, 20.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 70.0f, 0.0f);
      glEnd();
      //앞쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 20.0f, 40.0f);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(40.0f, 20.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 70.0f, 0.0f);
      glEnd();
      //뒷쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(40.0f, 20.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 20.0f, -40.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 70.0f, 0.0f);
      glEnd();
      //뒷쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 20.0f, -40.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-40.0f, 20.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 70.0f, 0.0f);
      glEnd();

      //세번째 파라미터
      glTranslatef(0.0f, -90.0f, 0.0f);
      //앞쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 60.0f, 70.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-70.0f, 60.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 130.0f, 0.0f);
      glEnd();
      //앞쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 0.0f);//그린
      glVertex3f(0.0f, 60.0f, 70.0f);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(70.0f, 60.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 130.0f, 0.0f);
      glEnd();
      //뒷쪽1
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(1.0f, 0.0f, 1.0f);//마젠타
      glVertex3f(70.0f, 60.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 60.0f, -70.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 130.0f, 0.0f);
      glEnd();
      //뒷쪽2
      glBegin(GL_TRIANGLE_STRIP);
      glColor3f(0.0f, 1.0f, 1.0f);//시안
      glVertex3f(0.0f, 60.0f, -70.0f);
      glColor3f(0.0f, 0.0f, 1.0f);//블루
      glVertex3f(-70.0f, 60.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);//레드
      glVertex3f(0.0f, 130.0f, 0.0f);
      glEnd();


      glTranslatef(0.0f, 40.0f, 0.0f);
      glColor3f(0.698039f, 0.163333f, 0.163333f);
      glScalef(3.0, 5.5, 3.0);
      glutSolidCube(6.5);

      glTranslatef(0.0f, 25.0f, 0.0f);
      glColor3f(1.0, 1.0, 0.0);
      glutSolidSphere(2.0, 30, 50);

      glPopMatrix();

   }
   else if (mode == 3) {
   glColor3f(1.0, 1.0, 1.0);
 
   glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
    glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f, -30.0f,  30.0f);      // 앞면
   glTexCoord2f(0.33f, 0.0f); glVertex3f( 30.0f, -30.0f,  30.0f);
   glTexCoord2f(0.33f, 0.5f); glVertex3f( 30.0f,  30.0f,  30.0f);
   glTexCoord2f(0.0f, 0.5f); glVertex3f(-30.0f,  30.0f,  30.0f);

   glTexCoord2f(0.34f, 0.0f); glVertex3f( 30.0f, -30.0f, -30.0f);
   glTexCoord2f(0.684f, 0.0f); glVertex3f(-30.0f, -30.0f, -30.0f);      // 뒷면
   glTexCoord2f(0.684f, 0.5f); glVertex3f(-30.0f,  30.0f, -30.0f);
   glTexCoord2f(0.34f, 0.5f); glVertex3f( 30.0f,  30.0f, -30.0f);

   glTexCoord2f(0.685f, 0.0f); glVertex3f(-30.0f,  30.0f,  30.0f);      // 윗면
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 30.0f,  30.0f,  30.0f);
   glTexCoord2f(1.0f, 0.51f); glVertex3f( 30.0f,  30.0f, -30.0f);
   glTexCoord2f(0.685f, 0.51f); glVertex3f(-30.0f,  30.0f, -30.0f);      

   glTexCoord2f(0.0f, 0.51f); glVertex3f(-30.0f, -30.0f, -30.0f);      // 아랫면
   glTexCoord2f(0.336f, 0.51f); glVertex3f( 30.0f, -30.0f, -30.0f);
   glTexCoord2f(0.336f, 1.0f); glVertex3f( 30.0f, -30.0f,  30.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, -30.0f,  30.0f);

   glTexCoord2f(0.34f, 0.51f); glVertex3f( 30.0f, -30.0f,  30.0f);      // 우측면
   glTexCoord2f(0.683f, 0.51f); glVertex3f( 30.0f, -30.0f, -30.0f);   
   glTexCoord2f(0.683f, 1.0f); glVertex3f( 30.0f,  30.0f, -30.0f);
   glTexCoord2f(0.34f, 1.0f); glVertex3f( 30.0f,  30.0f,  30.0f);

   glTexCoord2f(0.685f, 0.51f); glVertex3f(-30.0f, -30.0f, -30.0f);   // 좌측면
   glTexCoord2f(1.0f, 0.51f); glVertex3f(-30.0f, -30.0f,  30.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-30.0f,  30.0f,  30.0f);
   glTexCoord2f(0.685f, 1.0f); glVertex3f(-30.0f,  30.0f, -30.0f);
    glEnd();
  
   glPopMatrix();
   }
   

}
AUX_RGBImageRec * LoadBMP(char *Filename){
    FILE * File = NULL;
    if(!Filename) return NULL;        // 파일이름이 전달되었는지 확인
    File = fopen(Filename,"r");
    if(File) {            // 파일이 존재하는가?
        fclose(File);     // 핸들을 닫음
        return auxDIBImageLoad(Filename);        // 파일로부터 메모리로
    }
    return NULL;        // 로딩이 실패하면 NULL을 반환
}

int LoadGLTextures(){                                   // 파일을 로드하고 텍스쳐로 변환
   int Status = TRUE, i;
   AUX_RGBImageRec *TextureImage;

   
   for(i=0;i<TEXTURE_NUM;i++) {
     TextureImage=NULL;
     if (TextureImage=LoadBMP(texture_name[i])) {
          glGenTextures(1, &texture[i]);
          glBindTexture(GL_TEXTURE_2D, texture[i]);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);// 선형 필터링
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);// 선형 필터링
          glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY,
                         0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
     } else {
          MessageBox(NULL,"Image file has a error !",texture_name[i],MB_ICONERROR);
          Status=false;
     }

     if (TextureImage) {            // 텍스처가 존재하는지 확인
          if (TextureImage->data) free(TextureImage->data);// 텍스처 이미지가 존재하는지 확인
          free(TextureImage);// 이미지 구조체를 해제
     }
   }
   return Status;         // Status를 반환
   
}


void MyMouse(int button, int state, int x, int y) {
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            ptLastMousePosit.x = ptCurrentMousePosit.x = x;
            ptLastMousePosit.y = ptCurrentMousePosit.y = y;
            bMousing = true;
       } else 
         bMousing = false;
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         break;
      default:
         break;
   }

   glutPostRedisplay();
}

void MyMotion(int x, int y) {
   ptCurrentMousePosit.x = x;
    ptCurrentMousePosit.y = y;

    if( bMousing )
    {
      g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
        g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
    }

    ptLastMousePosit.x = ptCurrentMousePosit.x;
    ptLastMousePosit.y = ptCurrentMousePosit.y;

    glutPostRedisplay();
}


void tree()
{
   if (mode == 1) {
      PlaySound(TEXT(SOUND_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
      glPushMatrix();//왼쪽 상자
      glTranslatef(0.0f, -10.0f, 0.0f);
      glColor3f(1.0, 1.0, 1.0);
      glutSolidSphere(40, 100, 100);
      glTranslatef(0.0f, 50.0f, 0.0f);
      glColor3f(1.0, 1.0, 1.0);
      glutSolidSphere(25, 100, 100);

      glPushMatrix();//왼쪽 상자
      //눈사람 모자
      glTranslatef(0.0f, 12.0f, 0.0f);
      glColor3f(1.0, 0.0, 0.0);
      glRotatef(-90, 1, 0, 0);
      glutSolidCone(25, 30, 20, 20);

      //눈사람 모자위 장식
      glTranslatef(0.0f, 0.0f, 32.0f);
      glColor3f(1.0, 1.0, 1.0);
      glutSolidSphere(6, 30, 20);
      glPopMatrix();
      glPopMatrix();
   }

}
void snow()
{
   for (int i = 0; i < 100; ++i)
   {
      glPushMatrix();
      glColor3f(snowColor[i][0], snowColor[i][1], snowColor[i][2]);
      glTranslatef(snowObejct[i][0], snowObejct[i][1], snowObejct[i][2]);
      glutSolidSphere(2, 10, 10);
      glPopMatrix();
   }
}
void color()
{
   for (int i = 0; i < 100; ++i)
   {
      snowColor[i][0] += 0.1;
      if (snowColor[i][0] > 1)
      {
         snowColor[i][0] = 0;
         snowColor[i][1] += 0.1;
      }
      if (snowColor[i][1] > 1)
      {
         snowColor[i][1] = 0;
         snowColor[i][2] += 0.1;
      }
      if (snowColor[i][2] > 1)
         snowColor[i][2] = 0;
   }
}
void drop()
{
   for (int i = 0; i < 100; ++i)
   {
      snowObejct[i][1] -= 1;
   }
   for (int i = 0; i < 100; ++i)
   {
      if (snowObejct[i][1] < -50)
      {
         snowDrop[snowNumber][0] = snowObejct[i][0];
         snowDrop[snowNumber][2] = snowObejct[i][2];
         snowObejct[i][0] = rand() % (100 - (-100) + 1) + (-100);//x값
         snowObejct[i][1] = rand() % 150;//y값
         snowObejct[i][2] = rand() % (100 - (-100) + 1) + (-100);//x값
         if (snowNumber < 1000)
            snowNumber++;
      }
   }
}
