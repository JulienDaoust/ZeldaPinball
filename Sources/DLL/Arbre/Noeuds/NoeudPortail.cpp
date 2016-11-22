///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPortail.h"
#include "Utilitaire.h"
#include "ArbreRenduINF2990.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::NoeudPortail(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/portal.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::~NoeudPortail()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
	liste_.storageRelacher();
	//delete portailFrere;
	portailFrere = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Rotation autour de l'axe des z
	glRotated(angleRotation, 0, 0, 1);
	glScaled(scale_[0], scale_[1], scale_[2]);
	// Affichage du modèle.
	liste_.dessiner();
	// Restauration de la matrice.
	
	//Affichage du champs d'attraction du portail
	if (modeDebug_ == true)
	{
		glColor3d(0.3, 0.8, 0.8);
		glBegin(GL_TRIANGLE_FAN);

		double num_segments = 50.0;
		double r = calculerRayon();
		
		for (int i = 0; i < num_segments; i++)
		{
			double theta = 2.0f * 3.1415926f * double(i) / double(num_segments);//obtient l'angle courant

			double x = r * cosf(theta);//calculer la composante en x
			double y = r * sinf(theta);//calculer la composante en y

			glVertex2d(x,y);//sommet de la sortie
		}
		glEnd();
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}

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
void NoeudPortail::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::assignerFrere(NoeudPortail* noeud)
///
/// Cette fonction lie deux portail ensemble
///
/// @param[in] noeud: Portail lié
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::assignerFrere(NoeudPortail* noeud)
{
	portailFrere = noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  double NoeudPortail::calculerRayon()
///
/// Cette fonction calcul le rayon du plus petit cercle contenant le noeud (comprent le champ dattraction)
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudPortail::calculerRayon() const
{
	return utilitaire::calculerCylindreEnglobant(modele_).rayon * scale_[0] * modifierChampAttraction_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  double NoeudPortail::calculerRayonPortail()
///
/// Cette fonction calcul le rayon du plus petit cercle contenant le noeud (sans le champ dattraction)
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudPortail::calculerRayonPortail() const
{
	return utilitaire::calculerCylindreEnglobant(modele_).rayon * scale_[0];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  aidecollision::DetailsCollision NoeudButoirCirculaire::collision(NoeudAbstrait* noeud) const
///
/// Cette fonction retourne les informations de collisions
///
/// @return aidecollision::DetailsCollision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudPortail::collision(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision details;
	details.type = aidecollision::COLLISION_AUCUNE;

	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
	{
		double rayon = noeud->calculerRayon();
		glm::dvec3 pos2 = noeud->obtenirPositionRelative();
		details = aidecollision::calculerCollisionCercle(glm::dvec2(noeud->obtenirPositionRelative().x, noeud->obtenirPositionRelative().y), rayon, glm::dvec2(positionRelative_.x, positionRelative_.y), calculerRayon());
	}
	return details;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
