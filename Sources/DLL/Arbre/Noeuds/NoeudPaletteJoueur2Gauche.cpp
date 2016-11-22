///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur2Gauche.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "FacadeModele.h"
#include "NoeudPaletteJoueur2Gauche.h"
#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteJoueur2Gauche::NoeudPaletteJoueur2Gauche(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur2Gauche::NoeudPaletteJoueur2Gauche(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/flipper2Gauche.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	angleRotation = -30;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPalette::~NoeudPalette()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur2Gauche::~NoeudPaletteJoueur2Gauche()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPalette::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Gauche::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(angleRotation, 0, 0, 1);

	// Affichage du modèle.
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
void NoeudPaletteJoueur2Gauche::animer(float temps)
{
	if (dansLesAir && angleAnimation < 60)
	{
		angleRotation += 15;
		angleAnimation += 15;
		calculBoiteEnglobante();
		assignerEstAscension(1);
	}
	else if (!dansLesAir && angleAnimation > 0)
	{
		angleRotation -= 3;
		angleAnimation -= 3;
		calculBoiteEnglobante();
		assignerEstAscension(2);
	}
	else
		assignerEstAscension(0);

	if (dansLesAir && FacadeModele::obtenirInstance()->obtenirJoueurVirtuel() && angleAnimation >= 60)
	{
		setAnimation();
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudPaletteJoueur2Gauche::estScaeaable() const
///
/// Cette fonction verifie si un noeudpeut etre mis alechelle
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteJoueur2Gauche::estScaleable() const
{
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual void NoeudPaletteJoueur2Gauche::setAnimation()
///
/// Cette fonction change l'animation selon si la palette foit monter ou descendre
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur2Gauche::setAnimation()
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
void NoeudPaletteJoueur2Gauche::calculBoiteEnglobante()
{

	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	double longueur = abs(boite.coinMax[0] - boite.coinMin[0]);
	double hauteur = abs(boite.coinMax[2] - boite.coinMin[2]);
	glm::dvec3 HG = { boite.coinMin[0] + hauteur / 2, boite.coinMax[2], 0 };
	glm::dvec3 BG = { boite.coinMin[0] + hauteur / 2, boite.coinMin[2], 0 };
	glm::dvec3 HD = { boite.coinMax[0] - hauteur / 4, boite.coinMax[2] - hauteur / 2, 0 };
	glm::dvec3 BD = { boite.coinMax[0] - hauteur / 4, boite.coinMin[2], 0 };

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