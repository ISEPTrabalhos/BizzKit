#include "Keyboard.h"
#include "Login.h"
#include "ServicesHandler.h"
#include "MainCharacter.h"
#include "EnemyCharacter.h"
#include "Door.h"
#include "Graphics.h"

extern Status *status;
extern Model *model;
extern MainCharacter *character;
extern EnemyCharacter *enemy;
extern Door *door1;

void Keyboard::loginKeyboard(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	if (status->nextInput) { // enter in passwod
		if (key == 13) {
			Login *login = new Login();
			int id = login->LoginUser(status->username, status->password);
			int x = 1;
			if (true || id >= 1) { // valid user // for testing purpose replace by 'true' and press ENTER twice
				status->loggedIn = true;
				Keyboard::help();
			}
			else {
				status->username = "";
				status->password = "";
				status->passwd = "";
				status->nextInput = false;
				status->loginErrorMessage = "Invalid user, try again !!";
			}
		}
		else if (key == 8) { // backspace
			status->password.pop_back();
			status->passwd.pop_back();
		}
		else {
			if (key > 33 && key < 126) {
				status->password.push_back(key);
				status->passwd.push_back('*');
			}
		}
	}
	else {
		if (key == 13) {  // enter in username 
			status->nextInput = true; // go to password
		}
		else if (key == 8) { // backspace
			status->username.pop_back();
		}
		else {
			if (key > 33 && key < 126) {
				status->username.push_back(key);
			}
		}
	}

	glutPostRedisplay();

}
void Keyboard::keyboardUp(unsigned char key, int x, int y){
	switch (key) {
	case ' ':
		status->attacking = GL_FALSE;
		break;
	}
}

void Keyboard::keyboard(unsigned char key, int x, int y){
	if (status->loggedIn) {
		// in case wordls menu is visible
		if (status->showMapMenu) {
			switch (key) {
			case'1':
				status->mapfile = "mundo1.grafo";
				leGrafo(status->mapfile);
				status->showMapMenu = false;
				status->mainMenu = false;
				break;
			case '2':
				status->mapfile = "quarto1.grafo";
				leGrafo(status->mapfile);
				status->showMapMenu = false;
				status->mainMenu = false;
				break;
			case '0':
				status->showMapMenu = false;
				status->mainMenu = true;
				break;
			}
		}
		else if (status->showSoundsMenu) {
			switch (key) {
			case '0':
				status->showSoundsMenu = false;
				status->mainMenu = true;
				break;
			}
			int option = key - 48; // convert key
			if (option > 0 && option <= status->soundsList.size()) {
				ServicesHandler *handler = new ServicesHandler();
				//handler->saveSound(status->soundsList.at(option-1));
				status->showSoundsMenu = false;
				Graphics::createTextures(model->texID);
			}
		}
		else if (status->showTexturesMenu) {
			switch (key) {
			case '0':
				status->showTexturesMenu = false;
				status->mainMenu = true;
				break;
			}
			int option = key - 48; // convert key
			if (option > 0 && option <= status->texturesList.size()) {
				ServicesHandler *handler = new ServicesHandler();
				//handler->saveTexture(status->texturesList.at(option-1));
				status->showTexturesMenu = false;
				Graphics::createTextures(model->texID);
			}
		}
		else {
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
				if (status->mainMenu && status->finished == false) {
					status->mainMenu = false;
				}
				else {
					if (glIsEnabled(GL_CULL_FACE))
						glDisable(GL_CULL_FACE);
					else
						glEnable(GL_CULL_FACE);
					glutPostRedisplay();
					break;
				}

			case 'n':
			case 'N':
				if (status->mainMenu) {
					//INICIAR NOVO JOGO
					status->setDefaults();
					model->setDefaults();
					character->setDefaults();
					enemy->setDefaults();
					door1->setDefaults(15, 290);
					status->mainMenu = false;
				}
				else {
					status->apresentaNormais = !status->apresentaNormais;
					glutPostRedisplay();
				}
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
			case 'm':
			case 'M':
				//status->showMapMenu = !status->showMapMenu;
				status->snow = GL_FALSE;
				status->mainMenu = !status->mainMenu;
				break;
			case 'd':
			case 'D':
				status->daynight = GL_FALSE;
				if (status->main_light == white_light) {
					status->main_light = (GLfloat*)night_light;
				}
				else {
					status->main_light = (GLfloat*)white_light;
				}
				break;
			case '1':
				status->showMapMenu = true;
				status->showSoundsMenu = false;
				status->showTexturesMenu = false;
				break;
			case '2':
				status->showSoundsMenu = true;
				status->showMapMenu = false;
				status->showTexturesMenu = false;
				break;
			case '3':
				status->showTexturesMenu = !status->showTexturesMenu;
				status->showSoundsMenu = false;
				status->showMapMenu = false;
				break;
			case '4':
				if (!status->mainMenu) {
					status->snow = !status->snow;
				}
				break;
			case '5':
				if (!status->mainMenu) {
					status->rain = !status->rain;
				}
				break;

			case 'F':
			case 'f':
				status->spotlight = !status->spotlight;
				break;
			case ' ':
				status->attacking = GL_TRUE;
				break;
			}
		}
	}
	else {
		loginKeyboard(key, x, y);
	}
}

void Keyboard::specialKeyUp(int key, int x, int y)
{
	if (status->loggedIn) {
		switch (key)
		{
			//	case 'o':
			//	case 'O':
			//		status->tecla_o = AL_FALSE;
			//		break;

		case GLUT_KEY_UP: {
			status->up = GL_FALSE;
			string novo = "(" + to_string((int)character->position->x) + "," + to_string((int)character->position->y) + "," + to_string((int)character->position->y) + "),";
			status->gameRoute += novo;
			break;
		}
		case GLUT_KEY_DOWN:
			status->down = GL_FALSE;
			break;
		case GLUT_KEY_LEFT:
			status->left = GL_FALSE;
			break;
		case GLUT_KEY_RIGHT:
			status->right = GL_FALSE;
			break;
		}
	}

}

void Keyboard::Special(int key, int x, int y){

	if (status->loggedIn) {
		switch (key){
		case GLUT_KEY_F1:
			gravaGrafo(status->mapfile);
			break;
		case GLUT_KEY_F2:
			leGrafo(status->mapfile);
			glutPostRedisplay();
			break;

		case GLUT_KEY_F3:
			status->top = GL_TRUE;
			status->first = GL_FALSE;
			glutPostRedisplay();
			break;

		case GLUT_KEY_F4:
			status->top = GL_FALSE;
			status->first = GL_TRUE;
			glutPostRedisplay();
			break;

		case GLUT_KEY_F5:
			status->top = GL_FALSE;
			status->first = GL_FALSE;
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
			/*case GLUT_KEY_UP:
			status->camera->dist -= 1;
			glutPostRedisplay();
			break;
			case GLUT_KEY_DOWN:
			status->camera->dist += 1;
			glutPostRedisplay();
			break;*/

		case GLUT_KEY_UP:
			status->up = GL_TRUE;
			break;
		case GLUT_KEY_DOWN:
			status->down = GL_TRUE;
			break;
		case GLUT_KEY_LEFT:
			status->left = GL_TRUE;
			break;
		case GLUT_KEY_RIGHT:
			status->right = GL_TRUE;
			break;
		}
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
	printf("d,D - Alternar entre dia / noite\n");
	printf("******* Mundos ******* \n");
	printf("m,M - Seleccionar mundo \n");
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
