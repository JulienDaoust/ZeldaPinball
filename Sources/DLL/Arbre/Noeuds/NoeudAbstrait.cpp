////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include <iostream>
#include <math.h>
#include "ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	type_( type )
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide déclaré virtuel pour les classes dérivées.  La
/// libération des afficheurs n'est pas la responsabilité de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par défaut de la classe de base.
///
/// @param[in] noeud : Le noeud à effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donné parmi le noeud
/// lui-même et ses enfants.
///
/// Elle retourne donc le noeud lui-même si son type est celui passé en
/// paramètre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-ème enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// dernière ne possède pas d'enfant.
///
/// @param[in] indice : L'indice du noeud à trouver.
///
/// @return Le pointeur vers le noeud s'il est trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant à ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud à ajouter.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien été effectué, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'état de sélection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont sélectionnés parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
	//selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction sélectionne le noeud et ses enfants.
///
/// Elle ne fait que sélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction désélectionne le noeud et ses enfants.
///
/// Elle ne fait que désélectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction vérifie si le noeud ou un de ses enfants est
/// sélectionné.
///
/// Elle ne fait que regarder si le noeud est sélectionné, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud sélectionné, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est sélectionné ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode même si le
///                      noeud n'est pas sélectionné.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par défaut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// généralement à faire pour l'affichage, c'est-à-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit à sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'état.
///
/// L'affichage comme tel est confié à la fonction afficherConcret(),
/// appelée par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
			);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);

		// Affichage concret
		afficherConcret();

		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.  Elle est
/// appelée par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise à être surcharger par
/// les classes dérivées.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{
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
void NoeudAbstrait::calculBoiteEnglobante()
{
	if (scale_[0] == 0 && scale_[1] == 0 && scale_[2] == 0)
	{
		scale_[0] = 1;
		scale_[1] = 1;
		scale_[2] = 1;
	}
	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	glm::dvec3 HG = { boite.coinMin[0] * scale_[0], boite.coinMax[1] * scale_[1], 0 };
	glm::dvec3 BG = { boite.coinMin[0] * scale_[0], boite.coinMin[1] * scale_[1], 0 };
	glm::dvec3 HD = { boite.coinMax[0] * scale_[0], boite.coinMax[1] * scale_[1], 0 };
	glm::dvec3 BD = { boite.coinMax[0] * scale_[0], boite.coinMin[1] * scale_[1], 0 };

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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerScale(double x, double y, double z)
///
/// Cette fonction assigne des valeurs au parametre scale_
///
/// @param [in] x : valeu donner au x de scale
/// @param [in] y : valeu donner au y de scale
/// @param [in] z : valeu donner au z de scale
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerScale(double x, double y, double z)
{
	scale_[0] = x;
	scale_[1] = y;
	scale_[2] = z;
	calculBoiteEnglobante();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::dessinerBoiteEnglobante()
///
/// Cette fonction effectue le rendu de la boite englobante de l'objet
/// si il est selectionné
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::dessinerBoiteEnglobante() const
{
	glPushMatrix();
	if (estSelectionne())
	{
		//glBegin(GL_LINE);
		//glColor3f(1.0, 0.0, 0.0);
		//glRotatef(angleRotation, 0, 0, 1);

		//// Affichage du modèle.
		//liste_.dessiner();

		glColor3f(1.0, 1.0, 1.0);//(0.0, 0.0, 0.0);
		glLineWidth(3);
		glBegin(GL_LINE_LOOP);

		glVertex3d(boiteEnglobante.coinBD[0], boiteEnglobante.coinBD[1], boiteEnglobante.coinBD[2]);
		glVertex3d(boiteEnglobante.coinHD[0], boiteEnglobante.coinHD[1], boiteEnglobante.coinHD[2]);
		glVertex3d(boiteEnglobante.coinHG[0], boiteEnglobante.coinHG[1], boiteEnglobante.coinHG[2]);
		glVertex3d(boiteEnglobante.coinBG[0], boiteEnglobante.coinBG[1], boiteEnglobante.coinBG[2]);
		glEnd();
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}

	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  BoiteEnglobante NoeudAbstrait::obtenirBoiteEnglobante( NoeudAbstrait* parent )
///
/// Cette fonction retourne la boite englobante
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
BoiteEnglobante NoeudAbstrait::obtenirBoiteEnglobante()
{
	BoiteEnglobante boitePositionnee = boiteEnglobante;
	glm::dvec3 translation = obtenirPositionRelative();

	boitePositionnee.coinHG = { translation[0] + boitePositionnee.coinHG[0], translation[1] + boitePositionnee.coinHG[1], 0 };
	boitePositionnee.coinBG = { translation[0] + boitePositionnee.coinBG[0], translation[1] + boitePositionnee.coinBG[1], 0 };
	boitePositionnee.coinHD = { translation[0] + boitePositionnee.coinHD[0], translation[1] + boitePositionnee.coinHD[1], 0 };
	boitePositionnee.coinBD = { translation[0] + boitePositionnee.coinBD[0], translation[1] + boitePositionnee.coinBD[1], 0 };
	return boitePositionnee;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
/// @fn void NoeudAbstrait::rotation(double angle)
///
/// Cette fonction effectue une rotation d'un object simple
///
/// @param [in] angle : angle de rotation
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::rotation(double angle, glm::dvec3 centre)
{
	angleRotation += angle;

	if (centre.x != positionRelative_.x && centre.y != positionRelative_.y)
	{
		double distX = positionRelative_[0] - centre[0];
		double distY = positionRelative_[1] - centre[1];

		double radAngle = 3.14159265358979323846 * angle / 180;

		double posX = distX * std::cos(radAngle) - distY * std::sin(radAngle) + centre[0];
		double posY = distX * std::sin(radAngle) + distY * std::cos(radAngle) + centre[1];

		positionRelative_[0] = posX;
		positionRelative_[1] = posY;
	}
	calculBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  bool NoeudAbstrait::estScaleable() const
///
/// Cette fonction verifie si un noeudpeut etre mis alechelle
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::estScaleable() const
{
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  double NoeudAbstrait::calculerRayon()
///
/// Cette fonction calcul le rayon du plus petit cercle contenant le noeud
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudAbstrait::calculerRayon() const
{
	return utilitaire::calculerCylindreEnglobant(modele_).rayon * scale_[0];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  aidecollision::DetailsCollision NoeudAbstrait::collision(NoeudAbstrait* noeud) const
///
/// Cette fonction retourne les informations de collisions
///
/// @return aidecollision::DetailsCollision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudAbstrait::collision(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision details;
	details.type = aidecollision::COLLISION_AUCUNE;
	return details;

}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
