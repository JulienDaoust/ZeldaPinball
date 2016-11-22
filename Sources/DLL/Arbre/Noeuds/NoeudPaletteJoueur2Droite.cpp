///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur2Droite.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "FacadeModele.h"
#include "NoeudPaletteJoueur2Droite.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteJoueur2Droite::NoeudPaletteJoueur2Droite(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur2Droite::NoeudPaletteJoueur2Droite(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le mod�le 3D
	modele_.charger("media/flipper2Droit.obj");

	// Cr�ation d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la m�me liste serait
	// recr��e pour chaque instance d'un noeud, alors que la m�me pourrait
	// �tre partag�e par toutes les instances d'un m�me type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	angleRotation = 30;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPalette::~NoeudPalette()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur2Droite::~NoeudPaletteJoueur2Droite()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPalette::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Droite::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// R�volution autour du centre.
	glRotated(angleRotation, 0, 0, 1);

	// Affichage du mod�le.
	liste_.dessiner();
	// Restauration de la matrice.
	glPopMatrix();
	dessinerBoiteEnglobante();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Droite::animer(float temps)
{
	if (dansLesAir && angleAnimation > 0)
	{
		angleRotation -= 15;
		angleAnimation -= 15;
		calculBoiteEnglobante();
		assignerEstAscension(1);
	}
	else if (!dansLesAir && angleAnimation < 60)
	{
		angleRotation += 3;
		angleAnimation += 3;
		calculBoiteEnglobante();
		assignerEstAscension(2);
	}
	else
		assignerEstAscension(0);

	if (dansLesAir && FacadeModele::obtenirInstance()->obtenirJoueurVirtuel() && angleAnimation <= 0)
	{
		setAnimation();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudPaletteJoueur2Droite::estScaeaable() const
///
/// Cette fonction verifie si un noeudpeut etre mis alechelle
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteJoueur2Droite::estScaleable() const
{
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void NoeudPaletteJoueur2Droite::setAnimation()
///
/// Cette fonction change l'animation selon si la palette foit monter ou descendre
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Droite::setAnimation()
{
	dansLesAir = !dansLesAir;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculBoiteEnglobante()
///
/// Cette fonction calcule la boite englobant un noeud (hitbox)
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Droite::calculBoiteEnglobante()
{

	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	double longueur = abs(boite.coinMax[0] - boite.coinMin[0]);
	double hauteur = abs(boite.coinMax[2] - boite.coinMin[2]);
	glm::dvec3 HD = { boite.coinMax[0] - hauteur / 2, boite.coinMax[2], 0 };
	glm::dvec3 BD = { boite.coinMax[0] - hauteur / 2, boite.coinMin[2], 0 };
	glm::dvec3 HG = { boite.coinMin[0] + hauteur / 4, boite.coinMax[2] - hauteur / 2, 0 };
	glm::dvec3 BG = { boite.coinMin[0] + hauteur / 4, boite.coinMin[2], 0 };

	double radAngle = (angleRotation * 3.141592 / 180);


	boiteEnglobante.coinHG[0] = HG[0] * std::cos(radAngle) - HG[1] * std::sin(radAngle);
	boiteEnglobante.coinHG[1] = HG[0] * std::sin(radAngle) + HG[1] * std::cos(radAngle);

	boiteEnglobante.coinBG[0] = BG[0] * std::cos(radAngle) - BG[1] * std::sin(radAngle);
	boiteEnglobante.coinBG[1] = BG[0] * std::sin(radAngle) + BG[1] * std::cos(radAngle);

	boiteEnglobante.coinHD[0] = HD[0] * std::cos(radAngle) - HD[1] * std::sin(radAngle);
	boiteEnglobante.coinHD[1] = HD[0] * std::sin(radAngle) + HD[1] * std::cos(radAngle);

	boiteEnglobante.coinBD[0] = BD[0] * std::cos(radAngle) - BD[1] * std::sin(radAngle);
	boiteEnglobante.coinBD[1] = BD[0] * std::sin(radAngle) + BD[1] * std::cos(radAngle);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
