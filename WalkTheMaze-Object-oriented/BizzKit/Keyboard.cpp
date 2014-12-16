#include "Keyboard.h"

extern Status *status;
extern Model *model;

void Keyboard::keyboard(unsigned char key, int x, int y){
    
    switch (key){
        case 27:
            exit(0);
            break;
        case 'h':
        case 'H':
            Keyboard::help();
            break;
        case 'l':
        case 'L':
            if (status->lightViewer)
                status->lightViewer = 0;
            else
                status->lightViewer = 1;
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, status->lightViewer);
            glutPostRedisplay();
            break;
        case 'k':
        case 'K':
            status->light = !status->light;
            glutPostRedisplay();
            break;
        case 'w':
        case 'W':
            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutPostRedisplay();
            break;
        case 'p':
        case 'P':
            glDisable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glutPostRedisplay();
            break;
        case 's':
        case 'S':
            glEnable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glutPostRedisplay();
            break;
        case 'c':
        case 'C':
            if (glIsEnabled(GL_CULL_FACE))
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
            glutPostRedisplay();
            break;
        case 'n':
        case 'N':
            status->apresentaNormais = !status->apresentaNormais;
            glutPostRedisplay();
            break;
        case 'i':
        case 'I':
            status = new Status();
            model = new Model();
            glutPostRedisplay();
            break;
        case 'o':
        case 'O':
            status->tecla_o = !status->tecla_o;
            break;
    }
}

void Keyboard::Special(int key, int x, int y){
    
    switch (key){
        case GLUT_KEY_F1:
            gravaGrafo();
            break;
        case GLUT_KEY_F2:
            leGrafo();
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_F6:
            numNos = numArcos = 0;
            addNo(criaNo(0, 10, 0));  // 0
            addNo(criaNo(0, 5, 0));  // 1
            addNo(criaNo(-5, 5, 0));  // 2
            addNo(criaNo(5, 5, 0));  // 3
            addNo(criaNo(-5, 0, 0));  // 4
            addNo(criaNo(5, 0, 0));  // 5
            addNo(criaNo(-5, -5, 0));  // 6
            addArco(criaArco(0, 1, 1, 1));  // 0 - 1
            addArco(criaArco(1, 2, 1, 1));  // 1 - 2
            addArco(criaArco(1, 3, 1, 1));  // 1 - 3
            addArco(criaArco(2, 4, 1, 1));  // 2 - 4
            addArco(criaArco(3, 5, 1, 1));  // 3 - 5
            addArco(criaArco(4, 5, 1, 1));  // 4 - 5
            addArco(criaArco(4, 6, 1, 1));  // 4 - 6
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            status->camera->dist -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            status->camera->dist += 1;
            glutPostRedisplay();
            break;
    }
}

void Keyboard::help(void){
    printf("\n\nDesenho de um labirinto a partir de um grafo\n");
    printf("h,H - Ajuda \n");
    printf("i,I - Reset dos Valores \n");
    printf("******* Diversos ******* \n");
    printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
    printf("k,K - Alerna luz de camera com luz global \n");
    printf("s,S - PolygonMode Fill \n");
    printf("w,W - PolygonMode Wireframe \n");
    printf("p,P - PolygonMode Point \n");
    printf("c,C - Liga/Desliga Cull Face \n");
    printf("n,N - Liga/Desliga apresentaÁ„o das normais \n");
    printf("******* grafos ******* \n");
    printf("F1  - Grava grafo do ficheiro \n");
    printf("F2  - LÍ grafo para ficheiro \n");
    printf("F6  - Cria novo grafo\n");
    printf("******* Camera ******* \n");
    printf("Bot„o esquerdo - Arrastar os eixos (centro da camera)\n");
    printf("Bot„o direito  - Rodar camera\n");
    printf("Bot„o direito com CTRL - Zoom-in/out\n");
    printf("PAGE_UP, PAGE_DOWN - Altera dist‚ncia da camara \n");
    printf("ESC - Sair\n");
}
