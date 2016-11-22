///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRessort.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRessort.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRessort::NoeudRessort(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRessort::NoeudRessort(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/springFinal.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	scale_[0] = 0.5;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRessort::~NoeudRessort()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRessort::~NoeudRessort()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRessort::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(angleRotation, 0, 0, 1);
	glScaled(scale_[0], scale_[1] * facteurRetraction, scale_[2]);
	// Affichage du modèle.
	liste_.dessiner();
	// Restauration de la matrice.
	glPopMatrix();
	dessinerBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRessort::assignerRetraction(bool enRetraction)
///
/// Cette fonction assigne l'etat de retraction
///
/// @param[in] bool : etat de retraction
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::assignerRetraction(bool enRetraction)
{
	if (enRetraction)
	{
		auRepos_ = false;
		facteurColissionBille = 1.0;
	}
	else
		facteurColissionBille = 1 / facteurRetraction;
	retraction = enRetraction;
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
void NoeudRessort::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (retraction && facteurRetraction > 0.4)
	{
		// facteur retraction passe de 1 à 0.4 en 0.3 seconde
		facteurRetraction -= temps * 2;
		calculBoiteEnglobante();
	}
	else if (!retraction && facteurRetraction > 1.0)
	{
		facteurRetraction = 1;
		calculBoiteEnglobante();
	}
	else if (!retraction && facteurRetraction < 1.0)
	{
		// la vitesse de remontee du ressort depend desacompression initiale
		facteurRetraction += temps * facteurColissionBille;
		calculBoiteEnglobante();
	}

	if (facteurRetraction == 1.0 && !auRepos_)
		auRepos_ = true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudRessort::estScaleable() const
///
/// Cette fonction verifie si un noeudpeut etre mis alechelle
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudRessort::estScaleable() const
{
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudRessort::enRetraction() const
///
/// Cette fonction verifie le ressort est en retraction
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudRessort::enRetraction() const
{
	return retraction;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudRessort::auRepos() const
///
/// Cette fonction verifie le ressort est au repos
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudRessort::auRepos() const
{
	return auRepos_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRessort::obtenirFacteurRetraction() const
///
/// Cette fonction retourne le facteur de retraction de la bille
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudRessort::obtenirFacteurRetraction() const
{
	return facteurRetraction;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRessort::obtenirFacteurCollision() const
///
/// Cette fonction retourne le facteur de collision de la bille
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudRessort::obtenirFacteurCollision() const
{
	return facteurColissionBille;
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
void NoeudRessort::calculBoiteEnglobante()
{
	if (scale_[0] == 0 && scale_[1] == 0 && scale_[2] == 0)
	{
		scale_[0] = 1;
		scale_[1] = 1;
		scale_[2] = 1;
	}
	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	glm::dvec3 HG = { boite.coinMin[0] * scale_[0], boite.coinMax[1] * scale_[1] * facteurRetraction, 0 };
	glm::dvec3 BG = { boite.coinMin[0] * scale_[0], boite.coinMin[1] * scale_[1] * facteurRetraction, 0 };
	glm::dvec3 HD = { boite.coinMax[0] * scale_[0], boite.coinMax[1] * scale_[1] * facteurRetraction, 0 };
	glm::dvec3 BD = { boite.coinMax[0] * scale_[0], boite.coinMin[1] * scale_[1] * facteurRetraction, 0 };

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
