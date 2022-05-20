#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO;//глобальная переменная для хранения указателя на буфер фершин

static void RenderSceneCB()//функция отображения на экран
{
    glClear(GL_COLOR_BUFFER_BIT);//очистка буфера кадра

    glEnableVertexAttribArray(0);//включение индексации атрибутов каждой вершины
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//обратно привязываем наш буфер, приготавливая его для отрисовки
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//вызов говорит контейнеру как воспринимать данные внутри буфера

    glDrawArrays(GL_TRIANGLES, 0, 3);//функция для отрисовки, порядковая

    glDisableVertexAttribArray(0);//отключаем каждый атрибут вершины

    glutSwapBuffers();//функция просит GLUT поменять фоновый буфер и буфер кадра местами
}


static void InitializeGlutCallbacks()//функция обратного вызова
{
    glutDisplayFunc(RenderSceneCB);//отрисовка 1 кадра
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3]; //массив из тех вершин
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);//функция для генерации обьектов переменных типов. первый параметр- кол-во обьектов для создания
    //2- ссылка на массив типа GLuints для хранения указателя 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//функция для указания задачи использования буферов
    //Параметр GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);//вызов принимает название цели, размер данных в байт,
    //адрес массива вершин, и флаг,обозначающий исп-е паттернов для этих данных
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);//инициализируем GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//настраиваем 2 опции. Первая включает двойную буферизацию
    //(отрисовка будет происходить в фоновый буфер, в то время как другой буфер отображается). Вторая-буфер цвета
    glutInitWindowSize(1024, 768);//создаем окно и задаем ему параметры
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Создание треугольника");//заголовок окна

    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();//инициализируем GLEW
    if (res != GLEW_OK) { //и проверяем на ошибки
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//вызов, устанавливает цвет, использующийся во время очистки буфера кадра

    CreateVertexBuffer();

    glutMainLoop();//вызов передаёт контроль GLUT'у

    return 0;
}
