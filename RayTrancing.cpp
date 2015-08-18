#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "perspectiveCamera.h"
#include "csphere.h"
#include "intersectresult.h"
#include "plane.h"
#include "union.h"
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
GLFWwindow* window;
using namespace std;
void initScene(int w, int h)
{
	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	// 黑色背景
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// 设置深度缓存
	glClearDepth(1.0);
	// 启用深度测试
	glEnable(GL_DEPTH_TEST);
	// 所作深度测试的类型
	glDepthFunc(GL_LEQUAL);
	// 告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

Color rayTraceRecursive(CObject* scene, CRay& ray, long maxReflect) {
	IntersectResult result = scene->isIntersected(ray);

	if (result.isHit){
		float reflectiveness = result.object->material->getRef();
		Color color = result.object->material->sample(ray, result.position, result.normal);
		//color = color.multiply(1 - reflectiveness);
		color = color.multiply(1-reflectiveness);
		if (reflectiveness>0 && (maxReflect > 0)) {
			GVector3 r = result.normal*(-2 * result.normal.dotMul(ray.getDirection())) + ray.getDirection();
			CRay ray1 = CRay(result.position, r);
			Color reflectedColor = rayTraceRecursive(scene, ray1, maxReflect - 1);
			color = color.add(reflectedColor.multiply(reflectiveness));
		}
		return color;
	}
	else{
		return Color::blue();

	}
}
void renderUnion()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	//glTranslatef(-0.5f, -0.5f, -1.0f);
	//glPointSize(2.0);
	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);
	plane1->material = new CheckerMaterial(0.1f,0.2);
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16,0.25f);
	sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16,0.25f);
	Union scence;
	scence.push(plane1);
    scence.push(sphere1);
	scence.push(sphere2);
	long maxDepth = 20;

	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	//float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scence.isIntersected(ray);
		
	
			//IntersectResult result = plane1.isIntersected(ray);
			if (result.isHit )
			{
				//cout << result.object->material;
				//result.object->show();
				Color color = result.object->material->sample(ray, result.position, result.normal);
	            
				//Color color = plane1->material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.r * 255, color.g * 255, color.b * 255);
				glVertex2f(sx * 2 - 1.0, sy * 2 - 1.0);
			}
		}
	}
	glEnd();
	// 交换缓冲区
	glfwSwapBuffers(window);
}
void renderRecursive()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	//glTranslatef(-0.5f, -0.5f, -1.0f);
	//glPointSize(2.0);
	PerspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -2), 4.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -7), 3.0);
	plane1->material = new CheckerMaterial(0.1f,0.5f);
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16,0.25);
	sphere2->material = new PhongMaterial(Color::green(), Color::white(), 16,0.25);
	/*Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);
	plane1->material = new CheckerMaterial(0.1f,0.5f);
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16,0.25);
	sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16,0.25);*/

	Union scene;
	scene.push(plane1);
	scene.push(sphere1);
	scene.push(sphere2);
	long maxDepth = 20;
	long maxReflect = 5;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scene.isIntersected(ray);
			if (result.isHit)
			{
				Color color = rayTraceRecursive(&scene, ray, 5);
				//Color color = result.object->material->sample(ray, result.position, result.normal);
				//Color color =plane1.material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.r * 255, color.g * 255, color.b * 255);
				glVertex2f(sx*2-1.0, sy*2-1.0);
			}
		}
	}
	glEnd();
	// 交换缓冲区
	glfwSwapBuffers(window);
}


int main(void)
{
	//记录程序运行状态


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//initScene(WINDOW_WIDTH, WINDOW_HEIGHT);
	//主循环
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT);
		renderRecursive();

	}
	glfwTerminate();
	//退出程序
	exit(EXIT_SUCCESS);
}
