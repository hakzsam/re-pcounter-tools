#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/glut.h>

/**
 * This test program experiments counts points, lines, triangles, primitives
 * and primitives culled. It should return the following results :
 *
 *  - setup_primitive_count: 100000 (ie. setup_point_count + setup_line_count +
 *                                   setup_triangle_count)
 *  - setup_point_count: 20000
 *  - setup_line_count: 32000
 *  - setup_triangle_count: 48000
 *  - setup_primitive_culled_count: 48000
 */

#define POINT_COUNT     20000
#define LINE_COUNT      32000
#define TRIANGLE_COUNT  48000

static void test_setup_point_count()
{
    int i;

    glBegin(GL_POINTS);
    for (i = 0; i < POINT_COUNT; ++i)
        glVertex2i(0, 0);
    glEnd();
}

static void test_setup_line_count()
{
    int i;

    glBegin(GL_LINES);
    for (i = 0; i < LINE_COUNT; ++i) {
        glVertex2i(0, 0);
        glVertex2i(1, 1);
    }
    glEnd();
}

static void test_setup_triangle_count()
{
    int i;

    glBegin(GL_TRIANGLES);
    for (i = 0; i < TRIANGLE_COUNT; ++i) {
        glVertex2i(0, 0);
        glVertex2i(1, 0);
        glVertex2i(0, 1);
    }
    glEnd();
}

static void test_setup_primitive_culled_count()
{
    glEnable(GL_CULL_FACE);
    test_setup_triangle_count(); /* This is just an example... */
    glDisable(GL_CULL_FACE);
}

static void run_tests()
{
    test_setup_point_count();
    test_setup_line_count();
    test_setup_triangle_count();
    test_setup_primitive_culled_count();
}

char* LoadSource(const char *filename)
{
    char *src = NULL;   /* code source de notre shader */
    FILE *fp = NULL;    /* fichier */
    long size;          /* taille du fichier */
    long i;             /* compteur */


    /* on ouvre le fichier */
    fp = fopen(filename, "r");
    /* on verifie si l'ouverture a echoue */
    if(fp == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
        return NULL;
    }

    /* on recupere la longueur du fichier */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    /* on se replace au debut du fichier */
    rewind(fp);

    /* on alloue de la memoire pour y placer notre code source */
    src = malloc(size+1); /* +1 pour le caractere de fin de chaine '\0' */
    if(src == NULL)
    {
        fclose(fp);
        fprintf(stderr, "erreur d'allocation de memoire!\n");
        return NULL;
    }

    /* lecture du fichier */
    for(i=0; i<size; i++)
        src[i] = fgetc(fp);

    /* on place le dernier caractere a '\0' */
    src[size] = '\0';

    fclose(fp);

    return src;
}

static GLuint load_fragment_shader(const char *filename)
{
    GLint status = GL_TRUE;
    char *src = NULL;
    GLuint shader;

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (shader == 0) {
        fprintf(stderr, "Cannot create a fragment shader!\n");
        return 0;
    }

    src = LoadSource(filename);
    if (!src) {
        fprintf(stderr, "Cannot load '%s'!\n", filename);
        glDeleteShader(shader);
        return 0;
    }

    glShaderSource(shader, 1, (const GLchar **)&src, NULL);
    glCompileShader(shader);
    free(src);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLsizei logsize = 0;
        char *log = NULL;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        log = malloc(logsize + 1);
        if (!log) {
            fprintf(stderr, "Cannot allocate memory!\n");
            return 0;
        }
        memset(log, '\0', logsize + 1);

        glGetShaderInfoLog(shader, logsize, &logsize, log);
        fprintf(stderr, "Cannot compile the shader '%s' : %s\n", filename, log);

        free(log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static int my_shader()
{
    GLint compile_status = GL_TRUE;
    GLuint shader;

    shader = load_fragment_shader("my_pixel_shader.txt");
    if (!shader)
        return -1;

    /* Create the program. */
    GLuint program;
    program = glCreateProgram();

    /* Attach the shader. */
    glAttachShader(program, shader);

    /* Link the program. */
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        fprintf(stderr, "Cannot link the program\n,");
        return -1;
    }

    glUseProgram(program);
    return 0;
}

static void idle()
{
    /* Only draw one frame per sec. */
    sleep(1);

    /* Draw the current frame. */
    glutPostRedisplay ();
}

static void reshape(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w / h, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

    run_tests();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("NVIDIA SETUP signals test");

    /* Init GLEW. */
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(ret));
        return 1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    my_shader();

    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
