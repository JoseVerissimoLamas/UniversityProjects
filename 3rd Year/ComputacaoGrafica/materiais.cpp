#include <GL\freeGlut.h>
#include "materiais.h"

void initMaterials(int material) {

	switch (material) {
	/*case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
		break;*/
//.....................................................................Mine
	case 0: //..................................Oak Wood
		glMaterialfv(GL_FRONT, GL_AMBIENT, OakAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, OakDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, OakSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, OakCoef);
		break;
	case 1: //..................................Iron
		glMaterialfv(GL_FRONT, GL_AMBIENT, IronAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, IronDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, IronSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, IronCoef);
		break;
	case 2: //..................................Computer
	case 3:
	case 4:
	case 5:
		glMaterialfv(GL_FRONT, GL_AMBIENT, PcAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, PcDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, PcSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, PcCoef);
		break;
	case 6: //..................................Walls
	case 7:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WallAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WallDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WallSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, WallCoef);
		break;
	case 8: //..................................Sky
	case 9:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, SkyAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, SkyDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SkySpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SkyCoef);
		break;
	case 10: //..................................Grass
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GrassAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GrassDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GrassSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GrassCoef);
		break;
	case 11: //..................................Tapete
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, TapeteAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, TapeteDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, TapeteSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, TapeteCoef);
		break;

	}

}